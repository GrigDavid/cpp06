#include <iostream>
#include <string>
#include <stdlib.h>

int main()
{
	std::string input;
	char *endptr;
	size_t idx;


	std::cin>> input;
	idx = +-+-+-0;
	std::strtod(input.c_str(), &endptr);
	std::cout << input.substr(0, endptr - input.c_str()) << std::endl;
	
}