#include "BufferSerializer.hpp"

BufferSerializer::BufferSerializer(char * buffer, std::size_t size):
  buffer_(buffer),
  size_(size)
{
  buffer_ = buffer;
  size_ = size;
} // BufferParser

std::size_t BufferSerializer::GetCurrentSize()
{
  return bufferIndex_;
}
