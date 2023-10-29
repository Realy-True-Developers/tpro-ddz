cmake_minimum_required(VERSION 3.13)
project(tpro-ddz)

set(CMAKE_CXX_STANDART 20)

set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules/" ${CMAKE_MODULE_PATH}})

find_package(SFML 2.4.2 COMPONENTS graphics audio REQUIRED)

add_executable(main executable/main.cpp)

target_link_libraries(main sfml-graphics sfml-audio sfml-window sfml-system)