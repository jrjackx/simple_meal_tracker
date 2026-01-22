cmake_minimum_required(VERSION 3.10)
project(Meal_Tracker)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -pedantic)

add_executable(meal_tracker
    meal_tracker.c
    meal_io.c
    array_manip.c
    array_display.c
)
