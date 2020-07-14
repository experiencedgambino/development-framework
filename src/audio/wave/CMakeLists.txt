set(ChunksDirectory)

add_library(wave WavReader.cpp RiffHeader.cpp Subchunk1.cpp JunkChunk.cpp Subchunk2.cpp ListChunk.cpp)
target_include_directories(wave PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(wave parser)
