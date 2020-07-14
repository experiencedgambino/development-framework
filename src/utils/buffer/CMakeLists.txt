add_library(parser BufferParser.cpp BufferSerializer.cpp)
target_include_directories(parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
