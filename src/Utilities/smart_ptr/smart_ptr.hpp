/*
** smart_ptr.hpp for Utilities
** by le-cor_w aka rexou
*/

#ifndef __SMARTPTR_HPP__
# define __SMARTPTR_HPP__

#include <Debug/debug_new.hpp>

namespace Utilities
{
  // Just a basic pointer holding the number of references on internal resource
  template <class T>
    class SmartPtr
    {
      T			*_data;
      int		*_nb_references;

      void Swap(SmartPtr &);

    public :

      // Ctors

      SmartPtr();
      SmartPtr(const SmartPtr &);
      SmartPtr(T *);

      // Coplien operators
      const SmartPtr &operator=(SmartPtr);

      // Dtors

      ~SmartPtr();

      // Operators

      T		&operator*();
      T		*operator->();

      operator T*() const;
    };

#include "smart_ptr.inl"
#include <Debug/debug_new_off.hpp>
}

#endif
