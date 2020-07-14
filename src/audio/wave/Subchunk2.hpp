#ifndef SUBCHUNK2_HPP_
#define SUBCHUNK2_HPP_

#include "RiffChunk.hpp"
#include <cstring>

class Subchunk2: public RiffChunk
{
public:
  Subchunk2();

  bool Deserialize(BufferParser & bufferParser) override;
  bool Serialize(BufferSerializer & bufferSerializer) override;

  std::uint8_t*   data_;

private:
  // 0x64617461 = "data"
  static const std::uint32_t CHUNK_ID = 0x64617461;
}; // Subchunk2


#endif // SUBCHUNK2_HPP_
