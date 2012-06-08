/*
** singleton.hpp for Utilities
** by le-cor_w aka rexou
*/

#ifndef __SINGLETON_HPP__
# define __SINGLETON_HPP__

namespace Utilities
{
  template<typename T>
  class Singleton
  {
    Singleton(Singleton const&);
    Singleton &operator=(Singleton const&);

    static T *_inst;

  protected:
    Singleton() {}
    ~Singleton() {}

  public:
    static T *instance() {
      if (!_inst)
	_inst = new T;

      return _inst;
    }

    static void destroy() {
      if (!inst)
	return;

      delete _inst;
    }
  };

  template<typename T>
  T *Singleton<T>::_inst = 0;
}

#endif
