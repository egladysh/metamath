# metamath
Meta mathematic

metamath is a tiny header-only library. It can be used for symbolic computations on single-variable functions, such as dynamic computations of derivatives. The operator precedence rules are naturally handled by the compiler. The library could be useful for building custom DSL's in C++.

func.h contains definitions for some of the cmath functions: Sin/Cos, Ln, Pow, Abs, Sqrt, Exp, more to come...
Function composition is supported. 

	auto f1 = 3 * x;
	auto f2 = Ln(x);
	auto f = f1 + f2;

	auto y1 = f(2);
	auto y2 = f(4);

## Examples of Functions and Derivatives

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

* Run cmake

		$cmake ../metamath

* Build it    

		$make

* You can now run a sample (the sample source is in metamath/sample/)

		$./sample/mms


* The sample output:

		Metamath sample
		======
		f(x) = 3 * x * x
		f(4) = 48
		------
		f`(x) = ((0 * x + 3) * x + 3 * x)
		f`(4) = 24
		======

		======
		f(x) = 3 * x
		f(2) = 6
		f(3) = 9
		------
		f`(x) = (0 * x + 3)
		f`(2) = 3
		======

		======
		f(x) = ((1) / (x))
		f(2) = 0.5
		f(3) = 0.333333
		------
		f`(x) = (((0 * x - 1)) / (x * x))
		f`(2.f) = -0.25
		======

		======
		f(x) = ((2 * (x + 1)) / (x))
		f(2) = 3
		f(3) = 2.66667
		------
		f`(x) = ((((0 * (x + 1) + 2 * 1) * x - 2 * (x + 1))) / (x * x))
		f`(2) = -0.5
		======

		======
		f(x) = 4 * sin(2 * x)
		f(pi) = 6.99382e-07
		f(pi/4) = 4
		------
		f`(x) = (0 * sin(2 * x) + 4 * cos(2 * x) * (0 * x + 2))
		f`(pi) = 8
		f`(pi/4) = -3.49691e-07
		======

		======
		f(x) = sqrt(x)
		f(4) = 2
		f(6) = 2.44949
		------
		f`(x) = ((1) / (2 * sqrt(x)))
		f`(4) = 0.25
		f`(6) = 0.204124
		======

		======
		f(x) = (3 * x^2)
		f(4) = 144
		f(6) = 324
		------
		f`(x) = 2 * (3 * x^1) * (0 * x + 3)
		f`(4) = 72
		f`(6) = 108
		======

		======
		f(x) = e^(3 * x)
		f(4) = 162755
		f(6) = 6.566e+07
		------
		f`(x) = e^(3 * x) * (0 * x + 3)
		f`(4) = 488264
		f`(6) = 1.9698e+08
		======

		======
		f(x) = ln(3 * x)
		f(4) = 2.48491
		f(6) = 2.89037
		------
		f`(x) = ((1) / (3 * x)) * (0 * x + 3)
		f`(4) = 0.25
		f`(6) = 0.166667
		======

		======
		f(x) = |3 * x|
		f(-4) = 12
		f(6) = 18
		------
		f`(x) = ((3 * x) / (|3 * x|)) * (0 * x + 3)
		f`(-4) = -3
		f`(6) = 3
		======
