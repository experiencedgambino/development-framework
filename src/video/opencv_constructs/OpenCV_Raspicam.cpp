#include "OpenCV_Raspicam.hpp"

OpenCV_Raspicam::OpenCV_Raspicam()
{

} // OpenCV_WebCam

OpenCV_Raspicam::~OpenCV_Raspicam()
{

} // ~OpenCV_WebCam

bool OpenCV_Raspicam::open()
{
  if (raspicam_.open() == false)
  {
    return false;
  } // if
  else
  {
    std::this_thread::sleep_for(std::chrono::seconds(3));
  } // else
  return true;
} // open

bool OpenCV_Raspicam::getFrame(cv::Mat & frame)
{
    bool return_value {true};
    raspicam_.grab();
    raspicam_.retrieve(frame);
    return return_value;
} // getFrame
