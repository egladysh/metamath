# metamath
Meta mathematic

metamath is a tiny header-only library. It can be used for symbolic calculations on single-variable functions.
The library could be useful for custom DSL's in C++.

It includes derivative calculations. The func.h header contains definitions for Sin/Cos functions. 

Example:

	using namespace metamath;

	auto f = 3 * x * x;

	std::cout << "f(x) = " << f << std::endl;
	std::cout << "f(4) = " << f(4.f) << std::endl;
	std::cout << "------" << std::endl;

	// take derivative
	auto df = derivative(f);
	std::cout << "f`(x) = " << df << std::endl;
	std::cout << "f`(4) = " << df(4.f) << std::endl;

This will produce the following output:

	f(x) = 3 * x * x
	f(4) = 48
	------
	f`(x) = ((0 * x + 3) * x + 3 * x)
	f`(4) = 24

Example:

	auto f =  4 * Sin(2 * x);

	std::cout << "f(x) = " << f << std::endl;
	std::cout << "f(pi) = " << f(M_PI) << std::endl;
	std::cout << "f(pi/4) = " << f(M_PI/4.f) << std::endl;
	std::cout << "------" << std::endl;

	//take derivative
	auto df = derivative(f);
	std::cout << "f`(x) = " << df << std::endl;
	std::cout << "f`(pi) = " << df(M_PI) << std::endl;
	std::cout << "f`(pi/4) = " << df(M_PI/4.f) << std::endl;

This will produce the following output:

	f(x) = 4 * sin(2 * x)
	f(pi) = 6.99382e-07
	f(pi/4) = 4
	------
	f`(x) = (0 * sin(2 * x) + 4 * cos(2 * x) * (0 * x + 2))
	f`(pi) = 8
	f`(pi/4) = -3.49691e-07

## Build

### Requirements
C++14 or later

### Steps to build the sample
* Suppose you cloned to [HOME]/work/metamath
* For out-of-source, create a build folder in [HOME]/work, and go there.

		$mkdir build
		$cd build

* Run cmake (make sure the build Release for speed).

		$cmake ../metamath

* Build it.     

		$make

* You can now run a sample (the sample source is in metamath/sample/)

		$./sample/mms
