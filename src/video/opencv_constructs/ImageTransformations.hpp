#ifndef IMAGETRANSFORMATIONS_C_HPP_
#define IMAGETRANSFORMATIONS_C_HPP_

#include <opencv2/opencv.hpp>
#include <algorithm>
#include <limits>

class ImageTransformations
{
public:
  static void NormalizeImage(cv::Mat & image);
}; // ImageTransformations




#endif // IMAGETRANSFORMATIONS_C_HPP_
