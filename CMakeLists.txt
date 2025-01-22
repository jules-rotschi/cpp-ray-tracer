cmake_minimum_required (VERSION 3.31.3)

project(RayTracer)

set(HeadersDir headers)

set (Headers

)

set (Sources
src/main.cpp
)

set (CMAKE_CXX_STANDARD 17)

add_executable (ConnectFour ${Sources} ${Headers})

target_include_directories(RayTracer PRIVATE ${HeadersDir})