cmake_minimum_required (VERSION 3.31.3)

project(RayTracer)

set(HeadersDir headers)

set (Headers
  ${HeadersDir}/camera.h
  ${HeadersDir}/image.h
  ${HeadersDir}/light.h
  ${HeadersDir}/object.h
  ${HeadersDir}/point3.h
  ${HeadersDir}/ppm-encoder.h
  ${HeadersDir}/ray.h
  ${HeadersDir}/renderer.h
  ${HeadersDir}/scene.h
  ${HeadersDir}/sphere.h
  ${HeadersDir}/vector3.h
)

set (Sources
  src/camera.cpp
  src/image.cpp
  src/light.cpp
  src/object.cpp
  src/point3.cpp
  src/ppm-encoder.cpp
  src/ray.cpp
  src/renderer.cpp
  src/scene.cpp
  src/sphere.cpp
  src/vector3.cpp
  src/main.cpp
)

set (CMAKE_CXX_STANDARD 17)

add_executable (ConnectFour ${Sources} ${Headers})

target_include_directories(RayTracer PRIVATE ${HeadersDir})