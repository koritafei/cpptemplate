cmake_minimum_required(VERSION 3.15)

project(templateprogram)

add_definitions(--std=c++11)

set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_BUILD_TYPE "Debug")  
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")  
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")  


add_subdirectory(BaseSkill)
add_subdirectory(Chapter02)
add_subdirectory(Chapter03)