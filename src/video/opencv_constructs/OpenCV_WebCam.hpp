#ifndef OPENCV_WEBCAM_HPP
#define CAMERA_WEBCAM_HPP

#include "opencv2/videoio.hpp"

class OpenCV_WebCam
{
public:
    // Constructor
    OpenCV_WebCam();

    // Destructor
    ~OpenCV_WebCam();

    // Camera:getFrame
    bool getFrame(cv::Mat & frame);

    // Camera:open
    bool open();

    // Camera:close
    bool close();

    // isOpen
    bool isOpen();
private:
    // VideoCapture object
    cv::VideoCapture * mCapture;
}; // WebCam

#endif
