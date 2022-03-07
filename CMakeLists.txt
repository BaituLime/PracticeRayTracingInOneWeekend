cmake_minimum_required(VERSION 3.21)
project(RayTracingInOneWeekend)

set(CMAKE_CXX_STANDARD 17)

add_executable(GradientPPMGenerator GradientPPMGenerator/main.cpp)

add_executable(RayTracer
        General/Vector3.cpp
        General/Ray.cpp
        RayTracer/Main.cpp
        General/Color.cpp General/Sphere.cpp General/Sphere.h)