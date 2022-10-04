cmake_minimum_required(VERSION 3.13)
project(A1_Solution)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-Wall)

add_executable(A1_Solution
        main.cpp
        DB_lib/dbComponents.cpp
        DB_lib/dbComponents.h
        BplusTree_lib/BplusTree.cpp
        BplusTree_lib/BplusTree.h
        util/forDataFileCRUD.h
        util/forBlockANDRecordGeneration.h
        newBPTree_lib/newBPTree.cpp
        newBPTree_lib/newBPTree.h)
