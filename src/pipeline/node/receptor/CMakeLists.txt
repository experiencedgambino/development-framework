add_library(receptor INTERFACE)
target_link_libraries(receptor INTERFACE queuing)
target_include_directories(receptor INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
