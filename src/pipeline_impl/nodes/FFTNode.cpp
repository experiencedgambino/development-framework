#include "FFTNode.hpp"

const std::size_t FFTNode::FFT_SIZE = PCMDevicePlayer::NUMBER_OF_FRAMES * PCMDevicePlayer::BYTES_PER_SAMPLE;

FFTNode::FFTNode()
{
  input.resize(FFTNode::FFT_SIZE);
  output.resize(FFTNode::FFT_SIZE);
  input_filtered.resize(FFTNode::FFT_SIZE);
  magnitude_output.resize(FFTNode::FFT_SIZE);
}
FFTNode::~FFTNode()
{

} // FileRecorderNode

void FFTNode::OnDataAvailableAsync(std::shared_ptr<PipelineData> data)
{;
  // Channel 1
  CopyToInputBuffer(reinterpret_cast<std::int16_t *>(data->buffer_.data()), data->buffer_.size() / sizeof(std::int16_t));
  FilterInputBuffer();
  CopyFromInputBuffer(reinterpret_cast<std::int16_t *>(data->buffer_.data()), data->buffer_.size() / sizeof(std::int16_t));

  // Channel 2
  CopyToInputBuffer(reinterpret_cast<std::int16_t *>(data->buffer_.data())+1, data->buffer_.size() / sizeof(std::int16_t));
  FilterInputBuffer();
  CopyFromInputBuffer(reinterpret_cast<std::int16_t *>(data->buffer_.data())+1, data->buffer_.size() / sizeof(std::int16_t));

  SendData(data);
} // OnDataAvailableAsync

void FFTNode::CopyToInputBuffer(std::int16_t * buffer, std::size_t size)
{
  for (std::size_t index = 0; index < size / PCMDevicePlayer::NUMBER_CHANNELS; ++index)
  {
    input[index] = std::complex<double>((double)buffer[index*2], 0);
  } // for
} // CopyInputBuffer

void FFTNode::FilterInputBuffer()
{
  CooleyTurkeyFFT::fft_attempt(input.data(), output.data(), FFTNode::FFT_SIZE, 1);

  for (std::size_t k_counter = 0; k_counter < FFTNode::FFT_SIZE; ++k_counter)
  {
    magnitude_output[k_counter] = std::abs(output[k_counter]);
  } // for
  for (std::size_t min_counter = 0; min_counter < FFTNode::FFT_SIZE - 1; ++min_counter)
  {
    std::size_t minimum_output = std::min_element(magnitude_output.begin(), magnitude_output.begin()+FFTNode::FFT_SIZE) - magnitude_output.begin();
    magnitude_output[minimum_output] = std::numeric_limits<double>().max();
    output[minimum_output] = std::complex<double>(0,0);
  } // for
  CooleyTurkeyFFT::ifft_attempt(output.data(), input_filtered.data(), FFTNode::FFT_SIZE);

} // FFTInputBuffer

void FFTNode::CopyFromInputBuffer(std::int16_t * buffer, std::size_t size)
{
  for(std::size_t n_counter = 0; n_counter < size / PCMDevicePlayer::NUMBER_CHANNELS; ++n_counter)
  {
    buffer[n_counter*2] = input_filtered[n_counter].real();
  } // for
} // FFTInputBuffer
