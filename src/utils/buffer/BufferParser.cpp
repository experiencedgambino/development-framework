#include "BufferParser.hpp"

const std::uint16_t BufferParser::UPPER_EIGHT_BITS_MASK = 0xFF00;
const std::uint16_t BufferParser::LOWER_EIGHT_BITS_MASK = 0x00FF;
const std::uint32_t BufferParser::FIRST_BYTE_INT_32 = 0xFF000000;
const std::uint32_t BufferParser::SECOND_BYTE_INT_32 = 0x00FF0000;
const std::uint32_t BufferParser::THIRD_BYTE_INT_32 = 0x0000FF00;
const std::uint32_t BufferParser::FOURTH_BYTE_INT_32 = 0x000000FF;

const std::uint16_t BufferParser::ONE_BYTE_SHIFT = 8;
const std::uint16_t BufferParser::THREE_BYTE_SHIFT = 24;

BufferParser::BufferParser(const char * buffer, std::size_t size):
  buffer_(buffer),
  size_(size)
{
  buffer_ = buffer;
  size_ = size;
} // BufferParser

std::size_t BufferParser::GetCurrentSize()
{
  return bufferIndex_;
} // GetCurrentSize

std::uint32_t BufferParser::SwapEndian(std::uint32_t data)
{
  return ((data << THREE_BYTE_SHIFT) & FIRST_BYTE_INT_32)   |
         ((data << ONE_BYTE_SHIFT)   & SECOND_BYTE_INT_32)  |
         ((data >> ONE_BYTE_SHIFT)   & THIRD_BYTE_INT_32)   |
         ((data >> THREE_BYTE_SHIFT) & FOURTH_BYTE_INT_32);
} // SwapEndian

std::uint16_t BufferParser::SwapEndian(std::uint16_t data)
{
  return ((data << ONE_BYTE_SHIFT) & UPPER_EIGHT_BITS_MASK) |
         ((data >> ONE_BYTE_SHIFT) & LOWER_EIGHT_BITS_MASK);
} // SwapEndian
