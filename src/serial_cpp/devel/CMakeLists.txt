cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED True)
project(bufftest LANGUAGES C CXX)


add_executable(bufftest src/main.cpp)

add_library(buffer "")
target_sources(buffer PRIVATE "${CMAKE_SOURCE_DIR}/../include/Ring-Buffer/ringbuffer.c"
    PRIVATE "${CMAKE_SOURCE_DIR}/../include/Ring-Buffer/ringbuffer.h")
    
target_include_directories(bufftest PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_include_directories(bufftest PRIVATE "${CMAKE_SOURCE_DIR}/../include/")
target_include_directories(bufftest PRIVATE "/usr/include")
# add_library()
target_link_libraries(bufftest CppLinuxSerial buffer)

# target_link_libraries(bufftest SerialStateMachine)

#target_include_directories(enumtests PUBLIC "${CMAKE_SOURCE_DIR}/src")

# find dependencies