cmake_minimum_required(VERSION 2.6)
project(Game_Risk_in_C)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_C_FLAGS "-std=c99 -g -Wall")

set(SOURCE_FILES
        Risk/main.c
        Risk/model.c
        Risk/initializer.c
        Risk/view.c)

add_executable(Game_Risk_in_C ${SOURCE_FILES})