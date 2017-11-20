cmake_minimum_required(VERSION 2.6)
project(Game_Risk_in_C)

set(CMAKE_C_FLAGS "-std=c99 -O3 -g -Wall")

set(SOURCE_FILES
        Risk/main.c
        Risk/initializer.c
        Risk/model.c
        Risk/view.c
        Risk/interact.c)

add_executable(Game_Risk_in_C ${SOURCE_FILES})