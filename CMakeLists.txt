cmake_minimum_required (VERSION 3.30)

project(RayTracer)

set(HeadersDir headers)

set (Headers
  ${HeadersDir}/camera.h
  ${HeadersDir}/color.h
  ${HeadersDir}/hit.h
  ${HeadersDir}/image.h
  ${HeadersDir}/interval.h
  ${HeadersDir}/material.h
  ${HeadersDir}/object.h
  ${HeadersDir}/point3.h
  ${HeadersDir}/ppm-encoder.h
  ${HeadersDir}/ray.h
  ${HeadersDir}/renderer.h
  ${HeadersDir}/scene.h
  ${HeadersDir}/sphere.h
  ${HeadersDir}/utility.h
  ${HeadersDir}/vector3.h
)

set (Sources
  src/camera.cpp
  src/color.cpp
  src/hit.cpp
  src/image.cpp
  src/interval.cpp
  src/material.cpp
  src/object.cpp
  src/point3.cpp
  src/ppm-encoder.cpp
  src/ray.cpp
  src/renderer.cpp
  src/scene.cpp
  src/sphere.cpp
  src/utility.cpp
  src/vector3.cpp
  src/main.cpp
)

set (CMAKE_CXX_STANDARD 20)

add_executable (RayTracer ${Sources} ${Headers})

target_include_directories(RayTracer PRIVATE ${HeadersDir})