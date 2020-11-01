#include "ImageTransformations.hpp"

void ImageTransformations::NormalizeImage(cv::Mat & image)
{
  std::int32_t max = std::numeric_limits<std::int32_t>().min();
  std::int32_t min = std::numeric_limits<std::int32_t>().max();
  for (int row = 0; row < image.rows; ++row)
  {
    for (int col = 0; col < image.cols; ++col)
    {
      max = std::max(max, (int)image.at<std::uint8_t>(row, col));
      min = std::min(min, (int)image.at<std::uint8_t>(row, col));
    } // for
  } // for

  for (int row = 0; row < image.rows; ++row)
  {
    for (int col = 0; col < image.cols; ++col)
    {
      image.at<std::uint8_t>(row, col) = (image.at<std::uint8_t>(row, col) - min) * std::numeric_limits<std::uint8_t>().max() / (max - min);
    } // for
  } // for
} // NormalizeImage
