cmake_minimum_required(VERSION 3.20)
project(sicsic_assignments C)

set(CMAKE_C_STANDARD 11)

add_executable(sicsic_assignments code/main.c
        ../sicsic_c_2/assignment_details/main_template.c
        ../sicsic_c_2/assignment_details/ex02.c)
