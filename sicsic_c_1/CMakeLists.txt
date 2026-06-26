cmake_minimum_required(VERSION 3.20)
project(sicsic_assignments CXX)

set(CMAKE_CXX_STANDARD 14)

# --- הגדרת נתיב למטלה 3 הנוכחית ---
set(ASSIGNMENT3_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Assignment 3 - CPP")

# --- יעד הרצה ייעודי למטלה 3 ---
# זה יאפשר לך לבחור אותו למעלה ליד כפתור ה-Play ולהריץ רק אותו באופן נקי
add_executable(assignment3
        "${ASSIGNMENT3_DIR}/Array.h"
        "${ASSIGNMENT3_DIR}/Shape.h"
        "${ASSIGNMENT3_DIR}/Shape.cpp"
        "${ASSIGNMENT3_DIR}/Square.h"
        "${ASSIGNMENT3_DIR}/Square.cpp"
        "${ASSIGNMENT3_DIR}/Circle.h"
        "${ASSIGNMENT3_DIR}/Circle.cpp"
        "${ASSIGNMENT3_DIR}/OrthogonalTriangle.h"
        "${ASSIGNMENT3_DIR}/OrthogonalTriangle.cpp"
        "${ASSIGNMENT3_DIR}/main.cpp"
)