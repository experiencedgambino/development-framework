#ifndef RIFF_HEADER_HPP_
#define RIFF_HEADER_HPP_

#include "BufferParser.hpp"
#include "BufferSerializer.hpp"

class RiffHeader
{
public:
  bool Deserialize(BufferParser & bufferParser);
  bool Serialize(BufferSerializer & bufferSerializer);
  std::uint32_t chunkID_ {0};
  std::uint32_t restOfBufferSize_ {0};
  std::uint32_t waveString_ {0};
private:
  // 0x52494646 = "RIFF"
  static const std::uint32_t CHUNK_ID = 0x52494646;
  // 0x57415645 = "WAVE"
  static const std::uint32_t WAVE_STRING = 0x57415645;
}; // RiffHeader

#endif // RIFF_HEADER_HPP_
