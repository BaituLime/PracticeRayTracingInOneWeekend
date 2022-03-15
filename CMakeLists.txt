cmake_minimum_required(VERSION 3.0.0)
project(SoftwareRenderer VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories("./General")

find_package(SDL2 CONFIG REQUIRED)

add_executable(RayTracer
        main.cpp
        General/Vector3.cpp
        General/Ray.cpp 
        General/Color.cpp General/Sphere.cpp General/Sphere.h General/Hitable.hpp General/HitableList.cpp General/HitableList.h General/CommonHeader.hpp General/Camera.cpp General/Camera.h General/Material.hpp General/LambertianMaterial.cpp General/LambertianMaterial.h General/MetalMaterial.cpp General/MetalMaterial.h General/DielectricMaterial.cpp General/DielectricMaterial.h)

target_link_libraries(RayTracer PRIVATE SDL2::SDL2 SDL2::SDL2main)