#ifndef RIFF_CHUNK_HPP_
#define RIFF_CHUNK_HPP_

#include <cstdint>

#include "BufferParser.hpp"
#include "BufferSerializer.hpp"

class RiffChunk
{
public:
  virtual bool Deserialize(BufferParser & bufferParser) = 0;
  virtual bool Serialize(BufferSerializer & bufferSerializer) = 0;
public:
  std::uint32_t chunkIdentifier_ {0}; // Chunk type identifier
  std::uint32_t chunkSize_ {0}; // Chunk size field (size of ckData)
};

#endif // RIFF_CHUNK_HPP_
