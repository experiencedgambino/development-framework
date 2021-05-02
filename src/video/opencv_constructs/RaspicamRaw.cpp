#include "RaspicamRaw.hpp"

RaspicamRaw::RaspicamRaw()
{

} // OpenCV_WebCam

RaspicamRaw::~RaspicamRaw()
{

} // ~OpenCV_WebCam

bool RaspicamRaw::open()
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

bool RaspicamRaw::getFrame(cv::Mat & frame)
{
    bool return_value {true};
    frame.create(raspicam_.getHeight(), raspicam_.getWidth(), CV_8UC3);
    raspicam_.grab();
    raspicam_.retrieve(frame.data);
    return return_value;
} // getFrame
