#include "HexPrinterNode.hpp"
#include "SignalUntilKill.hpp"
#include "UdpReceiverNode.hpp"

int main()
{
  std::shared_ptr<Node> hex_printer_node = std::make_shared<HexPrinterNode>();
  std::shared_ptr<Node> udp_receiver_node = std::make_shared<UdpReceiverNode>();

  std::dynamic_pointer_cast<UdpReceiverNode>(udp_receiver_node)->Initialize("127.0.0.1", 19000);
  std::dynamic_pointer_cast<UdpReceiverNode>(udp_receiver_node)->Run();
  std::dynamic_pointer_cast<HexPrinterNode>(hex_printer_node)->Run();
  udp_receiver_node->RegisterNodeAsNext(hex_printer_node);

  SignalUntilKill suk;
  suk.ReturnOnSignal();
} // main
