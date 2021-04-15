#include "rapidjson/document.h"
#include "FileReaderUtils_c.hpp"
#include <iostream>
 
using namespace rapidjson;
 

int main(int argc, char ** argv)
{
    if (argc != 2)
    {
        std::cout << "Need config file argument" << std::endl;
        return -1;
    } // 
    std::vector<std::string> vec;
    OpenFileAndReadLines(argv[1], vec);
    std::string str = "";
    for (auto line : vec)
    {
        str += "\n" + line;
    } // for
    rapidjson::Document document;
    document.Parse(str.c_str());
    assert(document.HasMember("hello"));
    std::cout << "Hello" << std::endl;
    assert(document.HasMember("hello1"));
    std::cout << "Hellor1" << std::endl;
    const rapidjson::Value& itemn = document["hello1"];
    std::cout << itemn["goodbye"].GetInt() << std::endl;

} // main

