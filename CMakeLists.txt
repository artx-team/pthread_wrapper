cmake_minimum_required(VERSION 3.21)
project(pthread_wrapper NONE)

find_program(ASTYLE astyle)
if(ASTYLE)
    add_custom_target(astyle
        VERBATIM
        USES_TERMINAL
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMAND ${ASTYLE} --options=${CMAKE_SOURCE_DIR}/.astylerc -Q -n pthread_wrapper.h
    )
endif()

install(FILES pthread_wrapper.h DESTINATION include)
