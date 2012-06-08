template <class T>
inline SmartPtr<T>::SmartPtr() :
_data(NULL),
_nb_references(NULL)
{
}

template <class T>
inline SmartPtr<T>::SmartPtr(const SmartPtr<T> &other) :
_data(other._data),
_nb_references(other._nb_references)
{
    if (_nb_references)
        ++(*_nb_references);
}

template <class T>
inline SmartPtr<T>::SmartPtr(T *pointer) :
_data(pointer),
_nb_references(new int(1))
{

}
template <class T>
inline SmartPtr<T>::~SmartPtr()
{
    if (_nb_references && (!--(*_nb_references)))
    {
        delete _nb_references;
        delete _data;
    }
}

template <class T>
inline void SmartPtr<T>::Swap(SmartPtr<T> &other)
{
    std::swap(_data,    other._data);
    std::swap(_nb_references, other._nb_references);
}

template <class T>
inline T &SmartPtr<T>::operator*()
{
    Assert(_data != NULL);

    return *_data;
}

template <class T>
inline T* SmartPtr<T>::operator->()
{      
    Assert(_data != NULL);
    
    return _data;
}

template <class T>
inline const SmartPtr<T> &SmartPtr<T>::operator=(SmartPtr<T> pointer)	
{      
    Swap(pointer);	
    	
    return *this;
}	

template <class T>
inline SmartPtr<T>::operatorT*() const
{
    return _data;
}
