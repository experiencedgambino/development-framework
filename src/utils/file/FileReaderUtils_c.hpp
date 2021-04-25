#ifndef FILEREADERUTILS_C_HPP
#define FILEREADERUTILS_C_HPP

#include <fstream>
#include <iostream>
#include <vector>

static inline void OpenFileAndReadLines(const std::string & filename, std::vector<std::string> & vec)
{
    vec.clear();
    std::ifstream input_file;
    input_file.open(filename, std::ios::in);

    if (input_file.is_open() == true)
    {
        std::string tp;
        while(getline(input_file, tp))
        {
            vec.push_back(tp);
        } // while
        input_file.close();
    } // if
    else
    {
        std::cout << "Failed to open file" << std::endl;
    } // else
} // OpenFileAndReadLines

static inline void OpenFileAndReadIntoString(const std::string & filename, std::string & str)
{
    std::ifstream input_file;
    input_file.open(filename, std::ios::in | std::ios::binary);
    if (input_file.is_open() == true)
    {
        input_file.seekg(0, std::ios::end);
        std::size_t file_size = input_file.tellg();
        input_file.seekg(0, std::ios::beg);

        str.resize(file_size);
        input_file.read(str.data(), file_size);
        input_file.close();
    } // if
    else
    {
        std::cout << "Failed to open file" << std::endl;
    } // else
} // OpenFileAndReadLines

#endif // FILEREADERUTILS_C_HPP
