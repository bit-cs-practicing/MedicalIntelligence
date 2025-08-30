cmake_minimum_required(VERSION 3.10.0)

project(MedicalIntelligence)

set(DCMAKE_SH="CMAKE_SH-NOTFOUND")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src/core)
add_subdirectory(src/server)
add_subdirectory(src/doctor-client)
add_subdirectory(src/patient-client)
