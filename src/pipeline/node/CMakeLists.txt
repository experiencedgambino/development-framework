add_subdirectory(receptor)
add_subdirectory(forwarder)

add_library(node Node.cpp)
target_include_directories(node PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(node data)
target_link_libraries(node utils)
target_link_libraries(node forwarder)
