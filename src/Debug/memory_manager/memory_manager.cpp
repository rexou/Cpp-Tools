/*
** static.cpp for Memory Manager Module
** by le-cor_w aka rexou
*/

#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "memory_manager.hpp"

static std::ofstream		_file;		// Output file for logging purpose
static DataBlockMap		_data_blocks;	// Data blocks allocated
static std::stack<DataBlock>	_delete_stack;	// Stack holding informations (line, file) about next element(s) about to be removed

namespace Debug
{
  bool MemoryManager::init(const std::string &filename)
  {
    _file.open(filename.c_str());

    if (!_file)
      return false;

    _file << "==========================" << std::endl;
    _file << "- Memory leaks tracker - " << std::endl;
    _file << "=========================" << std::endl << std::endl;

    return true;
  }

  void MemoryManager::report_leaks()
  {
    if (_data_blocks.empty())
      {
        // No leaks
        _file << std::endl;
        _file << "========================" << std::endl;
	_file << " - No leaks detected. - " << std::endl;
	_file << "========================" << std::endl;
      }
    else
      {
	// Leaks
	_file << std::endl;
	_file << " ========================================" << std::endl;
	_file << "  A few memory leaks have been detected  " << std::endl;
	_file << " ========================================" << std::endl;
	_file << std::endl;

	// details about leaks
	std::size_t TotalSize = 0;
	for (DataBlockMap::iterator i = _data_blocks.begin(); i != _data_blocks.end(); ++i)
	  {
	    // Adding current leak size to total
	    TotalSize += i->second.size;

	    // Logging current allocation block informations
	    _file << "-> 0x" << i->first
		  << " | "  << std::setw(7) << std::setfill(' ') << static_cast<int>(i->second.size) << " bytes"
		  << " | Allocated in file "  << i->second.file << " (at line " << i->second.line << ")" << std::endl;

	    // Freeing unfreed resources
	    ::free(i->first);
	  }

	// Logging total leaks' size
	_file << std::endl << "-- "
	      << static_cast<int>(_data_blocks.size()) << " non freed block(s), "
	      << static_cast<int>(TotalSize)    << " bytes --"
	      << std::endl;
      }
  }

  void *MemoryManager::allocate(std::size_t size, const std::string &file, int line, bool is_array)
  {
    // Memory allocation
    void *ptr = malloc(size);

    // setting new block members
    DataBlock new_block;

    new_block.size = size;
    new_block.file = file;
    new_block.line = line;
    new_block.is_array = is_array;

    // Adding pointer to DataBlockMap
    _data_blocks[ptr] = new_block;

    // Logging current allocation properties
    _file << "++ Allocation  | 0x" << ptr
	  << " | " << std::setw(7) << std::setfill(' ') << static_cast<int>(new_block.size) << " bytes"
	  << " | " << new_block.file << " (at line " << new_block.line << ")" << std::endl;

    return ptr;
  }

  void MemoryManager::free(void *ptr, bool is_array)
  {
    // Finding ptr in allocated/indexed blocks
    DataBlockMap::iterator it = _data_blocks.find(ptr);

    if (it == _data_blocks.end())
      {
	::free(ptr);
	return;
      }

    _file << "-- Deletion    | 0x" << ptr
	  << " | " << std::setw(7) << std::setfill(' ') << static_cast<int>(it->second.size) << " bytes"
	  << " | " << _delete_stack.top().file << " (at line " << _delete_stack.top().line << ")"
	  << (is_array ? " | Array" : "")
	  << std::endl;

    _data_blocks.erase(it);
    _delete_stack.pop();

    ::free(ptr);
  }

  void MemoryManager::remove(const std::string &file, int line)
  {
    DataBlock to_delete;

    to_delete.file = file;
    to_delete.line = line;

    _delete_stack.push(to_delete);
  }
}
