#pragma once
#include "pch.h"
#include "framework.h"

namespace Structures
{
	//template<typename T>
	//concept FP_ = std::is_floating_point<T>::value;
	//template<FP_ T>
	template<typename T>
	struct ObservationPoint
	{
		T phi;		// ������, � ��������
		T lambda;	// �������, � ��������
		T H;		// ������ ��������������� ������ ��� ������� ����, � ��
		ObservationPoint() : phi(0.0), lambda(0.0), H(0.0)
		{};
		ObservationPoint(T a_phi, T a_lambda, T a_H) :
			phi(a_phi), lambda(a_lambda), H(a_H)
		{};
	};
}

