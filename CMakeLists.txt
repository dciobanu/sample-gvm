cmake_minimum_required(VERSION 3.0.0)
project(gvm VERSION 0.1.0)

add_executable(gvm main.cpp genesys_vm.cpp)
add_executable(tests tests.cpp genesys_vm.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
