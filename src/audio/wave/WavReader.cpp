#include "WavReader.hpp"

const std::uint16_t WavReader::UPPER_EIGHT_BITS_MASK = 0xFF00;
const std::uint16_t WavReader::LOWER_EIGHT_BITS_MASK = 0x00FF;
const std::uint32_t WavReader::FIRST_BYTE_INT_32 = 0xFF000000;
const std::uint32_t WavReader::SECOND_BYTE_INT_32 = 0x00FF0000;
const std::uint32_t WavReader::THIRD_BYTE_INT_32 = 0x0000FF00;
const std::uint32_t WavReader::FOURTH_BYTE_INT_32 = 0x000000FF;

const std::uint16_t WavReader::ONE_BYTE_SHIFT = 8;
const std::uint16_t WavReader::TWO_BYTE_SHIFT = 16;
const std::uint16_t WavReader::THREE_BYTE_SHIFT = 24;

const std::uint16_t WavReader::FOUR_BYTES = 4;
const std::uint16_t WavReader::TWO_BYTES = 2;

const std::uint16_t WavReader::SIXTEEN_BITS_PER_SAMPLE = 16;
const std::uint16_t WavReader::EIGHT_BITS_PER_SAMPLE = 8;

const char WavReader::RIFF_VALIDATE_STRING[5] = "RIFF";
const char WavReader::WAVE_VALIDATE_STRING[5] = "WAVE";
const char WavReader::DATA_VALIDATE_STRING[5] = "DATA";
const char WavReader::FORMAT_VALIDATE_STRING[5] = "fmt ";

const std::uint16_t WavReader::SIXTEEN_BITS_PER_SAMPLE_VALUE_OFFSET = 2;

WavReader::WavReader():
    mInputFileStream(),
    mOutputFileStream(),
    mWavFileBuffer(),
    mBufferOffset(0),
    mSubchunk1(),
    mSubchunk2()
{
} // WavReader

WavReader::~WavReader()
{
} // ~WavReader

bool WavReader::Read(const std::string & wavfileName)
{
  bool return_value = true;
  std::uint32_t length_of_file;
  mInputFileStream.open(wavfileName.c_str(), std::ios::binary);
  if (mInputFileStream.good() == true)
  {
    // Move to the end of the file to get length
    mInputFileStream.seekg(0, std::ios::end);
    length_of_file = mInputFileStream.tellg();
    // Return to beginning of file to read
    mInputFileStream.seekg(0, std::ios::beg);

    // Read the file into buffer
    mWavFileBuffer = static_cast<uint8_t *>(malloc(length_of_file));
    mInputFileStream.read(reinterpret_cast<char *>(mWavFileBuffer), length_of_file);
    // Deserialize wav file
    return_value = Deserialize();
    free(mWavFileBuffer);
    // Deserialize wav file
    if (Validate() == false)
    {
      std::cout << "WavReader::"<<std::string(__func__)<<": Validate failed" << std::endl;
    } // if
  } // else
  else
  {
    std::cout << "WavReader::"<<std::string(__func__)<<": Failed to open wav file" << std::endl;
  } // else
  mInputFileStream.close();

  return return_value;
} // WavReader

bool WavReader::Write(const std::string & wavfileName)
{
  bool return_value = true;

  mOutputFileStream.open(wavfileName, std::ios::binary);
  if (mOutputFileStream.good() == true)
  {
    std::uint32_t bytes_to_serialize = Serialize();
    mOutputFileStream.write(reinterpret_cast<char *>(mWavFileBuffer), bytes_to_serialize);
    free(mWavFileBuffer);
  } // else
  mOutputFileStream.close();

  return return_value;
} // WavReader

void WavReader::GetStream(std::ostream & output) const
{
  // Pipe all output to stream
  output << ".....Wavefile...." << std::endl;
  output << "RIFF: " << mWaveHeader.RIFF << std::endl;
  output << "FMT des: " << mWaveHeader.WAVE << std::endl;
  output << "Subchunk 1 ID: " << mSubchunk1.mSubchunk1Id << std::endl;
  output << "Subchunk 2 ID: " << mSubchunk2.DATA << std::endl;
  output << "Format: " << mSubchunk1.mAudioFormat << std::endl;
  output << "Num channels: " << mSubchunk1.mNumChannels << std::endl;
  output << "BitsPerSample: " << mSubchunk1.mBitsPerSample << std::endl;
  output << "Samples: " << mSubchunk2.mSubchunk2Size << std::endl;
  return;
} // GetStream

bool WavReader::Deserialize(void)
{
  // Reset offset at beginning
  mBufferOffset = 0;

  // Wave file header
  std::memcpy ( mWaveHeader.RIFF, mWavFileBuffer+mBufferOffset, FOUR_BYTES);
  mBufferOffset+=FOUR_BYTES;
  mWaveHeader.mChunkSize = SwapEndian(*(reinterpret_cast<std::uint32_t *>(mWavFileBuffer+mBufferOffset)));
  mBufferOffset+=FOUR_BYTES;
  std::memcpy( mWaveHeader.WAVE, mWavFileBuffer+mBufferOffset, FOUR_BYTES);
  mBufferOffset+=FOUR_BYTES;

  // Subchunk 1: Format
  std::memcpy ( mSubchunk1.mSubchunk1Id, mWavFileBuffer+mBufferOffset, FOUR_BYTES);
  mBufferOffset+=FOUR_BYTES;
  mSubchunk1.mSubchunk1Size = *(reinterpret_cast<std::uint32_t *>(mWavFileBuffer+mBufferOffset));
  mBufferOffset+=FOUR_BYTES;
  mSubchunk1.mAudioFormat = *(reinterpret_cast<std::uint16_t *>(mWavFileBuffer+mBufferOffset));
  mBufferOffset+=TWO_BYTES;
  mSubchunk1.mNumChannels = *(reinterpret_cast<std::uint16_t *>(mWavFileBuffer+mBufferOffset));
  mBufferOffset+=TWO_BYTES;
  mSubchunk1.mSampleRate = *(reinterpret_cast<std::uint32_t *>(mWavFileBuffer+mBufferOffset));
  mBufferOffset+=FOUR_BYTES;
  mSubchunk1.mByteRate = *(reinterpret_cast<std::uint32_t *>(mWavFileBuffer+mBufferOffset));
  mBufferOffset+=FOUR_BYTES;
  mSubchunk1.mBlockAlign = *(reinterpret_cast<std::uint16_t *>(mWavFileBuffer+mBufferOffset));
  mBufferOffset+=TWO_BYTES;
  mSubchunk1.mBitsPerSample = *(reinterpret_cast<std::uint16_t *>(mWavFileBuffer+mBufferOffset));
  mBufferOffset+=TWO_BYTES;

  // Subchunk 2: Data
  std::memcpy ( mSubchunk2.DATA, mWavFileBuffer+mBufferOffset, FOUR_BYTES);
  mBufferOffset+=FOUR_BYTES;
  mSubchunk2.mSubchunk2Size = *(reinterpret_cast<std::uint32_t *>(mWavFileBuffer+mBufferOffset));
  mBufferOffset+=FOUR_BYTES;
  // Allocate the data chunk
  free(mSubchunk2.mData);
  mSubchunk2.mData = (std::uint8_t *) malloc (mSubchunk2.mSubchunk2Size * sizeof(std::uint8_t));
  std::memcpy( mSubchunk2.mData, mWavFileBuffer+mBufferOffset, mSubchunk2.mSubchunk2Size);
  mBufferOffset+=mSubchunk2.mSubchunk2Size;

  return true;
} // Deserialize

std::uint32_t WavReader::Serialize(void)
{
  mSerializedByteIndex = 0;

  // Allocate buffer based on previous deserialize size
  mWavFileBuffer = (std::uint8_t *) malloc(mBufferOffset);

  // Wav File Header
  std::memcpy ( mWavFileBuffer+mSerializedByteIndex, (std::uint8_t *) mWaveHeader.RIFF, FOUR_BYTES);
  mSerializedByteIndex+=FOUR_BYTES;
  *(reinterpret_cast<std::uint32_t *>(mWavFileBuffer+mSerializedByteIndex)) = SwapEndian(mWaveHeader.mChunkSize);
  mSerializedByteIndex+=FOUR_BYTES;
  std::memcpy ( mWavFileBuffer+mSerializedByteIndex, (std::uint8_t *) mWaveHeader.WAVE, FOUR_BYTES);
  mSerializedByteIndex+=FOUR_BYTES;

  // Subchunk 1: Format
  std::memcpy ( mWavFileBuffer+mSerializedByteIndex, (std::uint8_t *) mSubchunk1.mSubchunk1Id, FOUR_BYTES);
  mSerializedByteIndex+=FOUR_BYTES;
  *(reinterpret_cast<std::uint32_t *>(mWavFileBuffer+mSerializedByteIndex)) = mSubchunk1.mSubchunk1Size;
  mSerializedByteIndex+=FOUR_BYTES;
  *(reinterpret_cast<std::uint16_t *>(mWavFileBuffer+mSerializedByteIndex)) = mSubchunk1.mAudioFormat;
  mSerializedByteIndex+=TWO_BYTES;
  *(reinterpret_cast<std::uint16_t *>(mWavFileBuffer+mSerializedByteIndex)) = mSubchunk1.mNumChannels;
  mSerializedByteIndex+=TWO_BYTES;
  *(reinterpret_cast<std::uint32_t *>(mWavFileBuffer+mSerializedByteIndex)) = mSubchunk1.mSampleRate;
  mSerializedByteIndex+=FOUR_BYTES;
  *(reinterpret_cast<std::uint32_t *>(mWavFileBuffer+mSerializedByteIndex)) = mSubchunk1.mByteRate;
  mSerializedByteIndex+=FOUR_BYTES;
  *(reinterpret_cast<std::uint16_t *>(mWavFileBuffer+mSerializedByteIndex)) = mSubchunk1.mBlockAlign;
  mSerializedByteIndex+=TWO_BYTES;
  *(reinterpret_cast<std::uint16_t *>(mWavFileBuffer+mSerializedByteIndex)) = mSubchunk1.mBitsPerSample;
  mSerializedByteIndex+=TWO_BYTES;

  // Subchunk 2: Data
  std::memcpy ( mWavFileBuffer+mSerializedByteIndex, (std::uint8_t *) mSubchunk2.DATA, FOUR_BYTES);
  mSerializedByteIndex+=FOUR_BYTES;
  *(reinterpret_cast<std::uint32_t *>(mWavFileBuffer+mSerializedByteIndex)) = mSubchunk2.mSubchunk2Size;
  mSerializedByteIndex+=FOUR_BYTES;
  std::memcpy( mWavFileBuffer+mSerializedByteIndex, (std::uint8_t *)  mSubchunk2.mData, mSubchunk2.mSubchunk2Size);
  mSerializedByteIndex+=mSubchunk2.mSubchunk2Size;

  return mSerializedByteIndex;
} // Serialize

bool WavReader::Validate(void)
{
  bool return_value = true;
  if (memcmp( mWaveHeader.RIFF, RIFF_VALIDATE_STRING, 4) != 0)
  {
    return_value = false;
  } // else
  if (memcmp( mSubchunk2.DATA, DATA_VALIDATE_STRING, 4) != 0)
  {
    return_value = false;
  } // else
  if (memcmp( mSubchunk1.mSubchunk1Id, FORMAT_VALIDATE_STRING, 4) != 0)
  {
    return_value = false;
  } // if
  if (memcmp( mWaveHeader.WAVE, WAVE_VALIDATE_STRING, 4) != 0)
  {
    return_value = false;
  } // if
  return return_value;
} // Validate

std::uint16_t WavReader::SwapEndian(const std::uint16_t & num)
{
  return ((num << ONE_BYTE_SHIFT) & UPPER_EIGHT_BITS_MASK) | ((num >> ONE_BYTE_SHIFT) & LOWER_EIGHT_BITS_MASK);
} // LittleToBigEndian

std::uint32_t WavReader::SwapEndian(const std::uint32_t & num)
{
  return ((num << THREE_BYTE_SHIFT) & FIRST_BYTE_INT_32)   |
         ((num << TWO_BYTE_SHIFT)   & SECOND_BYTE_INT_32)  |
         ((num << ONE_BYTE_SHIFT)   & THIRD_BYTE_INT_32)   |
       ((num)			          & FOURTH_BYTE_INT_32);
} // LittleToBigEndian

std::int16_t WavReader::GetSample(const std::uint32_t & sampleNumber, const WavReader::Channel_e & channel) const
{
  if (mSubchunk1.mBitsPerSample == SIXTEEN_BITS_PER_SAMPLE)
  {
    return *(reinterpret_cast<std::int16_t *>(
              mSubchunk2.mData + SIXTEEN_BITS_PER_SAMPLE_VALUE_OFFSET*(sampleNumber*mSubchunk1.mNumChannels+channel)
          ));
  } // if
  else
  {
    return 0;
  } // else
} // GetSample

std::int16_t WavReader::GetSample(const std::uint32_t & sampleNumber) const
{
  return GetSample(sampleNumber, WavReader::Channel_e::CHANNEL_ONE); // Get channel 1 sample
} // GetSample

void WavReader::SetSample(const std::uint32_t & sampleNumber, const WavReader::Channel_e & channel, const std::int16_t & value)
{
  *(reinterpret_cast<std::int16_t *>(
    mSubchunk2.mData + SIXTEEN_BITS_PER_SAMPLE_VALUE_OFFSET*(sampleNumber*mSubchunk1.mNumChannels+channel)
   )) = value;
  return;
} // SetSample

void WavReader::SetSample(const std::uint32_t & sampleNumber, const std::int16_t & value)
{
  SetSample(sampleNumber, WavReader::Channel_e::CHANNEL_ONE, value);
  return;
} // SetSample

std::uint32_t WavReader::DataSize(void)
{
  if ((mSubchunk1.mNumChannels != 0) && (mSubchunk1.mBitsPerSample != 0))
  {
    return mSubchunk2.mSubchunk2Size * 8 / (mSubchunk1.mNumChannels * mSubchunk1.mBitsPerSample);
  } // if
  else
  {
    return -1;
  } // else
} // GetChannelLength
