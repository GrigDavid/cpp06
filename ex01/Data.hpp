#ifndef DATA_HPP
#define DATA_HPP
#include <string>
class Data {
	public:
		Data();
		Data(int newValue, const std::string& newName);
		Data(const Data& other);
		~Data();

		Data& operator=(const Data& other);

		void setValue(int newValue);
		int getValue() const;
		std::string getName() const;
	private:
		int value;
		const std::string name;
};

#endif