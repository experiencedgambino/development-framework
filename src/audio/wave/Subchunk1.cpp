#include "Subchunk1.hpp"


bool Subchunk1::Deserialize(BufferParser & bufferParser)
{
  bool return_value {true};

  if (BufferParser::SwapEndian(bufferParser.Peek<std::uint32_t>()) == Subchunk1::CHUNK_ID)
  {
    chunkIdentifier_ = BufferParser::SwapEndian(bufferParser.Get<std::uint32_t>());
    chunkSize_ = bufferParser.Get<std::uint32_t>();

    // Data fields
    audioFormat_ = bufferParser.Get<std::uint16_t>();
    numChannels_ = bufferParser.Get<std::uint16_t>();
    sampleRate_ = bufferParser.Get<std::uint32_t>();
    byteRate_ = bufferParser.Get<std::uint32_t>();
    blockAlign_ = bufferParser.Get<std::uint16_t>();
    bitsPerSample_ = bufferParser.Get<std::uint16_t>();

    // Occasionally dummy byte exists here.
    //  normal size is 16
    if (chunkSize_ == 18)
    {
      std::uint16_t dummy_byte = bufferParser.Get<std::uint16_t>();
    } // if
  } // if
  else
  {
    // Chunk ID does not match
    return_value = false;
  } // else

  return return_value;
} // Deserialize

bool Subchunk1::Serialize(BufferSerializer & bufferSerializer)
{
  bufferSerializer.Set<std::uint32_t>(BufferParser::SwapEndian(chunkIdentifier_));
  bufferSerializer.Set<std::uint32_t>(chunkSize_);

  bufferSerializer.Set<std::uint16_t>(audioFormat_);
  bufferSerializer.Set<std::uint16_t>(numChannels_);
  bufferSerializer.Set<std::uint32_t>(sampleRate_);
  bufferSerializer.Set<std::uint32_t>(byteRate_);
  bufferSerializer.Set<std::uint16_t>(blockAlign_);
  bufferSerializer.Set<std::uint16_t>(bitsPerSample_);

  if (chunkSize_ == 18)
  {
    bufferSerializer.Set<std::uint16_t>(0);
  } // if

  return true;
} // Serialize
