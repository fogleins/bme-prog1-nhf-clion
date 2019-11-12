#[[
cmake_minimum_required(VERSION 3.15)
project(nhf C)

set(CMAKE_C_STANDARD 99)

add_executable(nhf main.c)]]

#ez igy mukodik clionben
cmake_minimum_required(VERSION 3.15)
project(sdlteszt C)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_C_STANDARD 99)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(sdlteszt main.c ablakkezeles.c menu.c jatek.c fajlkezeles.c fajlkezeles.h)

#target_link_libraries(sdlteszt ${SDL2_LIBRARY} -lmingw32 -lSDL2main -lSDL2 -mwindows -lSDL2_gfx)
target_link_libraries(sdlteszt "${SDL2_LIBRARY}" -lmingw32 -lSDL2 -lSDL2_gfx -lSDL2main -lSDL2_image -lSDL2_ttf)

