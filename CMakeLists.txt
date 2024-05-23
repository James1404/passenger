cmake_minimum_required(VERSION 3.27.7)

project(passenger VERSION 0.01)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_EXTENSIONS OFF)

add_library(passenger)
add_executable(passenger_exe)
set_property(TARGET passenger_exe PROPERTY OUTPUT_NAME passenger)

set(passenger_CURRENT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB passenger_src
	${passenger_CURRENT_DIR}/src/*.cpp
	${passenger_CURRENT_DIR}/src/*.c
)

target_sources(passenger PRIVATE ${passenger_src})
target_sources(passenger_exe PRIVATE ${passenger_src})

target_include_directories(passenger PUBLIC
    ${passenger_CURRENT_DIR}/include
)

target_include_directories(passenger_exe PUBLIC
    ${passenger_CURRENT_DIR}/include
)
