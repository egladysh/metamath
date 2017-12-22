#include <iostream>
#include "metamath/derivative.h"


using namespace metamath;

extern int fts();

int main()
{
	std::cout << "Metamath sample" << std::endl;

	{
		std::cout << "======" << std::endl;
		auto f = 3 * x;

		std::cout << "f(x) = " << f << std::endl;
		std::cout << "f(2) = " << f(2) << std::endl;
		std::cout << "f(3) = " << f(3) << std::endl;
		std::cout << "------" << std::endl;

		auto df = derivative(f);
		std::cout << "f`(x) = " << df << std::endl;
		std::cout << "f`(2) = " << df(2) << std::endl;
		std::cout << "======" << std::endl << std::endl;
	}

	{
		std::cout << "======" << std::endl;
		auto f =  (0.5 + 0.5) / x;

		std::cout << "f(x) = " << f << std::endl;
		std::cout << "f(2) = " << f(2) << std::endl;
		std::cout << "f(3) = " << f(3) << std::endl;
		std::cout << "------" << std::endl;

		auto df = derivative(f);
		std::cout << "f`(x) = " << df << std::endl;
		std::cout << "f`(2.f) = " << df(2) << std::endl;
		std::cout << "======" << std::endl << std::endl;
	}

	{
		std::cout << "======" << std::endl;
		auto f =  2 * (x + 1) / x;

		std::cout << "f(x) = " << f << std::endl;
		std::cout << "f(2) = " << f(2) << std::endl;
		std::cout << "f(3) = " << f(3) << std::endl;
		std::cout << "------" << std::endl;

		auto df = derivative(f);
		std::cout << "f`(x) = " << df << std::endl;
		std::cout << "f`(2) = " << df(2) << std::endl;
		std::cout << "======" << std::endl << std::endl;
	}

	{
		std::cout << "======" << std::endl;
		auto f =  4 * Sin(2 * x);

		std::cout << "f(x) = " << f << std::endl;
		std::cout << "f(pi) = " << f(M_PI) << std::endl;
		std::cout << "f(pi/4) = " << f(M_PI/4.f) << std::endl;
		std::cout << "------" << std::endl;

		auto df = derivative(f);
		std::cout << "f`(x) = " << df << std::endl;
		std::cout << "f`(pi) = " << df(M_PI) << std::endl;
		std::cout << "f`(pi/4) = " << df(M_PI/4.f) << std::endl;
		std::cout << "======" << std::endl << std::endl;
	}

	return 0;
}
