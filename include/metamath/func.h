#ifndef H_959A452BAE594DD3BBFD16C531B4AB04
#define H_959A452BAE594DD3BBFD16C531B4AB04

#include <cmath> 
#include "exp.h"

namespace metamath
{
		// trigonometric functions
		// 

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
		auto operator()(V v) const
		{
			return sin_f{}(e_(v));
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
		auto operator()(V v) const
		{
			return cos_f{}(e_(v));
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


		// SQRT

	struct sqrt_f
	{
		template<typename T>
		auto operator()(T v) const
		{
			return std::sqrt(v);
		}
	};
	
	template<typename E>
	struct exp<E, sqrt_f, func>
	{
		E e_;

		template<typename V>
		auto operator()(V v) const
		{
			return sqrt_f{}(e_(v));
		}

		template<typename Os>
		Os& print(Os& os) const
		{
			os << "sqrt(" << e_ << ")";
			return os;
		}

		auto derivative() const
		{
			return 1 / (2 * exp<E, sqrt_f, func>{e_});
		}
	};

	template<typename T>
		constexpr auto Sqrt(const T& e)
		{
			return exp<T, sqrt_f, func>{e};
		}


		// POW

	template<int N>
	struct pow_f
	{
		template<typename T>
		auto operator()(T v) const
		{
			return std::pow(v, N); 
		}
	}; 

	template<>
	struct pow_f<1>
	{
		template<typename T>
		auto operator()(T v) const
		{
			return v; 
		}
	}; 

	template<typename E, int N>
	struct exp<E, pow_f<N>, func>
	{
		E e_;

		template<typename V>
		auto operator()(V v) const
		{
			return pow_f<N>{}(e_(v));
		}

		template<typename Os>
		Os& print(Os& os) const
		{
			os << "(" << e_ << "^" << N << ")";
			return os;
		}

		auto derivative() const
		{
			return N * (exp<E, pow_f<N-1>, func>{e_});
		}
	};


	template<int N, typename T>
		constexpr auto Pow(const T& e)
		{
			return exp<T, pow_f<N>, func>{e};
		}


	// exponent
	//

	struct exponent_f
	{
		template<typename T>
		auto operator()(T v) const
		{
			return std::exp(v);
		}
	};
	
	template<typename E>
	struct exp<E, exponent_f, func>
	{
		E e_;

		template<typename V>
		auto operator()(V v) const
		{
			return exponent_f{}(e_(v));
		}

		template<typename Os>
		Os& print(Os& os) const
		{
			os << "e" << "^(" << e_ << ")";
			return os;
		}

		auto derivative() const
		{
			return exp<E, exponent_f, func>{e_};
		}
	};

	template<typename T>
		constexpr auto Exp(const T& e)
		{
			return exp<T, exponent_f, func>{e};
		}

	// natural logarithm
	//
	struct ln_f
	{
		template<typename T>
		auto operator()(T v) const
		{
			return std::log(v);
		}
	};
	
	template<typename E>
	struct exp<E, ln_f, func>
	{
		E e_;

		template<typename V>
		auto operator()(V v) const
		{
			return ln_f{}(e_(v));
		}

		template<typename Os>
		Os& print(Os& os) const
		{
			os << "ln" << "(" << e_ << ")";
			return os;
		}

		auto derivative() const
		{
			return 1 / e_;
		}
	};

	template<typename T>
		constexpr auto Ln(const T& e)
		{
			return exp<T, ln_f, func>{e};
		}


	// abs function
	//
	struct abs_f
	{
		template<typename T>
		auto operator()(T v) const
		{
			return std::abs(v);
		}
	};
	
	template<typename E>
	struct exp<E, abs_f, func>
	{
		E e_;

		template<typename V>
		auto operator()(V v) const
		{
			return abs_f{}(e_(v));
		}

		template<typename Os>
		Os& print(Os& os) const
		{
			os << "|" << e_ << "|";
			return os;
		}

		auto derivative() const
		{
			return (e_) / (exp<E, abs_f, func>{e_});
		}
	};

	template<typename T>
		constexpr auto Abs(const T& e)
		{
			return exp<T, abs_f, func>{e};
		}

}

#endif
