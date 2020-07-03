add_library(forwarder GenericForwarder.cpp MultiForwarder.cpp)
target_link_libraries(forwarder data)
target_link_libraries(forwarder receptor)
target_include_directories(forwarder PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
