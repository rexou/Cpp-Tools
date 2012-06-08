#ifdef DEBUG
#ifndef __DEBUGNEW_HPP__
#define __DEBUGNEW_HPP__

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
#endif

#endif
#endif
