#include "AccumulatorNode.hpp"
#include "FileRecorderNode.hpp"
#include "FileReaderNode.hpp"
#include "PCMDevicePlayerNode.hpp"
#include "SignalUntilKill.hpp"

#include <iostream>


#define NUMBER_ARGS_REQUIRED 4
#define INPUT_FILE_ARG 1
#define OUTPUT_FILE_ARG 2
#define ACCUMULATOR_SIZE_ARG 3

int main(int argc, char ** argv)
{
  if (argc != NUMBER_ARGS_REQUIRED)
  {
    std::cout << "Usage: " << argv[0] << " [input file] [output file] [accumulator size]" << std::endl;
    return -1;
  } // if

  std::shared_ptr<Node> file_reader_node = std::make_shared<FileReaderNode>();
  std::shared_ptr<Node> accumulator_node = std::make_shared<AccumulatorNode>(atoi(argv[ACCUMULATOR_SIZE_ARG]));
  std::shared_ptr<Node> file_recorder_node = std::make_shared<FileRecorderNode>();

  std::dynamic_pointer_cast<FileReaderNode>(file_reader_node)->Initialize(argv[INPUT_FILE_ARG]);
  std::dynamic_pointer_cast<FileRecorderNode>(file_recorder_node)->Initialize(argv[OUTPUT_FILE_ARG]);

  file_reader_node->RegisterNodeAsNext(accumulator_node);
  accumulator_node->RegisterNodeAsNext(file_recorder_node);

  std::dynamic_pointer_cast<FileRecorderNode>(file_recorder_node)->Run();
  std::dynamic_pointer_cast<FileReaderNode>(file_reader_node)->Run();

  SignalUntilKill suk;
  suk.ReturnOnSignal();

  return 0;
} // main
