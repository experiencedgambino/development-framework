add_executable(TestReceiver TestReceiver.cpp)
target_link_libraries(TestReceiver sockets)
target_link_libraries(TestReceiver argparser)

add_executable(TestSender TestSender.cpp)
target_link_libraries(TestSender sockets)
target_link_libraries(TestSender argparser)
