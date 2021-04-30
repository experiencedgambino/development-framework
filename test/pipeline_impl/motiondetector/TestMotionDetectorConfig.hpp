#include "FileReaderUtils_c.hpp"
#include "rapidjson/document.h"

class TestMotionDetectorConfig
{
public:
  TestMotionDetectorConfig()
  {

  }

  void ReadAndParse(const std::string & configPath)
  {
    std::string str;
    OpenFileAndReadIntoString(configPath, str);

    rapidjson::Document document;
    document.Parse(str.c_str());
    assert(document.HasMember("webcam"));

    use_webcam_ = document["webcam"].GetBool();

  }; //

  bool use_webcam_ {false};
}; // TestMotionDetectorConfig
