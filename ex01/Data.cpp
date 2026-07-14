#include "Data.hpp"

#include <cstring>

Data::Data() : value(0), name("Smith")
{
}

Data::Data(int newValue, const std::string& newName) : value(newValue), name(newName)
{
}

Data::Data(const Data& other) : value(other.value), name(other.name)
{
}

Data& Data::operator=(const Data& other)
{
	if (this != &other)
	{
		this->value = other.value;
	}
	return *this;
}

Data::~Data()
{
}

void Data::setValue(int newValue)
{
	this->value = newValue;
}

int Data::getValue() const
{
	return this->value;
}

std::string Data::getName() const
{
	return this->name;
}