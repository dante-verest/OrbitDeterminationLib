#pragma once
#include "pch.h"
#include "framework.h"

namespace Structures
{
	//template<typename T>
	//concept FP = std::is_floating_point<T>::value;
	//template<FP T>
	template<typename T>
	struct AngularMeasurements
	{
		T alpha;
		T delta;
		AngularMeasurements() : alpha(0.0), delta(0.0)
		{};
		AngularMeasurements(T a_alpha, T a_beta) : alpha(a_alpha), delta(a_beta)
		{};
	};
}
