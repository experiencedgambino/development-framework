add_library(sockets UdpReceiver.cpp UdpSender.cpp)
target_include_directories(sockets PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
