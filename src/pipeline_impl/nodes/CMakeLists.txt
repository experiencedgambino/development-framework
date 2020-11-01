add_library(nodes_impl
  FrameCaptureNode_Raspicam.cpp
  FrameCaptureNode_Webcam.cpp
  UdpReceiverNode.cpp
  FileReaderNode.cpp
  FileRecorderNode.cpp
  HexPrinterNode.cpp
  PCMDevicePlayerNode.cpp
  FFTNode.cpp
  FrameDisplayNode.cpp
  AccumulatorNode.cpp
)

target_include_directories(nodes_impl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(nodes_impl node)
target_link_libraries(nodes_impl opencv_constructs)
target_link_libraries(nodes_impl sockets)
target_link_libraries(nodes_impl sound)
target_link_libraries(nodes_impl threads)
target_link_libraries(nodes_impl dsp)
target_link_libraries(nodes_impl raspicam_3rdParty)
