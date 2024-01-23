project(Homework)
cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories(.)

enable_testing()

#add_subdirectory(Array)
#add_subdirectory(Rational)
add_subdirectory(Itertools.Range)
add_subdirectory(SharedPtr)
#add_subdirectory(UniquePtr)
#add_subdirectory(StringView)

