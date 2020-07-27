#ifndef WAV_READER_HPP
#define WAV_READER_HPP

#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <memory>
#include <vector>

#include "RiffChunk.hpp"
#include "RiffHeader.hpp"
#include "Subchunk1.hpp"
#include "Subchunk2.hpp"
#include "JunkChunk.hpp"
#include "ListChunk.hpp"

#include "BufferSerializer.hpp"

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

  std::uint32_t Serialize(void);

  std::uint16_t SwapEndian(const std::uint16_t & num);
  std::uint32_t SwapEndian(const std::uint32_t & num);

  std::vector<std::pair<std::int16_t, std::shared_ptr<RiffChunk>>> chunkvector_;
  RiffHeader riffHeader_;
  std::shared_ptr<Subchunk1> subchunk1_ {std::make_shared<Subchunk1>()};
  std::shared_ptr<Subchunk2> subchunk2_ {std::make_shared<Subchunk2>()};
  std::shared_ptr<JunkChunk> junkchunk_ {std::make_shared<JunkChunk>()};
  std::shared_ptr<ListChunk> listchunk_ {std::make_shared<ListChunk>()};

  bool foundJunk_ {false};
  bool foundList_ {false};

  std::ifstream   mInputFileStream;
  std::ofstream   mOutputFileStream;
  std::uint8_t*   mWavFileBuffer;
  std::uint32_t   mBufferOffset;
  std::uint32_t   mSerializedByteIndex;;

  std::size_t length_of_file;

  static const std::int16_t NOT_FOUND;

  static const std::uint16_t FOUR_BYTES;
  static const std::uint16_t TWO_BYTES;
  static const std::uint16_t SIXTEEN_BITS_PER_SAMPLE;
  static const std::uint16_t SIXTEEN_BITS_PER_SAMPLE_VALUE_OFFSET;
}; // WavReader

#endif /* WAV_READER_HPP */
