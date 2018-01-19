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
		struct identity;

	template<>
		struct identity<int>
		{
			static constexpr int v = 1;
		};
	template<>
		struct identity<float>
		{
			static constexpr float v = 1.0f;
		};
	template<>
		struct identity<double>
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
	
	constexpr bool is_identity(int v) 
	{
		return v == identity<int>::v;
	}
	template<typename T>
	constexpr bool is_identity(T v)
	{
		return is_zero<T>(std::abs(v - identity<T>::v));
	}

	// checks for exp<>
	//
	template<typename ...T> struct is_zero_t;

			//allow exp<> types only
	template<typename ...T>
	struct is_zero_t< exp<T...> >
	{
		typedef exp<T...> exp_t;
		static constexpr bool check(const exp_t&)
		{
			return false;
		}
	};
	template<typename T>
	struct is_zero_t<exp<T, empty, constant>>
	{
		typedef exp<T, empty, constant> exp_t;
		static constexpr bool check(const exp_t& e)
		{
			return e.z_;
		}
	};
	template<typename T>
	constexpr bool is_zero_const(const T& e)
	{
		return is_zero_t<T>::check(e);
	}
	

			//allow exp<> types only
	template<typename ...T> struct is_identity_t;

	template<typename ...T>
	struct is_identity_t<exp<T...>>
	{
		typedef exp<T...> exp_t;
		static constexpr bool check(const exp_t&)
		{
			return false;
		}
	};
	template<typename T>
	struct is_identity_t<exp<T, empty, constant>>
	{
		typedef exp<T, empty, constant> exp_t;
		static constexpr bool check(const exp_t& e)
		{
			return e.u_;
		}
	};
	template<typename T>
	constexpr bool is_identity_const(const T& e)
	{
		return is_identity_t<T>::check(e);
	}

	// expression specializations
	//
	template<typename T>
	struct exp<T, empty, constant>
	{
		typedef T type;

		T v_;
		bool z_; //indicates zero
		bool u_; //indicates identity

		exp(T v) 
			:v_{v} 
			,z_{is_zero(v)}
			,u_{is_identity(v)}
		{
		}

		template<typename V>
		constexpr T operator()(V v) const
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
		constexpr decltype(e1_(V{}) / e2_(V{})) operator()(V v) const
		{
			if (is_identity_const(e2_)) {
				return e1_(v);
			}
			return e1_(v) / e2_(v);
		}

		template<typename Os>
		Os& print(Os& os) const
		{
			if (is_identity_const(e2_)) {
				os << e1_;
				return os;
			}
			os << "((" << e1_ << ")" << " / " << "(" << e2_ << "))";
			return os;
		}
	};

	template<typename E1, typename E2>
	struct exp<E1, E2, mult>
	{
		E1 e1_;
		E2 e2_;

		template<typename V>
		constexpr decltype(e1_(V{}) * e2_(V{})) operator()(V v) const
		{
			if (is_zero_const(e1_) || is_zero_const(e2_)) {
				return zero<V>::v;
			}
			if (is_identity_const(e1_)) {
				return e2_(v);
			}
			if (is_identity_const(e2_)) {
				return e1_(v);
			}
			return e1_(v) * e2_(v);
		}

		template<typename Os>
		Os& print(Os& os) const
		{
			if (is_identity_const(e1_)) {
				os << e2_;
				return os;
			}
			if (is_identity_const(e2_)) {
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
		constexpr decltype(e1_(V{}) + e2_(V{})) operator()(V v) const
		{
			return e1_(v) + e2_(v);
		}

		template<typename Os>
		Os& print(Os& os) const
		{
			if (is_zero_const(e1_)) {
				os << e2_;
				return os;
			}
			if (is_zero_const(e2_)) {
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
		constexpr decltype(e1_(V{}) - e2_(V{})) operator()(V v) const
		{
			return e1_(v) - e2_(v);
		}

		template<typename Os>
		Os& print(Os& os) const
		{
			if (is_zero_const(e1_)) {
				os << e2_;
				return os;
			}
			if (is_zero_const(e2_)) {
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
