#include "ScalarConverter.hpp"
#include <iostream>
#include <limits>
#include <cstdlib>

static void printConverted(const double& num)
{
	if (num < 0 || num > 255)
		std::cout << "char: Impossible\n";
	else if (std::isprint(num))
		std::cout << "char: \'" << static_cast<char>(num) << "\'\n";
	else if (num >= 0 && num < 256)
		std::cout << "char: Non displayable\n";

	if (num > std::numeric_limits<int>::max() || num < -std::numeric_limits<int>::max() - 1)
		std::cout << "int: Impossible\n";
	else
		std::cout << "int: " << static_cast<int>(num) << '\n';
	
	//set precision needed
	std::cout << "double: " << num << '\n';

	if (num > std::numeric_limits<float>::max() || num < -std::numeric_limits<float>::max())
		std::cout << "float: Impossible\n";
	else
		std::cout << "float: " << static_cast<float>(num) << std::endl;
}

static void printImpossible()
{
	std::cout << "char: Impossible\n"
	<< "int: Impossible\n"
	<< "double: Impossible\n"
	<< "float: Impossible" << std::endl;
}

static void isNum(const std::string& s)
{
	char *end;
	errno = 0;
	double num = std::strtod(s.c_str(), &end);
	if (errno == ERANGE)
	{
		printImpossible();
		return ;
	}
	if (*end && (*end != 'f' || *(end + 1)))
	{

		printImpossible();
		return ;
	}
	printConverted(num);
}

static void	printSpecial(const std::string& s)
{
	if (s == "+inf" || s == "+inff")
	{
		std::cout << "char: Impossible\n"
		<< "int: Impossible\n"
		<< "double: +inf\n"
		<< "float: +inff" << std::endl;
	}
	else if (s == "-inf" || s == "-inff")
	{
		std::cout << "char: Impossible\n"
		<< "int: Impossible\n"
		<< "double: -inf\n"
		<< "float: -inff" << std::endl;
	}
	else
	{
		std::cout << "char: Impossible\n"
		<< "int: Impossible\n"
		<< "double: nan\n"
		<< "float: nanf" << std::endl;
	}
}

void ScalarConverter::convert(const std::string& s)
{
	if (s.length() == 3 && s.at(0) == '\'' && s.at(2) == '\'')
		printConverted(static_cast<double>(s.at(1)));
	else if (s == "+inf" || s == "-inf" || s == "nan")
		printSpecial(s);
	else if (s == "+inff" || s == "-inff" || s == "nanf")
		printSpecial(s);
	else
		isNum(s);
}