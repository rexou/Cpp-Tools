/*
 * file.hpp for Utilities
 * by le-cor_w aka rexou
 */

#ifndef __FILE_HPP__
# define __FILE_HPP__

#include <string>

namespace Utilities
{
  class File
  {
    std::string		_full_name;
    std::string		_base_name;
    std::string		_extension;

  public :

    // Ctors / Dtors

    File(const std::string& = "/dev/null");
    File(const char *);

    ~File();

    // Misc
    bool exists() const;

    const std::string &getFullName() const;
    const std::string &getBasename() const;
    const std::string &getExtension() const;
  };
}

#endif
