#ifndef STRINGCONVERTER_HPP_
#define STRINGCONVERTER_HPP_

#include <stdexcept>
#include <string>
#include <sstream>

class StringConverter
{
public:
  template <typename T>
  static const T StringTo(const std::string& value)
  {
    T returnvalue;

    // Fill stringstream with value
    std::stringstream ss(value);

    // Try to populate return type with string
    ss >> returnvalue;
    if(ss.fail())
    {
      throw std::runtime_error((std::string)typeid(T).name() + " type wanted: " + value);
    } // if

    return returnvalue;
  } // StringTo

}; // StringConverter

#endif // STRINGCONVERTER_HPP_
