#include "PCMDevicePlayer.hpp"

PCMDevicePlayer::PCMDevicePlayer()
{

} // PCMDevicePlayer

PCMDevicePlayer::~PCMDevicePlayer()
{
  Shutdown();
} // ~PCMDevicePlayer

void PCMDevicePlayer::Shutdown()
{
  if (buffer_ != nullptr)
  {
    snd_pcm_drop(handle_);
    snd_pcm_close(handle_);
    free(buffer_);
    buffer_ = nullptr;
  } // if
} // Shutdown

bool PCMDevicePlayer::Initialize(void)
{
  bool return_value {true};
  int asound_ret {0};
  snd_pcm_hw_params_t *params;
  int size, dir;
  unsigned int val;
  // Open PCM device for recording (capture)
  asound_ret = snd_pcm_open(&handle_, "default",
                    SND_PCM_STREAM_CAPTURE, 0);

  // Handle possible error
  if (asound_ret < 0)
  {
    std::cout << "PCMDevicePlayer::" << std::string(__func__)
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
  snd_pcm_hw_params_set_channels(handle_, params, 2);

  /* 44100 bits/second sampling rate (CD quality) */
  val = 44100;
  snd_pcm_hw_params_set_rate_near(handle_, params,
                                  &val, &dir);

  /* Set period size to 32 frames. */
  frames_ = 32;
  snd_pcm_hw_params_set_period_size_near(handle_,
                              params, &frames_, &dir);

  /* Write the parameters to the driver */
  asound_ret = snd_pcm_hw_params(handle_, params);
  if (asound_ret < 0)
  {
    std::cout << "PCMDevicePlayer::" << std::string(__func__)
              << ": unable to set hw params: "  << snd_strerror(asound_ret)
              << std::endl;
    return_value = false;
    return return_value;
  }

  /* Use a buffer large enough to hold one period */
  snd_pcm_hw_params_get_period_size(params,
                                      &frames_, &dir);
  buffersize_ = frames_ * 4; /* 2 bytes/sample, 2 channels */
  buffer_ = (char *) malloc(buffersize_);

  /* We want to loop for 5 seconds */
  snd_pcm_hw_params_get_period_time(params,
                                         &val, &dir);

  return return_value;
} // Initialize

void PCMDevicePlayer::ReadSound(void)
{
  int asound_ret {0};
  asound_ret = snd_pcm_readi(handle_, buffer_, frames_);
  if (asound_ret == -EPIPE)
  {
    /* EPIPE means overrun */
    fprintf(stderr, "overrun occurred\n");
    snd_pcm_prepare(handle_);
  }
  else if (asound_ret < 0)
  {
    fprintf(stderr,
            "error from read: %s\n",
            snd_strerror(asound_ret));
  }
  else if (asound_ret != (int)frames_)
  {
    fprintf(stderr, "short read, read %d frames\n", asound_ret);
  }
  if (asound_ret != buffersize_)
  {
    // fprintf(stderr,
            // "short write: wrote %d bytes\n", asound_ret);
  } // if
} // ReadSound

const char * PCMDevicePlayer::Data()
{
  return buffer_;
} // Data

std::size_t PCMDevicePlayer::Size()
{
  return buffersize_;
} // Size
