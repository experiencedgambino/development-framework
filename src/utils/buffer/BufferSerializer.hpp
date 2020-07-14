#ifndef BUFFERSERIALIZER_HPP_
#define BUFFERSERIALIZER_HPP_

#include <cstdint>
#include <cstring>
#include <iostream>

class BufferSerializer
{
public:
  BufferSerializer(char * buffer, std::size_t size);

  template<typename T>
  void Set(const T & value);

  template<typename T>
  void Set(T * data, std::size_t size);

  std::size_t GetCurrentSize();

private: // Member variables
  char * buffer_;
  std::size_t size_;

  std::size_t bufferIndex_ {0};
}; // BufferSerializer

template<typename T>
void BufferSerializer::Set(const T & value)
{
  if (bufferIndex_ + sizeof(T) > size_)
  {
    std::cerr << "BufferParser - Next item reaches end of buffer" << std::endl;
  } // if
  else
  {
    *(reinterpret_cast<T*>(buffer_ + bufferIndex_)) = value;
    bufferIndex_ += sizeof(T);
  } // else
} // BufferSerializer

template<typename T>
void BufferSerializer::Set(T * data, std::size_t size)
{
  if (bufferIndex_ + (sizeof(T)*size) > size_)
  {
    std::cerr << "BufferParser - Next item reaches end of buffer" << std::endl;
  } // if
  else
  {
    std::memcpy(buffer_ + bufferIndex_, data, sizeof(T) * size);
    bufferIndex_ += sizeof(T) * size;
  } // else
} // Set

#endif // BUFFERSERIALIZER_HPP_
