#include "OpenCV_WebCam.hpp"

OpenCV_WebCam::OpenCV_WebCam()
{

} // OpenCV_WebCam

OpenCV_WebCam::~OpenCV_WebCam()
{

} // ~OpenCV_WebCam

bool OpenCV_WebCam::open()
{
    mCapture = new cv::VideoCapture(0);
    if (!mCapture->isOpened())
        return false;
    return true;
} // open

bool OpenCV_WebCam::close()
{
    delete mCapture;
    return true;
} // close

bool OpenCV_WebCam::getFrame(cv::Mat & frame)
{
    bool return_value = mCapture->read(frame); // get a new frame from the camera
    return return_value;
} // getFrame
