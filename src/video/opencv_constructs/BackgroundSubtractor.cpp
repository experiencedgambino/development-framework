#include "BackgroundSubtractor.hpp"

BackgroundSubtractor::BackgroundSubtractor()
{
} // BackgroundSubtractor

void BackgroundSubtractor::resetBackground(cv::Mat & frame)
{
    frame.copyTo(mBackground);
} // resetBackground

void BackgroundSubtractor::addFrame(cv::Mat frame, float percentNew)
{
    cv::Mat grayFrame;
    cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
    cv::addWeighted(mBackground, 1.0 - percentNew, grayFrame, percentNew, 0, mBackground, 0);
    cv::absdiff(grayFrame, mBackground, mDiff);
} // addFrame

cv::Mat BackgroundSubtractor::getBackground()
{
     return mBackground.clone();
} // getBackground
