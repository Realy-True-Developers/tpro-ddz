cmake_minimum_required(VERSION 3.13)
project(tpro-ddz)

set(CMAKE_CXX_STANDART 20)

# set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules/" ${CMAKE_MODULE_PATH}})

# find_package(SFML 2.4.2 COMPONENTS graphics audio REQUIRED)

set(SFML_STATIC_LIBRARIES TRUE)

set(SFML_DIR "C:/Program Files/SFML-2.6.0/lib/cmake/SFML")

find_package(SFML 2.4.2 COMPONENTS graphics audio window system REQUIRED)

#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup") //Чтобы в Release версии не открывалась консоль

add_executable(main executable/main.cpp)
add_executable(menu game_menu/game_menu.cpp game_menu/menu_main.cpp)

target_link_libraries(menu sfml-graphics sfml-audio sfml-window sfml-system)
target_link_libraries(main sfml-graphics sfml-audio sfml-window sfml-system)