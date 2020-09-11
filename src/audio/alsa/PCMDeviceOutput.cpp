#include "PCMDeviceOutput.hpp"

const std::uint32_t PCMDeviceOutput::NUMBER_CHANNELS = 2;
const int PCMDeviceOutput::BYTES_PER_SAMPLE = 2;
const int PCMDeviceOutput::NUMBER_OF_FRAMES = 32;
std::uint32_t PCMDeviceOutput::SAMPLING_RATE = 44100;

PCMDeviceOutput::PCMDeviceOutput()
{

} // PCMDeviceOutput

PCMDeviceOutput::~PCMDeviceOutput()
{
  Shutdown();
} // ~PCMDeviceOutput

void PCMDeviceOutput::Shutdown()
{
  if (buffer_ != nullptr)
  {
    snd_pcm_drop(handle_);
    snd_pcm_close(handle_);
    free(buffer_);
    buffer_ = nullptr;
  } // if
} // Shutdown

bool PCMDeviceOutput::Initialize(void)
{
  bool return_value {true};
  int asound_ret {0};
  snd_pcm_hw_params_t *params;
  int size, dir;
  unsigned int val;
  // Open PCM device for recording (capture)
  asound_ret = snd_pcm_open(&handle_, "default",
                    SND_PCM_STREAM_PLAYBACK, 0);

  // Handle possible error
  if (asound_ret < 0)
  {
    std::cout << "PCMDeviceOutput::" << std::string(__func__)
              << ": unable to open pcm device: "  << snd_strerror(asound_ret)
              << std::endl;
    return_value = false;
    return return_value;
  } // if

  /* Allocate a hardware parameters object. */
  snd_pcm_hw_params_alloca(&params);

  /* Fill it in with default values. */
  snd_pcm_hw_params_any(handle_, params);

  /* Set the desired hardware parameters. */

  /* Interleaved mode */
  snd_pcm_hw_params_set_access(handle_, params,
                      SND_PCM_ACCESS_RW_INTERLEAVED);

  /* Signed 16-bit little-endian format */
  snd_pcm_hw_params_set_format(handle_, params,
                              SND_PCM_FORMAT_S16_LE);

  /* Two channels (stereo) */
  snd_pcm_hw_params_set_channels(handle_, params, NUMBER_CHANNELS);


  snd_pcm_hw_params_set_rate_near(handle_, params,
                                  &SAMPLING_RATE, &dir);

  // Set period size
  frames_ = NUMBER_OF_FRAMES;
  snd_pcm_hw_params_set_period_size_near(handle_,
                              params, &frames_, &dir);

  /* Write the parameters to the driver */
  asound_ret = snd_pcm_hw_params(handle_, params);
  if (asound_ret < 0)
  {
    std::cout << "PCMDeviceOutput::" << std::string(__func__)
              << ": unable to set hw params: "  << snd_strerror(asound_ret)
              << std::endl;
    return_value = false;
    return return_value;
  }

  /* Use a buffer large enough to hold one period */
  snd_pcm_hw_params_get_period_size(params,
                                      &frames_, &dir);
  buffersize_ = frames_ * NUMBER_CHANNELS * BYTES_PER_SAMPLE;

  buffer_ = (char *) malloc(buffersize_);

  /* We want to loop for 5 seconds */
  snd_pcm_hw_params_get_period_time(params,
                                         &val, &dir);

  return return_value;
} // Initialize

void PCMDeviceOutput::PlaySound(void)
{
  int asound_ret {0};
  asound_ret = snd_pcm_writei(handle_, buffer_, frames_);

  if (asound_ret == -EPIPE)
  {
    /* EPIPE means underrun */
    std::cout << "underrun occurred" << std::endl;
    snd_pcm_prepare(handle_);
  } // if
  else if (asound_ret < 0)
  {
    std::cout << "error from writei: " << snd_strerror(asound_ret) << std::endl;
  } // else if
  else if (asound_ret != (int)frames_)
  {
    std::cout << "short write, write " << asound_ret << " frames" << std::endl;
  } // else if
} // ReadSound

char * PCMDeviceOutput::Data()
{
  return buffer_;
} // Data

std::size_t PCMDeviceOutput::Size()
{
  return buffersize_;
} // Size
