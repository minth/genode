/*
 * \brief  IPC message buffer layout for Fiasco.OC
 * \author Stefan Kalkowski
 * \date   2010-11-30
 *
 * On Fiasco.OC, IPC is used to transmit plain data and capabilities.
 * Therefore the message buffer contains both categories of payload.
 */

/*
 * Copyright (C) 2010-2013 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU General Public License version 2.
 */

#ifndef _INCLUDE__BASE__IPC_MSGBUF_H_
#define _INCLUDE__BASE__IPC_MSGBUF_H_

/* Genode includes */
#include <base/cap_map.h>

/* Fiasco.OC includes */
namespace Fiasco {
#include <l4/sys/types.h>
#include <l4/sys/utcb.h>
}

namespace Genode {

	class Ipc_marshaller;

	class Msgbuf_base
	{
		public:

			enum { MAX_CAP_ARGS_LOG2 = 2, MAX_CAP_ARGS = 1 << MAX_CAP_ARGS_LOG2 };

		protected:

			friend class Ipc_marshaller;

			size_t const _capacity;

			size_t _data_size = 0;

			/**
			 * Number of capability selectors to send.
			 */
			size_t _snd_cap_sel_cnt = 0;

			/**
			 * Capability selectors to delegate.
			 */
			addr_t _snd_cap_sel[MAX_CAP_ARGS];

			/**
			 * Base of capability receive window.
			 */
			Cap_index* _rcv_idx_base = nullptr;

			/**
			 * Read counter for unmarshalling portal capability selectors
			 */
			addr_t _rcv_cap_sel_cnt = 0;

			unsigned long _label = 0;

			char _msg_start[];  /* symbol marks start of message */

			/**
			 * Constructor
			 */
			Msgbuf_base(size_t capacity)
			:
				_capacity(capacity),
				_rcv_idx_base(cap_idx_alloc()->alloc_range(MAX_CAP_ARGS))
			{
				rcv_reset();
				snd_reset();
			}

		public:

			~Msgbuf_base()
			{
				cap_idx_alloc()->free(_rcv_idx_base, MAX_CAP_ARGS);
			}

			/*
			 * Begin of actual message buffer
			 */
			char buf[];

			/**
			 * Return size of message buffer
			 */
			size_t capacity() const { return _capacity; };

			/**
			 * Return pointer of message data payload
			 */
			void       *data()       { return &_msg_start[0]; };
			void const *data() const { return &_msg_start[0]; };

			size_t data_size() const { return _data_size; }

			unsigned long &word(unsigned i)
			{
				return reinterpret_cast<unsigned long *>(buf)[i];
			}

			/**
			 * Reset portal capability selector payload
			 */
			void snd_reset() { _snd_cap_sel_cnt = 0; }

			/**
			 * Append capability selector to message buffer
			 */
			bool snd_append_cap_sel(addr_t cap_sel)
			{
				if (_snd_cap_sel_cnt >= MAX_CAP_ARGS)
					return false;

				_snd_cap_sel[_snd_cap_sel_cnt++] = cap_sel;
				return true;
			}

			/**
			 * Return number of marshalled capability selectors
			 */
			size_t snd_cap_sel_cnt() const { return _snd_cap_sel_cnt; }

			/**
			 * Return capability selector to send.
			 *
			 * \param i  index (0 ... 'snd_cap_sel_cnt()' - 1)
			 * \return   capability selector, or 0 if index is invalid
			 */
			addr_t snd_cap_sel(unsigned i) const {
				return i < _snd_cap_sel_cnt ? _snd_cap_sel[i] : 0; }

			/**
			 * Return address of capability receive window.
			 */
			addr_t rcv_cap_sel_base() { return _rcv_idx_base->kcap(); }

			/**
			 * Reset capability receive window
			 */
			void rcv_reset() { _rcv_cap_sel_cnt = 0; }

			/**
			 * Return next received capability selector.
			 *
			 * \return   capability selector, or 0 if index is invalid
			 */
			addr_t rcv_cap_sel() {
				return rcv_cap_sel_base() + _rcv_cap_sel_cnt++ * Fiasco::L4_CAP_SIZE; }

			void label(unsigned long label) { _label = label; }
			unsigned long label() { return _label & (~0UL << 2); }
	};


	template <unsigned BUF_SIZE>
	class Msgbuf : public Msgbuf_base
	{
		public:

			char buf[BUF_SIZE];

			Msgbuf() : Msgbuf_base(BUF_SIZE) { }
	};
}

#endif /* _INCLUDE__BASE__IPC_MSGBUF_H_ */
