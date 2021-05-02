#ifndef RASPICAMRAW_HPP
#define RASPICAMRAW_HPP

#include <raspicam/raspicam.h>
#include <opencv2/videoio.hpp>
#include <thread>
#include <iostream>

class RaspicamRaw
{
public:
    // Constructor
    RaspicamRaw();

    // Destructor
    ~RaspicamRaw();

    // Camera:getFrame
    bool getFrame(cv::Mat & frame);

    // Camera:open
    bool open();
    
    // isOpen
    bool isOpen();
private:
    // VideoCapture object
    raspicam::RaspiCam raspicam_; //Cmaera object
}; // RaspicamRaw

#endif // RASPICAMRAW_HPP
