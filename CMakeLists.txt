cmake_minimum_required(VERSION 3.23)
project(distributed_file_system_test)
set(CMAKE_CXX_STANDARD 11)

#连接pthread
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -fPIC -lrt")

ADD_EXECUTABLE(copy_file copy_file.cpp)
ADD_EXECUTABLE(large_file_write_once_test large_file_write_once_test.cpp)

target_link_libraries(large_file_write_once_test
    PUBLIC
        /usr/local/lib64/libcfs.so)
