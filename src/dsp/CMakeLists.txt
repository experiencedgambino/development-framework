add_library(dsp CooleyTurkeyFFT.cpp)
target_include_directories(dsp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
