add_library(threads AbstractThread.cpp)
target_include_directories(threads PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(threads pthread)
