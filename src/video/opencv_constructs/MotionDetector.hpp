#ifndef MOTION_DETECTOR_HPP
#define MOTION_DETECTOR_HPP

#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/opencv.hpp>

class MotionDetector
{
public:
    MotionDetector();

    bool detect(const cv::Mat & frame, const cv::Mat & reference);

    cv::Mat mFrameOfInterest;
private:
    double mAreaThreshold {10000.0};

};

#endif // MOTION_DETECTOR_HPP
