#ifndef FFTNODE_HPP
#define FFTNODE_HPP

#include "AsyncNode.hpp"
#include "CooleyTurkeyFFT.hpp"
#include "PCMDevicePlayer.hpp"

class FFTNode: public AsyncNode
{
public:
  FFTNode();
  ~FFTNode();

  void OnDataAvailableAsync(std::shared_ptr<PipelineData> data) override;

private:
  void CopyToInputBuffer(std::int16_t * buffer, std::size_t size);
  void FilterInputBuffer();
  void CopyFromInputBuffer(std::int16_t * buffer, std::size_t size);

private:
  static const std::size_t FFT_SIZE;
  std::vector<std::complex<double>> input;
  std::vector<std::complex<double>> output;
  std::vector<std::complex<double>> input_filtered;
  std::vector<double> magnitude_output;
}; // FFTNode



#endif // FFTNODE_HPP
