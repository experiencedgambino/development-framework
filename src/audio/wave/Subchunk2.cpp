#include "Subchunk2.hpp"

Subchunk2::Subchunk2()
{
  data_ = (std::uint8_t *) malloc(1);
}

bool Subchunk2::Deserialize(BufferParser & bufferParser)
{
  bool return_value {true};

  if (BufferParser::SwapEndian(bufferParser.Peek<std::uint32_t>()) == Subchunk2::CHUNK_ID)
  {
    chunkIdentifier_ = BufferParser::SwapEndian(bufferParser.Get<std::uint32_t>());
    chunkSize_ = bufferParser.Get<std::uint32_t>();

    // Data fields
    // // Assume the data chunk has always been allocated
    free(data_);
    data_ = (std::uint8_t *) malloc (chunkSize_ * sizeof(std::uint8_t));
    std::memcpy(data_, bufferParser.Get<std::uint8_t>(chunkSize_), chunkSize_);
  } // if
  else
  {
    // Chunk ID does not match
    return_value = false;
  } // else

  return return_value;
} // Deserialize

bool Subchunk2::Serialize(BufferSerializer & bufferSerializer)
{
  bufferSerializer.Set<std::uint32_t>(BufferParser::SwapEndian(chunkIdentifier_));
  bufferSerializer.Set<std::uint32_t>(chunkSize_);

  bufferSerializer.Set<std::uint8_t>(data_, chunkSize_);

  return true;
} // Serialize
