#ifndef __PROPERTY_HPP__
# define __PROPERTY_HPP__

#include <string>
#include <typeinfo>

class BaseProperty
{

public:

    // Right now, Type is just a string so kinda useless, might contain more informations later
    class Type
    {
        std::string type_name;

        public:

        Type(const std::string &name) :
            type_name(name)
        {
        }

        const std::string &getName() const {
            return (type_name);
        }
    };

    BaseProperty(const std::string &);

    const std::string &getType() const;

    private:

    Type        type;
    std::string key;
};

template <typename T = int>
class Property : public BaseProperty
{
    T		_value;

public:

    Property(const std::string &key, const T &value) :
        BaseProperty(typeid(T).name()),
        _value(value)
    {
    }

    const T &getValue() const {
        return _value;
    }

    void setValue(const T &value) {
        _value = value;
    }
};

#endif
