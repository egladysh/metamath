#ifndef H_B167998171FB4FBD813140B6FC14688D
#define H_B167998171FB4FBD813140B6FC14688D

#include "func.h"

namespace metamath
{
	template<typename T>
		struct drv;

	// derivative of a function
	template<typename E, typename F>
		struct drv<exp<E, F, func>>
		{
			typedef exp<E, F, func> fexp;

			auto operator()(const fexp& e)
			{
				//function definition must supply its derivative
				return e.derivative() * drv<E>{}(e.e_);
			}
		};

	// derivative of a variable
	template<typename E>
		struct drv<exp<E, empty, variable>>
		{
			typedef exp<E, empty, variable> vexp;

			auto operator()(const vexp&)
			{
				return exp<E, empty, constant>{unity<E>::v};
			}
		};

	// derivative of a constant
	template<typename E>
		struct drv<exp<E, empty, constant>>
		{
			typedef exp<E, empty, constant> cexp;

			auto operator()(const cexp&)
			{
				return exp<E, empty, constant>{zero<E>::v};
			}
		};

	// derivative of a product
	template<typename E1, typename E2>
		struct drv<exp<E1, E2, mult>>
		{
			typedef exp<E1, E2, mult> mexp;

			auto operator()(const mexp& e)
			{
				return drv<E1>{}(e.e1_) * e.e2_ + e.e1_ * drv<E2>{}(e.e2_);
			}
		};

	// derivative of a division
	template<typename E1, typename E2>
		struct drv<exp<E1, E2, div>>
		{
			typedef exp<E1, E2, div> dexp;

			auto operator()(const dexp& e)
			{
				return (drv<E1>{}(e.e1_) * e.e2_ - e.e1_ * drv<E2>{}(e.e2_)) / (e.e2_ * e.e2_);
			}
		};

	// derivative of additions
	template<typename E1, typename E2>
		struct drv<exp<E1, E2, plus>>
		{
			typedef exp<E1, E2, plus> pexp;

			auto operator()(const pexp& e)
			{
				return drv<E1>{}(e.e1_) + drv<E2>{}(e.e2_);
			}
		};
	template<typename E1, typename E2>
		struct drv<exp<E1, E2, minus>>
		{
			typedef exp<E1, E2, minus> mexp;

			auto operator()(const mexp& e)
			{
				return drv<E1>{}(e.e1_) - drv<E2>{}(e.e2_);
			}
		};

	
	// wrap it
	template<typename E>
		auto derivative(const E& e)
		{
			return drv<E>()(e);
		}
}

#endif
