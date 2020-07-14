#ifndef SUBCHUNK1_HPP_
#define SUBCHUNK1_HPP_

#include "RiffChunk.hpp"

class Subchunk1: public RiffChunk
{
public:
  bool Deserialize(BufferParser & bufferParser) override;
  bool Serialize(BufferSerializer & bufferSerializer) override;
  
  // Data fields
  std::uint16_t   audioFormat_ {0};
  std::uint16_t   numChannels_ {0};
  std::uint32_t   sampleRate_ {0};
  std::uint32_t   byteRate_ {0};
  std::uint16_t   blockAlign_ {0};
  std::uint16_t   bitsPerSample_ {0};

private:
  // 0x666d7420 = "fmt "
  static const std::uint32_t CHUNK_ID = 0x666d7420;


}; // SubChunk1

#endif  // SUBCHUNK1_HPP_
