#include	"A.hpp"
#include	"B.hpp"
#include	"C.hpp"
#include <cstdlib>
#include <ctime>

Base * generate(void);
void identify(Base* p);
void identify(Base& p);

int main()
{
	std::srand(std::time(NULL));
	Base *p = generate();
	identify(p);
	identify(*p);

	delete p;
	return (0);
}