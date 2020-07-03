add_library(receptor INTERFACE)
target_link_libraries(receptor INTERFACE utils)
target_include_directories(receptor INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
