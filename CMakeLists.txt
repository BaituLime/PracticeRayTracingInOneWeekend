cmake_minimum_required(VERSION 3.21)
project(RayTracingInOneWeekend)

set(CMAKE_CXX_STANDARD 17)

add_executable(GradientPPMGenerator GradientPPMGenerator/main.cpp)

add_executable(RayTracer
        General/Vector3.cpp
        General/Ray.cpp
        RayTracer/Main.cpp
        General/Color.cpp General/Sphere.cpp General/Sphere.h General/Hitable.hpp General/HitableList.cpp General/HitableList.h General/CommonHeader.hpp General/Camera.cpp General/Camera.h General/Material.hpp General/LambertianMaterial.cpp General/LambertianMaterial.h General/MetalMaterial.cpp General/MetalMaterial.h General/DielectricMaterial.cpp General/DielectricMaterial.h)