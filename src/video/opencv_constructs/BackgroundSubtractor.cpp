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
  cv::addWeighted(mBackground, 1.0 - percentNew, frame, percentNew, 0, mBackground, 0);
  cv::absdiff(frame, mBackground, mDiff);
} // addFrame

cv::Mat BackgroundSubtractor::getBackground()
{
  return mBackground.clone();
} // getBackground
