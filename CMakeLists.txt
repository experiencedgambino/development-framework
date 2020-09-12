cmake_minimum_required(VERSION 3.0.0)
project(DevelopmentFramework)
set (CMAKE_CXX_STANDARD 17)

# Always set build type to release by default
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(3rdparty)
