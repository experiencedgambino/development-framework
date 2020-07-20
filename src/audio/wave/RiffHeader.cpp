#include "RiffHeader.hpp"

bool RiffHeader::Deserialize(BufferParser & bufferParser)
{
  bool return_value {true};

  if (BufferParser::SwapEndian(bufferParser.Peek<std::uint32_t>()) == RiffHeader::CHUNK_ID)
  {
    chunkID_ = BufferParser::SwapEndian(bufferParser.Get<std::uint32_t>());
    restOfBufferSize_ = bufferParser.Get<std::uint32_t>();
    waveString_ = BufferParser::SwapEndian(bufferParser.Get<std::uint32_t>());

    return_value &= (waveString_ == RiffHeader::WAVE_STRING);
  } // if
  else
  {
    return_value = false;
  } // else

  return return_value;
} // IsCorrectChunk

bool RiffHeader::Serialize(BufferSerializer & bufferSerializer)
{
  bufferSerializer.Set<std::uint32_t>(BufferParser::SwapEndian(chunkID_));
  bufferSerializer.Set<std::uint32_t>(restOfBufferSize_);
  bufferSerializer.Set<std::uint32_t>(BufferParser::SwapEndian(waveString_));
  return true;
} // Serialize
