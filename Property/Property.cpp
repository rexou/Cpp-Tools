#include <iostream>

#include "Property.hpp"

BaseProperty::BaseProperty(const std::string &type_name) :
	type(type_name)
{
}

const std::string &BaseProperty::getType() const {
	return type.getName();
}
