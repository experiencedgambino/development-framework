add_library(opencv_constructs
  BackgroundSubtractor.cpp
  ImageTransformations.cpp
  MotionDetector.cpp
  OpenCV_WebCam.cpp
  OpenCV_Raspicam.cpp
)
target_link_libraries(opencv_constructs opencv_3rdparty)
target_link_libraries(opencv_constructs raspicam_3rdParty)
target_include_directories(opencv_constructs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
