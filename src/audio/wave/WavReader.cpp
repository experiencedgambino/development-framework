#include "WavReader.hpp"

const std::uint16_t WavReader::FOUR_BYTES = 4;
const std::uint16_t WavReader::TWO_BYTES = 2;

const std::uint16_t WavReader::SIXTEEN_BITS_PER_SAMPLE = 16;
const std::uint16_t WavReader::EIGHT_BITS_PER_SAMPLE = 8;


const std::uint16_t WavReader::SIXTEEN_BITS_PER_SAMPLE_VALUE_OFFSET = 2;

WavReader::WavReader():
    mInputFileStream(),
    mOutputFileStream(),
    mWavFileBuffer(),
    mBufferOffset(0),
    subchunk1_(),
    subchunk2_()
{
} // WavReader

WavReader::~WavReader()
{
} // ~WavReader

bool WavReader::Read(const std::string & wavfileName)
{
  bool return_value = true;

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
  // output << "RIFF: " << mWaveHeader.RIFF << std::endl;
  // output << "FMT des: " << mWaveHeader.WAVE << std::endl;
  output << "Subchunk 1 ID: " << subchunk1_.chunkIdentifier_ << std::endl;
  // output << "Subchunk 2 ID: " << subchunk2_.DATA << std::endl;
  output << "Format: " << subchunk1_.audioFormat_ << std::endl;
  output << "Num channels: " << subchunk1_.numChannels_ << std::endl;
  output << "BitsPerSample: " << subchunk1_.bitsPerSample_ << std::endl;
  output << "Samples: " << subchunk2_.chunkSize_ << std::endl;
  return;
} // GetStream

bool WavReader::Deserialize(void)
{
  BufferParser parser(reinterpret_cast<const char *>(mWavFileBuffer), length_of_file);

  if (riffHeader_.Deserialize(parser) == false)
  {
    std::cout << "Unable to parser riff header" << std::endl;
    return false;
  } // if

  if (junkchunk_.Deserialize(parser) == false)
  {
    foundJunk_ = false;
    std::cout << "INFO: Didn't find junk chunk" << std::endl;
  } // if
  else
  {
    foundJunk_ = true;
  } // else

  if (listchunk_.Deserialize(parser) == false)
  {
    foundList_ = false;
    std::cout << "INFO: Didn't find list chunk" << std::endl;
  } // if
  else
  {
    foundList_ = true;
  } // else

  if (subchunk1_.Deserialize(parser) == false)
  {
    std::cout << "Unable to parse subchunk 1" << std::endl;
  } // if

  if (subchunk2_.Deserialize(parser) == false)
  {
    std::cout << "Unable to parse subchunk 2" << std::endl;
  } // if

  mBufferOffset = parser.GetCurrentSize();

  return true;
} // Deserialize

std::uint32_t WavReader::Serialize(void)
{
  // Allocate buffer based on previous deserialize size
  mWavFileBuffer = (std::uint8_t *) malloc(mBufferOffset);

  BufferSerializer serializer(reinterpret_cast<char *>(mWavFileBuffer), mBufferOffset);

  // Wav File Header
  riffHeader_.Serialize(serializer);

  if (foundJunk_ == true)
  {
    junkchunk_.Serialize(serializer);
  } // if

  if (foundList_ == true)
  {
    listchunk_.Serialize(serializer);
  } // if
  subchunk1_.Serialize(serializer);
  subchunk2_.Serialize(serializer);

  return serializer.GetCurrentSize();
} // Serialize

std::int16_t WavReader::GetSample(const std::uint32_t & sampleNumber, const WavReader::Channel_e & channel) const
{
  if (subchunk1_.bitsPerSample_ == SIXTEEN_BITS_PER_SAMPLE)
  {
    return *(reinterpret_cast<std::int16_t *>(
              subchunk2_.data_ + SIXTEEN_BITS_PER_SAMPLE_VALUE_OFFSET*(sampleNumber*subchunk1_.numChannels_+channel)
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
    subchunk2_.data_ + SIXTEEN_BITS_PER_SAMPLE_VALUE_OFFSET*(sampleNumber*subchunk1_.numChannels_+channel)
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
  if ((subchunk1_.numChannels_ != 0) && (subchunk1_.bitsPerSample_ != 0))
  {
    return subchunk2_.chunkSize_ * 8 / (subchunk1_.numChannels_ * subchunk1_.bitsPerSample_);
  } // if
  else
  {
    return -1;
  } // else
} // GetChannelLength
