cmake_minimum_required(VERSION 2.6)
project(Game_Risk)

set(ENV{TERM} "xterm-256color")
set(CMAKE_CFLAGS "-std=c99 -Wall")
set(SOURCES_FILES
        main.c
        model.c
        initializer.c
        view.c
        interact.c)

add_executable(Risk_text ${SOURCES_FILES})