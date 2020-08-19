#include "AccumulatorNode.hpp"
#include "FFTNode.hpp"
#include "FileRecorderNode.hpp"
#include "PCMDevicePlayerNode.hpp"
#include "SignalUntilKill.hpp"

#include <iostream>

int main()
{
  std::shared_ptr<Node> audio_player_node = std::make_shared<PCMDevicePlayerNode>();
  std::shared_ptr<Node> accumulator_node = std::make_shared<AccumulatorNode>(1024);
  std::shared_ptr<Node> fft_node = std::make_shared<FFTNode>(1024);
  std::shared_ptr<Node> file_recorder_node = std::make_shared<FileRecorderNode>();

  std::dynamic_pointer_cast<PCMDevicePlayerNode>(audio_player_node)->Initialize();
  std::dynamic_pointer_cast<FileRecorderNode>(file_recorder_node)->Initialize("out.audio.bin");

  audio_player_node->RegisterNodeAsNext(file_recorder_node);
  // accumulator_node->RegisterNodeAsNext(file_recorder_node);
  // fft_node->RegisterNodeAsNext(file_recorder_node);

  std::dynamic_pointer_cast<PCMDevicePlayerNode>(audio_player_node)->Run();
  // std::dynamic_pointer_cast<FFTNode>(fft_node)->Run();
  std::dynamic_pointer_cast<FileRecorderNode>(file_recorder_node)->Run();

  SignalUntilKill suk;
  suk.ReturnOnSignal();
} // main
