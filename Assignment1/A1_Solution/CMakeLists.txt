cmake_minimum_required(VERSION 3.13)
project(A1_Solution)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-Wall)

add_executable(A1_Solution
        main.cpp
        DB_library/dbComponents.cpp
        DB_library/dbComponents.h
        BplusTree_library/BplusTree.cpp
        BplusTree_library/BplusTree.h
        )
