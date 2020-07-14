#ifndef BUFFERPARSER_HPP_
#define BUFFERPARSER_HPP_

#include <cstdint>
#include <iostream>

class BufferParser
{
public:
  BufferParser(const char * buffer, std::size_t size);

  std::uint32_t GetUnsignedInt32(void);

  template<typename T>
  T Get(void);

  template<typename T>
  T Peek(void);

  template<typename T>
  T * Get(std::size_t size);

  std::size_t GetCurrentSize();

  static std::uint32_t SwapEndian(std::uint32_t data);
  static std::uint16_t SwapEndian(std::uint16_t data);


private:
  static const std::uint16_t UPPER_EIGHT_BITS_MASK;
  static const std::uint16_t LOWER_EIGHT_BITS_MASK;
  static const std::uint32_t FIRST_BYTE_INT_32;
  static const std::uint32_t SECOND_BYTE_INT_32;
  static const std::uint32_t THIRD_BYTE_INT_32;
  static const std::uint32_t FOURTH_BYTE_INT_32;

  static const std::uint16_t ONE_BYTE_SHIFT;
  static const std::uint16_t THREE_BYTE_SHIFT;

private: // Member variables
  const char * buffer_;
  std::size_t size_;

  std::size_t bufferIndex_ {0};
}; // BufferParser


template<typename T>
T BufferParser::Get(void)
{
  T return_value {0};

  if (bufferIndex_ + sizeof(T) > size_)
  {
    std::cerr << "BufferParser - Next item reaches end of buffer" << std::endl;
    return_value = 0;
  } // if
  else
  {
    return_value = *(reinterpret_cast<const T*>(buffer_+bufferIndex_));
    bufferIndex_ += sizeof(T);
  } // else

  return return_value;
} // Get

template<typename T>
T BufferParser::Peek(void)
{
  T return_value;

  if (bufferIndex_ + sizeof(T) > size_)
  {
    std::cerr << "BufferParser - Next item reaches end of buffer" << std::endl;
    return_value = 0;
  } // if
  else
  {
    return_value = *(reinterpret_cast<const T*>(buffer_+bufferIndex_));
  } // else

  return return_value;
}

template<typename T>
T * BufferParser::Get(std::size_t size)
{
  T * return_value = nullptr;

  if (bufferIndex_ + (sizeof(T)*size) > size_)
  {
    std::cerr << "BufferParser - Next item reaches end of buffer" << std::endl;
    return_value = 0;
  } // if
  else
  {
    return_value = (T *) (buffer_ + bufferIndex_);
    bufferIndex_ += size;
  } // else

  return return_value;
} // Get


#endif // BUFFERPARSER_HPP_
