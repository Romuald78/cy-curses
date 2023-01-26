cmake_minimum_required(VERSION 3.23)
project(cy_curses C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_CXX_FLAGS "-lncursesw")
#set(CURSES_NEED_WIDE TRUE)
#find_package(Curses REQUIRED)
#include_directories(${CURSES_INCLUDE_DIR})

add_library(RGR STATIC sources/errors/errors.c sources/errors/errors.h sources/libRGR/libRGR.c sources/libRGR/libRGR.h sources/libRGR/keys.h)

add_executable(cy_curses main.h cb01_init.c cb02_event.c cb03_update.c cb04_draw.c cb05_finish.c main.c)

target_link_libraries(cy_curses RGR)
target_link_libraries(cy_curses ncursesw)
