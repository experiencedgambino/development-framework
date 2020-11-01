#ifndef OPENCV_RASPICAM_HPP
#define OPENCV_RASPICAM_HPP

#include <raspicam/raspicam_cv.h>
#include <thread>

class OpenCV_Raspicam
{
public:
    // Constructor
    OpenCV_Raspicam();

    // Destructor
    ~OpenCV_Raspicam();

    // Camera:getFrame
    bool getFrame(cv::Mat & frame);

    // Camera:open
    bool open();
    
    // isOpen
    bool isOpen();
private:
    // VideoCapture object
    raspicam::RaspiCam_Cv raspicam_; //Cmaera object
}; // WebCam

#endif // OPENCV_RASPICAM_HPP
