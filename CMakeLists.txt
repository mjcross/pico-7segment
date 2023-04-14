cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(myproject)

pico_sdk_init()

add_compile_options(
	-Wall
	-Wno-format
	-Wno-unused-function
	-Wno-maybe-uninitialized
	-Wextra    			# optional
)

add_executable(myproject)

target_sources(myproject PRIVATE myproject.c)

add_subdirectory(myproject_library)

target_link_libraries(myproject PRIVATE
	pico_stdlib
	hardware_pio
	myproject_library)

pico_add_extra_outputs(myproject)

# pico_enable_stdio_usb(myproject 1)
pico_enable_stdio_uart(myproject 1)

# example_auto_set_url(myproject)
