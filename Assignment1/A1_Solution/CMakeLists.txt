cmake_minimum_required(VERSION 3.23)
project(A1_Solution)

set(CMAKE_CXX_STANDARD 14)

add_executable(A1_Solution
        main.cpp
        db_library/dbComponents.cpp
        db_library/dbComponents.h BplusTree_library/BplusTree.cpp BplusTree_library/BplusTree.h)
