add_subdirectory(socket)

add_library(utils AbstractThread.cpp)
target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
