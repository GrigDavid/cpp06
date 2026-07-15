#include	"A.hpp"
#include	"B.hpp"
#include	"C.hpp"

#include <cstdlib>

Base * generate(void)
{
	int a = std::rand() % 3;
	if (a == 0)
		return (new A());
	else if (a == 1)
		return (new B());
	else
		return (new C());
}