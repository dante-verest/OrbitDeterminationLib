#pragma once
#include "pch.h"
#include "framework.h"

namespace Structures
{
	struct Date
	{
		int year;	// год
		int month;	// мес€ц, 1-12
		int day;	// день, 1-366
		int hour;	// час, 0-23
		int min;	// минута, 0-59
		double sec;	// секунда, 0.0-59.99999...
		Date();
		Date(int year, int month, int day, int hour, int min, double sec);
		~Date();

		//template <typename T> T
		//	GetFieldThroughIndex(int index) const
		//{
		//	if (index == 0) return year;
		//	if (index == 1) return month;
		//	if (index == 2) return day;
		//	if (index == 3) return hour;
		//	if (index == 4) return min;
		//	if (index == 5) return sec;
		//	return 0;
		//};
		//template <typename T> void
		//	SetFieldThroughIndex(T field, int index)
		//{
		//	if (std::is_same<T, int>::value)
		//	{
		//		if (index == 0) year = field;
		//		if (index == 1) month = field;
		//		if (index == 2) day = field;
		//		if (index == 3) hour = field;
		//		if (index == 4) min = field;
		//	}
		//	if (std::is_same<T, double>::value)
		//		if (index == 5) sec = field;
		//	return;
		//};

		double JulianDate();
		static double JulianDate(int year, int month, int day, int hour, int min, double sec);
		static double JulianDate(const Date& date);

		Date operator +(const Date&) const;
		Date operator -(const Date&) const;
		//static Date DateDifference(const Date&, const Date&);
		Date operator +=(const Date&);
		Date operator -=(const Date&);
		bool operator ==(const Date&);
		bool operator !=(const Date&);
		friend bool operator ==(const Date& oneDate, const Date& secondDate)
		{
			if (oneDate.year != secondDate.year) return false;
			if (oneDate.month != secondDate.month) return false;
			if (oneDate.day != secondDate.day) return false;
			if (oneDate.hour != secondDate.hour) return false;
			if (oneDate.min != secondDate.min) return false;
			if (!AreEqualStatic(oneDate.sec, secondDate.sec, 1e-6)) return false;
			return true;
		}
		friend bool operator !=(const Date& oneDate, const Date& secondDate)
		{
			return !(oneDate == secondDate);
		}
	private:
		bool AreEqual(double a, double b, double epsilon) const;
		static bool AreEqualStatic(double a, double b, double epsilon);
	};
}
