#include "ScalarConverter.hpp"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <cerrno>
#include <iomanip>
#include <sstream>


int calcPrec(const std::string& s)
{
	size_t dotPos = s.find('.');
	if (dotPos == std::string::npos)
		return (1);
	size_t endPos = s.length() - 1;
	if (s.at(endPos) == 'f')
		endPos--;
	size_t lastDigitPos = s.find_last_not_of('0', endPos);
	if (lastDigitPos == std::string::npos)
		return (1);
	if (lastDigitPos <= dotPos)
		return (1);
	return (lastDigitPos - dotPos);
}

int calcPrec(float n, int oldprec)
{
	std::ostringstream strm;
	strm << std::fixed << std::setprecision(oldprec) << n;
	std::string str = strm.str();
	return (calcPrec(str));
}

static void printConverted(const double& num, int prec = 1)
{
	if (num < 0 || num > 255)
		std::cout << "char: Impossible\n";
	else if (std::isprint(static_cast<unsigned char>(num)))
		std::cout << "char: \'" << static_cast<char>(num) << "\'\n";
	else if (num >= 0 && num < 256)
		std::cout << "char: Non displayable\n";

	if (num > std::numeric_limits<int>::max() || num < -std::numeric_limits<int>::max() - 1)
		std::cout << "int: Impossible\n";
	else
		std::cout << "int: " << static_cast<int>(num) << '\n';

	if (num > std::numeric_limits<float>::max() || num < -std::numeric_limits<float>::max())
		std::cout << "float: Impossible\n";
	else
		std::cout << "float: " << std::fixed << std::setprecision(calcPrec(static_cast<float>(num), prec)) << static_cast<float>(num) << "f\n";	

	std::cout << "double: " << std::fixed << std::setprecision(prec) << num << std::endl;
}

static void printImpossible()
{
	std::cout << "char: Impossible\n"
	<< "int: Impossible\n"
	<< "float: Impossible\n"
	<< "double: Impossible" << std::endl;
}

bool wrongNotation(const std::string& s)
{
	for (size_t i = 0; i < s.length(); i++)
	{
		if (!std::isdigit(s.at(i)) && s.at(i) != '.' && s.at(i) != 'f' && s.at(i) != '-')
		{
			return (true);
		}
	}
	if (s.at(0) == '+' || s.at(0) == '.')
		return (true);
	size_t dotPos = s.find('.');
	if (dotPos == std::string::npos)
		return (false);
	else if (dotPos + 1 >= s.length() || !std::isdigit(s.at(dotPos + 1)))
		return (true);
	return (false);
}

static void isNum(const std::string& s)
{
	if (wrongNotation(s))
	{
		printImpossible();
		return ;
	}
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
	printConverted(num, calcPrec(s));
}

static void	printSpecial(const std::string& s)
{
	if (s == "+inf" || s == "+inff")
	{
		std::cout << "char: Impossible\n"
		<< "int: Impossible\n"
		<< "float: +inff\n"
		<< "double: +inf" << std::endl;
	}
	else if (s == "-inf" || s == "-inff")
	{
		std::cout << "char: Impossible\n"
		<< "int: Impossible\n"
		<< "float: -inff\n"
		<< "double: -inf" << std::endl;
	}
	else
	{
		std::cout << "char: Impossible\n"
		<< "int: Impossible\n"
		<< "float: nanf\n"
		<< "double: nan" << std::endl;
	}
}

void ScalarConverter::convert(const std::string& s)
{
	if (s.empty())
		printImpossible();
	else if (s.length() == 1)
		printConverted(static_cast<double>(s.at(0)));
	else if (s.length() == 3 && s.at(0) == '\'' && s.at(2) == '\'')
		printConverted(static_cast<double>(s.at(1)));
	else if (s == "+inf" || s == "-inf" || s == "nan")
		printSpecial(s);
	else if (s == "+inff" || s == "-inff" || s == "nanf")
		printSpecial(s);
	else
		isNum(s);
}