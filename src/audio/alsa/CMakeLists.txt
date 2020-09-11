add_library(sound PCMDevicePlayer.cpp PCMDeviceOutput.cpp)
target_include_directories(sound PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(sound asound)
