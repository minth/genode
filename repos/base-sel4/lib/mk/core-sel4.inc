GEN_CORE_DIR = $(BASE_DIR)/src/core

SRC_CC      += \
               main.cc \
               pd_session_component.cc \
               ram_dataspace_support.cc \
               rom_session_component.cc \
               cpu_session_component.cc \
               cpu_session_support.cc \
               cpu_thread_component.cc \
               rpc_cap_factory.cc \
               ram_dataspace_factory.cc \
               pd_session_support.cc \
               io_mem_session_component.cc \
               io_mem_session_support.cc \
               thread_start.cc \
               platform_thread.cc \
               platform_pd.cc \
               platform_services.cc \
               platform.cc \
               dataspace_component.cc \
               region_map_component.cc \
               region_map_support.cc \
               irq_session_component.cc \
               signal_source_component.cc \
               signal_transmitter_proxy.cc \
               signal_receiver.cc \
               trace_session_component.cc \
               core_region_map.cc \
               core_mem_alloc.cc \
               core_rpc_cap_alloc.cc \
               core_log.cc default_log.cc \
               dump_alloc.cc \
               stack_area.cc \
               capability_space.cc \
               pager.cc

LIBS        += base-sel4-common syscall-sel4 cxx

INC_DIR     += $(REP_DIR)/src/core/include $(GEN_CORE_DIR)/include \
               $(REP_DIR)/src/include      $(BASE_DIR)/src/include

include $(GEN_CORE_DIR)/version.inc

vpath main.cc                      $(GEN_CORE_DIR)
vpath pd_session_component.cc      $(GEN_CORE_DIR)
vpath rom_session_component.cc     $(GEN_CORE_DIR)
vpath cpu_session_component.cc     $(GEN_CORE_DIR)
vpath cpu_session_support.cc       $(GEN_CORE_DIR)
vpath cpu_thread_component.cc      $(GEN_CORE_DIR)
vpath pd_session_support.cc        $(GEN_CORE_DIR)
vpath pd_upgrade_ram_quota.cc      $(GEN_CORE_DIR)
vpath region_map_component.cc      $(GEN_CORE_DIR)
vpath io_mem_session_component.cc  $(GEN_CORE_DIR)
vpath io_mem_session_support.cc    $(GEN_CORE_DIR)
vpath trace_session_component.cc   $(GEN_CORE_DIR)
vpath signal_transmitter_proxy.cc  $(GEN_CORE_DIR)
vpath signal_receiver.cc           $(GEN_CORE_DIR)
vpath ram_dataspace_factory.cc     $(GEN_CORE_DIR)
vpath dataspace_component.cc       $(GEN_CORE_DIR)
vpath core_mem_alloc.cc            $(GEN_CORE_DIR)
vpath core_rpc_cap_alloc.cc        $(GEN_CORE_DIR)
vpath dump_alloc.cc                $(GEN_CORE_DIR)
vpath default_log.cc               $(GEN_CORE_DIR)
vpath %.cc                         $(REP_DIR)/src/core
