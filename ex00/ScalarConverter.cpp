#include "ScalarConverter.hpp"
#include <string>
#include <iostream>
#include <limits>
#include <cerrno>

bool isSpecial(const std::string& literal)
{
	return (literal == "+inf" || literal == "-inf" || literal == "nan" || literal == "+inff" || literal == "-inff" || literal == "nanf");
}

bool isChar(const std::string& literal)
{
	return (literal.length() == 3 && literal.at(0) == '\'' && literal.at(2) == '\'' && std::isprint(literal.at(1)));
}

bool isNum(const std::string& literal, int len)
{
	int	i = 0;

	if (len < 3)
		return (false);
	if (literal.at(0) == '-' || literal.at(0) == '+')
		i++;
	while (i < len && literal.at(i) != '.')
	{
		if (!std::isdigit(literal.at(i)))
			return (false);
		i++;
	}
	if (i == len)
		return (false);
	if (literal.at(i) == '.')
		i++;
	if (i == len)
		return (false);
	while (i < len)
	{
		if (!std::isdigit(literal.at(i)))
			return (false);
		i++;
	}
	return (true);
}

bool isDouble(const std::string& literal)
{
	return (isNum(literal, literal.length()));
}

bool isFloat(const std::string& literal)
{
	return (isNum(literal, literal.length() - 1) && literal.back() == 'f');
}

bool isInt(const std::string& literal)
{
	int i = 0;
	int len = literal.length();
	if (literal.at(0) == '-' || literal.at(0) == '+')
		i++;
	if (i == len || len - i > 10)
		return (false);
	if (len - i == 10)
	{
		if (literal.at(0) == '+' && literal.compare(i, len - i, "2147483647") > 0)
			return (false);
		else if (literal.at(0) == '-' && literal.compare(i, len - i, "2147483648") > 0)
			return (false);
	}
	
	while (i < len){
		if (!std::isdigit(literal.at(i)))
			return (false);
		i++;
	}
	return (true);
}

void printChar(double num)
{
	std::cout << "char: ";
	if (num < 0 || num > 127)
		std::cout << "impossible";
	else if (std::isprint(static_cast<int>(num)))
		std::cout << static_cast<char>(num);
	else
		std::cout << "Non displayable";
}

void ScalarConverter::convert(const std::string& literal)
{
	double num;

	if (literal.empty())
	{
		std::cout << "char: Non displayable\nint: Nondisplayable\nfloat: Nondisplayable\ndouble: Nondisplayable" << std::endl;
		return ;
	}
	if (isChar(literal))
	{
		std::cout << "char: " << literal.at(1);
		std::cout << "\nint: " << static_cast<int>(literal.at(1));
		std::cout << "\nfloat: " << static_cast<float>(literal.at(1));
		std::cout << "\ndouble: " << static_cast<double>(literal.at(1)) << std::endl;
		return ;
	}
	if (isSpecial(literal))
	{
		if (literal == "+inf" || literal == "-inf" || literal == "nan")
			std::cout << "char: Non displayable\n" << "int: Nondisplayable\n" << "float: " << literal << "f\ndouble: " << literal << std::endl;
		else
			std::cout << "char: Non displayable\n" << "int: Nondisplayable\n" << "float: " << literal << "f\ndouble: " << literal.substr(0, literal.length() - 1) << std::endl;
		return ;
	}
	errno = 0;
	num = std::strtod(literal.c_str(), NULL);
	if (errno == ERANGE)
	{
		std::cout << "char: Non displayable\nint: Nondisplayable\nfloat: Nondisplayable\ndouble: Nondisplayable" << std::endl;
		return ;
	}
	if (isInt(literal))
	{
		std::cout << "char: ";
		if (num >= 0 && num <= 127 && std::isprint(static_cast<int>(num)))
			std::cout << static_cast<char>(num);
		else
			std::cout << "char: Non displayable";
		std::cout << "\nint: " << literal;
		std::cout << "\nfloat: " << static_cast<float>(num);
		std::cout << "\ndouble: " << num << std::endl;
		return ;
	}
	if (isFloat(literal))
	{
		num = std::strtod(literal.c_str(), NULL);
		std::cout << "char: ";
		if (num >= 0 && num <= 127 && std::isprint(static_cast<int>(num)))
			std::cout << static_cast<char>(num);
		else
			std::cout << "char: Non displayable";
		std::cout << "\nint: ";
		if (num > std::numeric_limits<int>::max() || num < std::numeric_limits<int>::lowest())
			std::cout << "Non displayable";
		else
			std::cout << static_cast<int>(num);
		std::cout << "\nfloat: " << literal;
		std::cout << "\ndouble: " << num << std::endl;
		return ;
	}
	if (isDouble(literal))
	{
		num = std::strtod(literal.c_str(), NULL);
		std::cout << "char: ";
		if (num >= 0 && num <= 127 && std::isprint(static_cast<int>(num)))
			std::cout << static_cast<char>(num);
		else
			std::cout << "char: Non displayable";
		std::cout << "\nint: ";
		if (num > std::numeric_limits<int>::max() || num < std::numeric_limits<int>::lowest())
			std::cout << "Non displayable";
		else
			std::cout << static_cast<int>(num);
		std::cout << "\nfloat: ";
		if (num > std::numeric_limits<float>::max() || num < std::numeric_limits<float>::lowest())
			std::cout << "Non displayable";
		else
			std::cout << static_cast<float>(num);
		std::cout << "\ndouble: " << literal << std::endl;
		return ;
	}
	std::cout << "char: Non displayable\nint: Nondisplayable\nfloat: Nondisplayable\ndouble: Nondisplayable" << std::endl;
}






/*

is special ---------------- +-inf, nan
	char ---------------- impossible
	int  ---------------- impossible
	float --------------- +-inff, nanf
	double -------------- +-inf, nan

is num     ---------------- double, int, float
	convert to double, cast to 
	char ---------------- char if printable, impossible if not
	int ----------------- cast-to-int
	float --------------- cast-to-float
	double -------------- double

is char    ---------------- printable chars without '0' to '9'
	char ---------------- char
	int ----------------- cast-to-int
	float --------------- cast-to-int.0f
	double -------------- cast-to-int.0

*/