cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(seven_segment)

pico_sdk_init()

add_compile_options(
	-Wall
	-Wno-format
	-Wno-unused-function
	-Wno-maybe-uninitialized
	-Wextra    			# optional
)

add_executable(seven_segment)

target_sources(seven_segment PRIVATE seven_segment.c)

add_subdirectory(seven_segment_library)

target_link_libraries(seven_segment PRIVATE
	pico_stdlib
	hardware_pio
	seven_segment_library)

pico_add_extra_outputs(seven_segment)

# pico_enable_stdio_usb(seven_segment 1)
pico_enable_stdio_uart(seven_segment 1)

# example_auto_set_url(seven_segment)
