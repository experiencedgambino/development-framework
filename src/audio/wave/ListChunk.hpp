#ifndef LISTCHUNK_HPP_
#define LISTCHUNK_HPP_

#include "RiffChunk.hpp"

class ListChunk: public RiffChunk
{
public:
  bool Deserialize(BufferParser & bufferParser) override;
  bool Serialize(BufferSerializer & bufferSerializer) override;
private:
  // 0x4a554e4b = "LIST"
  static const std::uint32_t CHUNK_ID = 0x4c495354;

  // Data fields
  std::uint8_t  dummyByte_ {0};
}; // ListChunk

#endif // LISTCHUNK_HPP_
