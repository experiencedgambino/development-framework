#include "ListChunk.hpp"

bool ListChunk::Deserialize(BufferParser & bufferParser)
{
  bool return_value {true};

  if (BufferParser::SwapEndian(bufferParser.Peek<std::uint32_t>()) == ListChunk::CHUNK_ID)
  {
    chunkIdentifier_ = bufferParser.Get<std::uint32_t>();
    chunkSize_ = bufferParser.Get<std::uint32_t>();

    if (chunkSize_ % 2 != 0)
    {
      // Add the pad byte
      //  only present if chunkSize is off number of bytes
      chunkSize_ += 1;
    } // if

    // At this moment, don't care about this field
    for (std::size_t chunk_byte_index = 0; chunk_byte_index < chunkSize_; ++chunk_byte_index)
    {
      dummyByte_ = bufferParser.Get<std::uint8_t>();
    } // for

  } // if
  else
  {
    // Chunk ID does not match
    return_value = false;
  } // else

  return return_value;
} // Deserialize

bool ListChunk::Serialize(BufferSerializer & bufferSerializer)
{
  bufferSerializer.Set<std::uint32_t>(BufferParser::SwapEndian(chunkIdentifier_));
  bufferSerializer.Set<std::uint32_t>(chunkSize_);

  // Rest of chunk is unknown at this time
  for (std::size_t chunk_byte_index = 0; chunk_byte_index < chunkSize_; ++chunk_byte_index)
  {
    bufferSerializer.Set<std::uint8_t>(0);
  } // for

  return true;
} // Serialize
