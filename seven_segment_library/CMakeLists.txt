add_library(seven_segment_library INTERFACE)

target_sources(seven_segment_library INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/seven_segment_library.c)

# invoke pio_asm to assemble the state machine programs
#
pico_generate_pio_header(seven_segment_library ${CMAKE_CURRENT_LIST_DIR}/seven_segment_library.pio)

target_link_libraries(seven_segment_library INTERFACE
        pico_stdlib
        hardware_pio
        )

# add the `binary` directory so that the generated headers are included in the project
#
target_include_directories(seven_segment_library INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
	)