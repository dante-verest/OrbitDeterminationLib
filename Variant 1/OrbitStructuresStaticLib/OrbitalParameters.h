#pragma once
#include "pch.h"
#include "framework.h"

namespace Structures
{
	//template<typename T>
	//concept FPT = std::is_floating_point<T>::value;
	//template<FPT T>
	template<typename T>
	struct OrbitalParameters
	{
		T i;		// наклонение, в радианах
		T Omega;	// долгота восходящего узла, в радианах
		T omega;	// аргумент перигея, в радианах
		T e;		// эксцентриситет, безразмерная
		T a;		// большая полуось, в км
		T Theta;	// истинная аномалия, в радианах
		T h;		// угловой момент, в км^2/с
		OrbitalParameters() : 
			i(0.0), Omega(0.0), omega(0.0), e(0.0), a(0.0), Theta(0.0), h(0.0)
		{};
		OrbitalParameters(T a_i, T a_Omega, T a_omega, T a_e, T a_a, T a_Theta, T a_h) : 
			i(a_i), Omega(a_Omega),	omega(a_omega), e(a_e), a(a_a), Theta(a_Theta), h(a_h)
		{};
	};
}
