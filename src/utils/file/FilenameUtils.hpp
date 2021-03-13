#include <string>
#include <filesystem>

class FilenameUtils
{
public:
  static std::string GetNextAvailableFilename(const std::string & prefix, const std::string & extension = ".penis")
  {
    std::string return_string = prefix + extension;

    if (std::filesystem::exists(std::filesystem::path(return_string)) == true)
    {
      // Do nothing. Return string is good.
    }
    else
    {
      bool found_file = false;
      int index = 0;
      while (found_file == false)
      {
        // Build a new file path with the index
        return_string = prefix + "_" + std::to_string(index) + extension;
        if (std::filesystem::exists(std::filesystem::path(return_string)) == false)
        {
          // The file path does not exist. We have found the file.
          found_file = true;
        }
      }
    }

    return return_string;
  } // GetNextAvailableFilename
}; // FileUtils
