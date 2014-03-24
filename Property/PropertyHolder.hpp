#ifndef __PROPERTIES_HOLDER_HPP__
# define __PROPERTIES_HOLDER_HPP__

#include <unordered_map>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <typeinfo>

#include "Property.hpp"

/* 
    Templated Class holding saved properties
    Might be the base for our entities
*/
template <typename Key, bool ReplacingPolicy = true>
class PropertyHolder
{
    typedef std::unique_ptr<BaseProperty> PropertyPtr;

    std::unordered_map<Key, PropertyPtr> _properties;

public:

    template <typename T>
    void setValue(const Key &key, const T &value) {
        auto it = _properties.find(key);

        if (ReplacingPolicy || it == _properties.end()) 
        {
            std::unique_ptr<Property<T>> tmp(new Property<T>(key, value));

            _properties[key] = std::move(tmp);
        }
    }

    template <typename T>
    const T &getValue(const Key &key) const {
        auto it = _properties.find(key);

        if (it != _properties.end()) 
        {
            if (typeid(T).name() != it->second->getType())
                // should we throw an exception or assert(requested_type == real_type) ?
                throw std::invalid_argument("PropertyHolder::getValue<T>(const Key &) : Requested type T != Property's type" +
                                            "(requested \"" + Key + "\" as type " + typeid(T).name() + ")");

            Property<T> *tmp = reinterpret_cast<Property<T> *>(&*it->second);

            return tmp->getValue();
        }

        throw std::invalid_argument("PropertyHolder::getValue<T>(const Key &) : Key not found.");
    }

    bool hasKey(const Key &key) const {
        auto it = _properties.find(key);

        return (!(it == _properties.end()));
    }
};

#endif
