#include "MotionDetector.hpp"

MotionDetector::MotionDetector()
{

} // MotionDetector

bool MotionDetector::detect(const cv::Mat & frame, const cv::Mat & reference)
{
    cv::Mat difference;
    cv::Mat threshold;
    cv::Mat opened_image;
    cv::Mat dilated_image;

    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(11,11));
    cv::Mat kernel_dilate = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(19,19));

    std::vector<std::vector<cv::Point>> contours;

    cv::absdiff(frame, reference, difference);
    cv::threshold(difference, threshold, 20, 255, cv::THRESH_BINARY);
    cv::morphologyEx(threshold, opened_image, cv::MORPH_OPEN, kernel);
    cv::morphologyEx(opened_image, dilated_image, cv::MORPH_DILATE, kernel_dilate);
    cv::findContours(dilated_image, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
    mFrameOfInterest = dilated_image.clone();
    for (std::size_t contourNum = 0; contourNum < contours.size(); ++contourNum)
    {
        double contour_area = cv::contourArea(contours[contourNum]);

        if (contour_area > mAreaThreshold)
        {
            return true;
        } // if
    } // for

    return false;
}
