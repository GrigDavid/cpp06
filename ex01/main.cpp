#include "Data.hpp"
#include "Serialize.hpp"
#include <iostream>
int main() {
	Data* originalData = new Data();
	originalData->setValue(42);

	uintptr_t serializedData = Serialize::serialize(originalData);
	Data* deserializedData = Serialize::deserialize(serializedData);

	std::cout << "Original Data Value: " << originalData << std::endl;
	std::cout << "Deserialized Data Value: " << deserializedData << std::endl;

	delete originalData;
	return 0;
}