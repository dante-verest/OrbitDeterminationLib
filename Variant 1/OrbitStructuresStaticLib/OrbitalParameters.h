#pragma once
#include "pch.h"
#include "framework.h"

namespace Structures
{
	template<typename T>
	bool AreEqual(const T comparable, const T comparative, const T epsilon)
	{
		return (std::fabs(comparable - comparative) <=
			epsilon * std::fmax(std::fabs(comparable), std::fabs(comparative)));
	};

	//template<typename T>
	//concept FPT = std::is_floating_point<T>::value;
	//template<FPT T>
	template<typename T>
	struct OrbitalParameters
	{
		std::optional<T> i;		// наклонение, в радианах
		std::optional<T> Omega;	// долгота восходящего узла, в радианах
		std::optional<T> omega;	// аргумент перигея, в радианах
		std::optional<T> e;		// эксцентриситет, безразмерная
		std::optional<T> a;		// большая полуось, в км
		std::optional<T> Theta;	// истинная аномалия, в радианах
		std::optional<T> h;		// угловой момент, в км^2/с
		OrbitalParameters()
		{};
		//OrbitalParameters() : 
		//	i(0.0), Omega(0.0), omega(0.0), e(0.0), a(0.0), Theta(0.0), h(0.0)
		//{};
		OrbitalParameters(T a_i, T a_Omega, T a_omega, T a_e, T a_a, T a_Theta, T a_h) : 
			i(a_i), Omega(a_Omega),	omega(a_omega), e(a_e), a(a_a), Theta(a_Theta), h(a_h)
		{};
		bool IsEmpty()
		{
			//return (AreEqual(i, 0.0, 1e-6) && AreEqual(Omega, 0.0, 1e-6) && AreEqual(omega, 0.0, 1e-6) &&
			//	AreEqual(e, 0.0, 1e-6) && AreEqual(a, 0.0, 1e-6) && AreEqual(Theta, 0.0, 1e-6) && AreEqual(h, 0.0, 1e-6));
			return !(i.has_value() && Omega.has_value() && omega.has_value() && 
				e.has_value() && a.has_value() && Theta.has_value() && h.has_value());
		};
	};
}
