#ifndef WAV_READER_HPP
#define WAV_READER_HPP

#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

class WavReader
{
public:
  WavReader();
  ~WavReader();

  bool Read(const std::string & wavString);
  bool Write(const std::string & wavString);
  void GetStream(std::ostream & output) const;
  enum Channel_e : std::uint16_t
  {
      CHANNEL_ONE,
      CHANNEL_TWO
  }; // Channel_e
  std::int16_t GetSample(const std::uint32_t & sampleNumber, const WavReader::Channel_e & channel) const;
  std::int16_t GetSample(const std::uint32_t & sampleNumber) const; // Retreive channel 1 sample
  void SetSample(const std::uint32_t & sampleNumber, const WavReader::Channel_e & channel, const std::int16_t & value);
  void SetSample(const std::uint32_t & sampleNumber, const std::int16_t & value);
  std::uint32_t DataSize(void);

private:
  bool Deserialize(void);
  bool Validate(void);
  std::uint32_t Serialize(void);

  std::uint16_t SwapEndian(const std::uint16_t & num);
  std::uint32_t SwapEndian(const std::uint32_t & num);

  // Wave structure fields
  struct WavHeader_s
  {
    char            RIFF[5];
    std::uint32_t   mChunkSize;
    char            WAVE[5];
  }; // WavHeader_s

  struct SubChunk1_s
  {
    char            mSubchunk1Id[5];
    std::uint16_t   mSubchunk1Size;
    std::uint16_t   mAudioFormat;
    std::uint16_t   mNumChannels;
    std::uint32_t   mSampleRate;
    std::uint32_t   mByteRate;
    std::uint16_t   mBlockAlign;
    std::uint16_t   mBitsPerSample;
  }; // SubChunk1

  struct SubChunk2_s
  {
    char            DATA[5];
    std::uint32_t   mSubchunk2Size;
    std::uint8_t*   mData;
  }; // SubChunk2

  std::ifstream   mInputFileStream;
  std::ofstream   mOutputFileStream;
  std::uint8_t*   mWavFileBuffer;
  std::uint32_t   mBufferOffset;
  std::uint32_t   mSerializedByteIndex;;

  WavHeader_s mWaveHeader;
  SubChunk1_s mSubchunk1;
  SubChunk2_s mSubchunk2;

  static const std::uint16_t UPPER_EIGHT_BITS_MASK;
  static const std::uint16_t LOWER_EIGHT_BITS_MASK;
  static const std::uint32_t FIRST_BYTE_INT_32;
  static const std::uint32_t SECOND_BYTE_INT_32;
  static const std::uint32_t THIRD_BYTE_INT_32;
  static const std::uint32_t FOURTH_BYTE_INT_32;

  static const std::uint16_t ONE_BYTE_SHIFT;
  static const std::uint16_t TWO_BYTE_SHIFT;
  static const std::uint16_t THREE_BYTE_SHIFT;

  static const std::uint16_t FOUR_BYTES;
  static const std::uint16_t TWO_BYTES;

  static const std::uint16_t SIXTEEN_BITS_PER_SAMPLE;
  static const std::uint16_t SIXTEEN_BITS_PER_SAMPLE_VALUE_OFFSET;
  static const std::uint16_t EIGHT_BITS_PER_SAMPLE;

  static const char RIFF_VALIDATE_STRING[5];
  static const char WAVE_VALIDATE_STRING[5];
  static const char DATA_VALIDATE_STRING[5];
  static const char FORMAT_VALIDATE_STRING[5];

}; // WavReader

#endif /* WAV_READER_HPP */
