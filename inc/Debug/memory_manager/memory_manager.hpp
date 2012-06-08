/*
 * MemoryManager.h for DebugPurpose
 * by le-cor_w aka rexou
 */

#ifdef DEBUG
#ifndef __MEMORYMANAGER_HPP__
#define __MEMORYMANAGER_HPP__

#include <fstream>
#include <map>
#include <stack>
#include <string>

struct DataBlock
{
  std::size_t		size;		// Allocated size
  std::string		file;		// File where allocation has been made
  int			line;		// Line of allocation into file ^
  bool			is_array;	// bool to dispatch to new/new[] & delete/delete[]
};

typedef std::map<void*, DataBlock> DataBlockMap; // typedefing it for convenience

namespace Debug
{
  struct MemoryManager
  {
    static bool init(const std::string &);
    static void report_leaks();
    static void *allocate(std::size_t, const std::string &, int, bool);
    static void remove(const std::string &, int);
    static void free(void *, bool);
  };
}

inline void *operator new(std::size_t size, const char *__file__, int __line__)
{
  return Debug::MemoryManager::allocate(size, __file__, __line__, false);
}

inline void *operator new[](std::size_t size, const char *__file__, int __line__)
{
  return Debug::MemoryManager::allocate(size, __file__, __line__, true);
}

inline void operator delete(void *ptr)
{
  Debug::MemoryManager::free(ptr, false);
}

inline void operator delete(void *ptr, const char *__file__, int __line__)
{
  Debug::MemoryManager::remove(__file__, __line__);
  Debug::MemoryManager::free(ptr, false);
}

inline void operator delete[](void *ptr)
{
  Debug::MemoryManager::free(ptr, true);
}

inline void operator delete[](void *ptr, const char *__file__, int __line__)
{
  Debug::MemoryManager::remove(__file__, __line__);
  Debug::MemoryManager::free(ptr, true);
}

#ifndef new
	#define new	new(__FILE__, __LINE__)
	#define delete  Debug::MemoryManager::remove(__FILE__, __LINE__), delete
#endif // new

#endif // MemoryManager
#endif // DEBUG
