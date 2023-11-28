#include "pch.h"
#include "Date.h"

Structures::Date::
Date() : year(0), month(0), day(0), hour(0), min(0), sec(0.0)
{};
Structures::Date::
Date(int year_, int month_, int day_,
	int hour_, int min_, double sec_) :
	year(year_), month(month_), day(day_), hour(hour_), min(min_), sec(sec_)
{};
Structures::Date::
~Date()
{};
double Structures::Date::JulianDate()
{
	return (367 * this->year -
		(7 * (this->year + (this->month + 9) / 12) / 4) +
		(275 * this->month / 9) +
		this->day +
		1721013.5 +
		((this->sec / 60 + this->min) / 60 + this->hour) / 24);
};
double Structures::Date::JulianDate(int year, int month, int day, int hour, int min, double sec)
{
	return (367 * year -
		(7 * (year + (month + 9) / 12) / 4) +
		(275 * month / 9) +
		day +
		1721013.5 +
		((sec / 60 + min) / 60 + hour) / 24);
};
double Structures::Date::JulianDate(const Date& date)
{
	return (367 * date.year -
		(7 * (date.year + (date.month + 9) / 12) / 4) +
		(275 * date.month / 9) +
		date.day +
		1721013.5 +
		((date.sec / 60 + date.min) / 60 + date.hour) / 24);
};
bool Structures::Date::AreEqual(const double a, const double b, const double epsilon) const
{
	//return (std::fabs(a - b) <= 
	//	std::numeric_limits<double>::epsilon() * std::fmax(std::fabs(a), std::fabs(b)));
	return (std::fabs(a - b) <=
		epsilon * std::fmax(std::fabs(a), std::fabs(b)));
};
bool Structures::Date::AreEqualStatic(const double a, const double b, const double epsilon)
{
	return (std::fabs(a - b) <=
		epsilon * std::fmax(std::fabs(a), std::fabs(b)));
};
Structures::Date Structures::Date::
operator+(const Date& otherDate) const
{
	Date newDate;
	newDate.year = this->year + otherDate.year;
	newDate.month = this->Date::month + otherDate.month;
	newDate.day = this->Date::day + otherDate.day;
	newDate.hour = this->Date::hour + otherDate.hour;
	newDate.min = this->Date::min + otherDate.min;
	newDate.sec = this->Date::sec + otherDate.sec;
	if (newDate.sec >= 60) newDate.sec -= 60, newDate.min++;
	if (newDate.min >= 60) newDate.min -= 60, newDate.hour++;
	if (newDate.hour >= 24) newDate.hour -= 24, newDate.day++;
	if (newDate.month == 2 && newDate.year % 4 != 0 && newDate.day > 28)
		newDate.day -= 28, newDate.month++;
	else if (newDate.month == 2 && newDate.year % 4 == 0 && newDate.day > 29)
		newDate.day -= 29, newDate.month++;
	else if (newDate.month == 4 || newDate.month == 6 || newDate.month == 9 || newDate.month == 11)
		newDate.day -= 30, newDate.month++;
	else
		newDate.day -= 31, newDate.month++;
	if (newDate.month >= 13) newDate.month -= 12, newDate.year++;
	return newDate;
};
Structures::Date Structures::Date::
operator-(const Date& otherDate) const
{
	Date newDate;
	newDate.year = this->year - otherDate.year;
	newDate.month = this->month - otherDate.month;
	newDate.day = this->day - otherDate.day;
	newDate.hour = this->hour - otherDate.hour;
	newDate.min = this->min - otherDate.min;
	newDate.sec = this->sec - otherDate.sec;
	if (newDate.sec < 0) newDate.sec += 60, newDate.min--;
	if (newDate.min < 0) newDate.min += 60, newDate.hour--;
	if (newDate.hour < 0) newDate.hour += 24, newDate.day--;
	if (newDate.day < 0)
	{
		if (newDate.month == 3 && newDate.year % 4 != 0)
			newDate.day += 28;
		else if (newDate.month == 3 && newDate.year % 4 == 0)
			newDate.day += 29;
		else if (newDate.month == 5 || newDate.month == 7 || newDate.month == 10 || newDate.month == 12)
			newDate.day += 30;
		else
			newDate.day += 31;
		newDate.month--;
	}
	if (newDate.month < 1) newDate.month += 12, newDate.year--;
	return newDate;
};
//Structures::Date Structures::Date::
//DateDifference(const Date& oneDate, const Date& secondDate)
//{
//	//return Date(oneDate.year)
//};
Structures::Date Structures::Date::
operator+=(const Date& otherDate)
{
	this->year += otherDate.year;
	this->month += otherDate.month;
	this->day += otherDate.day;
	this->hour += otherDate.hour;
	this->min += otherDate.min;
	this->sec += otherDate.sec;
	return *this;
};
Structures::Date Structures::Date::
operator-=(const Date& otherDate)
{
	this->year -= otherDate.year;
	this->month -= otherDate.month;
	this->day -= otherDate.day;
	this->hour -= otherDate.hour;
	this->min -= otherDate.min;
	this->sec -= otherDate.sec;
	return *this;
};
bool Structures::Date::
operator ==(const Date& otherDate)
{
	if (this->year != otherDate.year) return false;
	if (this->month != otherDate.month) return false;
	if (this->day != otherDate.day) return false;
	if (this->hour != otherDate.hour) return false;
	if (this->min != otherDate.min) return false;
	if (!AreEqual(this->sec, otherDate.sec, 1e-6)) return false;
	return true;
};
bool Structures::Date::
operator !=(const Date& otherDate)
{
	return !(*this == otherDate);
};