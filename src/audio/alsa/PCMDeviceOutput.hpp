#ifndef PCMDEVICEOUTPUT_HPP_
#define PCMDEVICEOUTPUT_HPP_

#define ALSA_PCM_NEW_HW_PARAMS_API

#include <alsa/asoundlib.h>
#include <cstdint>
#include <iostream>

class PCMDeviceOutput
{
public:
  PCMDeviceOutput();
  ~PCMDeviceOutput();

  bool Initialize(void);

  void PlaySound(void);

  char * Data();
  std::size_t Size();

  void Shutdown();

public:
  static const std::uint32_t NUMBER_CHANNELS;
  static const int BYTES_PER_SAMPLE;
  static const int NUMBER_OF_FRAMES;
  static std::uint32_t SAMPLING_RATE;


private:
  snd_pcm_t *handle_;
  std::size_t buffersize_ {0};
  char * buffer_ {nullptr};
  snd_pcm_uframes_t frames_;
}; // PCMDevicePlayer

#endif // PCMDEVICEOUTPUT_HPP_
