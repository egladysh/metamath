#ifndef H_C5A1C710C76845F8AE8B0E2F16424836
#define H_C5A1C710C76845F8AE8B0E2F16424836

#include <assert.h>
#include <limits>
#include <cmath>

namespace metamath
{
	// default function domain
	// the default variable name, 'x' is mapped to this domain type
	typedef float domain;

	// operation and other tags
	struct plus;
	struct minus;
	struct mult;
	struct div;
	struct func;
	struct variable;
	struct constant;

	struct empty;

	// fundamental expression type
	//
	template<typename E1, typename E2, typename Op>
	struct exp;


	// some built-in definitions and checks
	template<typename T>
		struct zero;

	template<>
		struct zero<int>
		{
			static constexpr int v = 0;
		};
	template<>
		struct zero<float>
		{
			static constexpr float v = 0.0f;
		};
	template<>
		struct zero<double>
		{
			static constexpr double v = 0.0;
		};

	template<typename T>
		struct unity;

	template<>
		struct unity<int>
		{
			static constexpr int v = 1;
		};
	template<>
		struct unity<float>
		{
			static constexpr float v = 1.0f;
		};
	template<>
		struct unity<double>
		{
			static constexpr double v = 1.0;
		};


	constexpr bool is_zero(int v) 
	{
		return v == zero<int>::v;
	}
	template<typename T>
	constexpr bool is_zero(T v)
	{
		if ( (std::nextafter(v, std::numeric_limits<T>::lowest()) > zero<T>::v)
			|| (std::nextafter(v, std::numeric_limits<T>::max()) < zero<T>::v) )
			return false;
		return true;
	}
	
	constexpr bool is_unity(int v) 
	{
		return v == unity<int>::v;
	}
	template<typename T>
	constexpr bool is_unity(T v)
	{
		return is_zero<T>(std::abs(v - unity<T>::v));
	}

	// checks
	//
	template<typename T>
	struct is_zero_t
	{
		constexpr bool operator()(const T&)
		{
			return false;
		}
	};
	template<typename T>
	struct is_zero_t<exp<T, empty, constant>>
	{
		typedef exp<T, empty, constant> exp_t;
		constexpr bool operator()(const exp_t& e)
		{
			return e.z_;
		}
	};
	template<typename T>
	constexpr bool iszero(const T& e)
	{
		return is_zero_t<T>()(e);
	}
	
	template<typename T>
	struct is_unity_t
	{
		constexpr bool operator()(const T&)
		{
			return false;
		}
	};
	template<typename T>
	struct is_unity_t<exp<T, empty, constant>>
	{
		typedef exp<T, empty, constant> exp_t;
		constexpr bool operator()(const exp_t& e)
		{
			return e.u_;
		}
	};
	template<typename T>
	constexpr bool isunity(const T& e)
	{
		return is_unity_t<T>()(e);
	}

	// expression specializations
	//
	template<typename T>
	struct exp<T, empty, constant>
	{
		typedef T type;

		T v_;
		bool z_; //indicates zero
		bool u_; //indicates unity

		exp(T v) 
			:v_(v) 
			,z_(is_zero(v))
			,u_(is_unity(v))
		{
		}

		template<typename V>
		constexpr V operator()(V v) const
		{
			return v_;
		}

		template<typename Os>
		Os& print(Os& os) const
		{
			os << v_;
			return os;
		}
	};

	// variable expression
	template<typename T>
	struct exp<T, empty, variable>
	{
		typedef T type;

		constexpr T operator()(T v) const
		{
			return v;
		}

		template<typename Os>
		Os& print(Os& os) const
		{
			os << "x";
			return os;
		}
	};

	// variable placeholder
	template<typename Domain=domain>
		using var = exp<Domain, empty, variable>;

	template<typename E1, typename E2>
	struct exp<E1, E2, div>
	{
		E1 e1_;
		E2 e2_;

		template<typename V>
		constexpr decltype(e1_(V()) / e2_(V())) operator()(V v) const
		{
			if (isunity(e2_)) {
				return e1_(v);
			}
			return e1_(v) / e2_(v);
		}

		template<typename Os>
		Os& print(Os& os) const
		{
			if (isunity(e2_)) {
				os << e1_;
				return os;
			}
			os << "(" << e1_ << ")" << " / " << "(" << e2_ << ")";
			return os;
		}
	};

	template<typename E1, typename E2>
	struct exp<E1, E2, mult>
	{
		E1 e1_;
		E2 e2_;

		template<typename V>
		constexpr decltype(e1_(V()) * e2_(V())) operator()(V v) const
		{
			if (iszero(e1_) || iszero(e2_)) {
				return zero<V>::v;
			}
			if (isunity(e1_)) {
				return e2_(v);
			}
			if (isunity(e2_)) {
				return e1_(v);
			}
			return e1_(v) * e2_(v);
		}

		template<typename Os>
		Os& print(Os& os) const
		{
			if (isunity(e1_)) {
				os << e2_;
				return os;
			}
			if (isunity(e2_)) {
				os << e1_;
				return os;
			}
			os << e1_ << " * " << e2_;
			return os;
		}
	};

	template<typename E1, typename E2>
	struct exp<E1, E2, plus>
	{
		E1 e1_;
		E2 e2_;

		template<typename V>
			//must use decltype in case adding another return
		constexpr decltype(e1_(V()) + e2_(V())) operator()(V v) const
		{
			return e1_(v) + e2_(v);
		}

		template<typename Os>
		Os& print(Os& os) const
		{
			if (iszero(e1_)) {
				os << e2_;
				return os;
			}
			if (iszero(e2_)) {
				os << e1_;
				return os;
			}
			os << "(" << e1_ << " + " << e2_ << ")";
			return os;
		}
	};
	
	template<typename E1, typename E2>
	struct exp<E1, E2, minus>
	{
		E1 e1_;
		E2 e2_;

		template<typename V>
			//must use decltype in case adding another return
		constexpr decltype(e1_(V()) - e2_(V())) operator()(V v) const
		{
			return e1_(v) - e2_(v);
		}

		template<typename Os>
		Os& print(Os& os) const
		{
			if (iszero(e1_)) {
				os << e2_;
				return os;
			}
			if (iszero(e2_)) {
				os << "-" << e1_;
				return os;
			}
			os << "(" << e1_ << " - " << e2_ << ")";
			return os;
		}
	};

	// operators
	//

	template<typename T>
	struct exp_type
	{
		typedef T type;
	};
	template<>
	struct exp_type<int>
	{
		typedef exp<int, empty, constant> type;
	};
	template<>
	struct exp_type<float>
	{
		typedef exp<float, empty, constant> type;
	};
	template<>
	struct exp_type<double>
	{
		typedef exp<double, empty, constant> type;
	};

	template<typename E1, typename E2>
	exp<typename exp_type<E1>::type, typename exp_type<E2>::type, plus>
	operator+(const E1& e1, const E2& e2)
	{
		return {e1, e2};
	}

	template<typename E1, typename E2>
	exp<typename exp_type<E1>::type, typename exp_type<E2>::type, minus>
	operator-(const E1& e1, const E2& e2)
	{
		return {e1, e2};
	}

	template<typename E1, typename E2>
	exp<typename exp_type<E1>::type, typename exp_type<E2>::type, mult>
	operator*(const E1& e1, const E2& e2)
	{
		return {e1, e2};
	}

	template<typename E1, typename E2>
	exp<typename exp_type<E1>::type, typename exp_type<E2>::type, div>
	operator/(const E1& e1, const E2& e2)
	{
		return {e1, e2};
	}


	template<class T>
	auto operator<<(std::ostream& os, const T& t) -> decltype(t.print(os), os) 
	{ 
		t.print(os); 
		return os; 
	} 

	// the default variable label
	static constexpr var<domain> x;

}


#endif
