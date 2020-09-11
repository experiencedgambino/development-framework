#include "FileReaderNode.hpp"

FileReaderNode::FileReaderNode()
{

} // FileReaderNode

FileReaderNode::~FileReaderNode()
{
  inputFileStream_.close();
} // FileReaderNode

bool FileReaderNode::Initialize(const std::string & filename, std::size_t batchSize)
{
  bool return_value {true};
  batchSize_ = batchSize;

  inputFileStream_.open(filename, std::ifstream::in | std::ifstream::binary);

  if (!inputFileStream_)
  {
    std::cout << "FileReaderNode: Couldn't open " << filename << " for reading" << std::endl;
    return_value = false;
  } // if
  return return_value;
} // Initialize

void FileReaderNode::OnDataAvailable(std::shared_ptr<PipelineData> data)
{
  std::cout << "Not handling data. Start node" << std::endl;
} // OnDataAvailable

void FileReaderNode::RunThread(void)
{
  while (IsRunning() == true)
  {
    std::shared_ptr<PipelineData> new_data = std::make_shared<PipelineData>();
    new_data->buffer_.resize(batchSize_);
    inputFileStream_.read((char *) new_data->buffer_.data(), batchSize_);
    if (inputFileStream_)
    {
      // We all good!
    } // if
    else
    {
      std::cout << "Short read: " << inputFileStream_.gcount() << " chars read" << std::endl;
      new_data->buffer_.resize(inputFileStream_.gcount());
      DetachStop();
    } // else

    SendData(new_data);
  } // while
} // RunThread
