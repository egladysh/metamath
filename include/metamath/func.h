#ifndef H_959A452BAE594DD3BBFD16C531B4AB04
#define H_959A452BAE594DD3BBFD16C531B4AB04

#include <cmath> 
#include "exp.h"

namespace metamath
{
	struct sin_f
	{
		template<typename T>
		auto operator()(T v) const
		{
			return std::sin(v);
		}
	};
	struct cos_f
	{
		template<typename T>
		auto operator()(T v) const
		{
			return std::cos(v);
		}
	};

	template<typename E>
	struct exp<E, sin_f, func>
	{
		E e_;

		template<typename V>
		V operator()(V v) const
		{
			return sin_f()(e_(v));
		}

		template<typename Os>
		Os& print(Os& os) const
		{
			os << "sin(" << e_ << ")";
			return os;
		}

		auto derivative() const
		{
			return exp<E, cos_f, func>{e_};
		}
	};

	template<typename E>
	struct exp<E, cos_f, func>
	{
		E e_;

		template<typename V>
		V operator()(V v) const
		{
			return cos_f()(e_(v));
		}

		template<typename Os>
		Os& print(Os& os) const
		{
			os << "cos(" << e_ << ")";
			return os;
		}

		auto derivative() const
		{
			return exp<E, sin_f, func>{e_} * -1;
		}
	};

	// T is of an exp<> kind
	template<typename T>
		constexpr auto Sin(const T& e)
		{
			return exp<T, sin_f, func>{e};
		}
	template<typename T>
		constexpr auto Cos(const T& e)
		{
			return exp<T, cos_f, func>{e};
		}
}

#endif
