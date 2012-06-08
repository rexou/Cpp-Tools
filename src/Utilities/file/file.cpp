/*
** file.cpp for Utilities
** by le-cor_w aka rexou
*/

#include <algorithm>
#include <fstream>

#include "file.hpp"

namespace Utilities
{
  // Ctors / Dtors

  File::File(const std::string &filename) :
    _full_name(filename)
  {
    std::string::size_type pos = _full_name.find_last_of(".");

    _extension = (pos != std::string::npos ? _full_name.substr(pos + 1, std::string::npos) : "");

    pos = _full_name.find_last_of("/");
    _base_name = _full_name.substr(pos + 1);
    pos = _base_name.find_last_of(".");

    if (pos != std::string::npos)
      _base_name = _base_name.substr(0, pos);
  }

  File::File(const char *filename) :
    _full_name(filename)
  {
    std::string::size_type pos = _full_name.find_last_of(".");

    _extension = (pos != std::string::npos ? _full_name.substr(pos + 1, std::string::npos) : "");

    pos = _full_name.find_last_of("/");
    _base_name = _full_name.substr(pos + 1);
    pos = _base_name.find_last_of(".");

    if (pos != std::string::npos)
      _base_name = _base_name.substr(0, pos);
  }

  File::~File()
  {
  }

  // Getters

  const std::string& File::getFullName() const
  {
    return _full_name;
  }

  const std::string &File::getBasename() const
  {
    return _base_name;
  }

  const std::string &File::getExtension() const
  {
    return _extension;
  }

  // Misc

  bool File::exists() const
  {
    std::ifstream file(_full_name.c_str());

    return file.is_open();
  }
}
