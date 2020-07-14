#ifndef JUNKCHUNK_HPP_
#define JUNKCHUNK_HPP_

#include "RiffChunk.hpp"

class JunkChunk: public RiffChunk
{
public:
  bool Deserialize(BufferParser & bufferParser) override;
  bool Serialize(BufferSerializer & bufferSerializer) override;
private:
  // 0x4a554e4b = "JUNK"
  static const std::uint32_t CHUNK_ID = 0x4a554e4b;

  // Data fields
  std::uint8_t  dummyByte_ {0};
}; // JunkChunk

#endif // JUNKCHUNK_HPP_
