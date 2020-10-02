add_library(opencv_constructs
  BackgroundSubtractor.cpp
  MotionDetector.cpp
  OpenCV_WebCam.cpp
)
target_link_libraries(opencv_constructs opencv_3rdparty)
target_include_directories(opencv_constructs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
