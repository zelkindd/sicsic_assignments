cmake_minimum_required(VERSION 3.20)
project(sicsic_assignments CXX) # הגדרה ל-C++ בלבד עבור המטלה הנוכחית

set(CMAKE_CXX_STANDARD 14)

# הגדרת משתנה הנתיב למטלה החדשה ב-C++
set(ASSIGNMENT1_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Assignment 1 - CPP")

# המטלה החדשה שלך - היעד היחיד שמעניין אותנו כרגע
add_executable(assignment1
        "${ASSIGNMENT1_DIR}/assignment1.cpp"
        "${ASSIGNMENT1_DIR}/StackNode.h"
        "${ASSIGNMENT1_DIR}/StackNode.cpp"
        "${ASSIGNMENT1_DIR}/Stack.h"
        "${ASSIGNMENT1_DIR}/Stack.cpp"
        #        "${ASSIGNMENT1_DIR}/MyQueue.h"
        #        "${ASSIGNMENT1_DIR}/MyQueue.cpp"
        #        "${ASSIGNMENT1_DIR}/Menu.h"
        #        "${ASSIGNMENT1_DIR}/Menu.cpp"
)