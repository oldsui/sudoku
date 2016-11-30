cmake_minimum_required(VERSION 3.6)
project(sudokuSolver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(myTest myTest.cc)

add_executable(tst tst.cc)