cmake_minimum_required(VERSION 3.6)
project(aiProject)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    sudokuSolver/BackTrackGrid.h
    sudokuSolver/Cell.h
    sudokuSolver/Grid.h
    sudokuSolver/MRVGrid.h
    sudokuSolver/myTest.cc)

add_executable(myTest ${SOURCE_FILES})