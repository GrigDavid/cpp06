#ifndef DATA_HPP
#define DATA_HPP
#include <string>
class Data {
	public:
		Data();
		Data(const Data& other);
		Data& operator=(const Data& other);
		~Data();
		Data(int newValue, const std::string& newName);
		void setValue(int newValue);
		int getValue() const;
		std::string getName() const;
	private:
		int value;
		const std::string name;
};

#endif