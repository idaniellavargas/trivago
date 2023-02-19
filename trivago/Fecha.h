#pragma once
#include <string>
#include <conio.h>
#include <iostream>

using namespace std;

string months[12] = { "Enero","Febrero","Marzo","Abril","Mayo","Junio",
					"Julio","Agosto","Septiembre","Octubre","Noviembre", "Diciembre" };

class Date {
private:
	int year;
	int month;
	int day;
public:
	Date();
	Date(int day, int month, int year);
	~Date();
	int get_year();
	int get_month();
	int get_day();
	void set_year(int year);
	void set_day(int day);
	void set_month(int month);
	string getDate();
	void monthLetters();
	bool leapYear(); //anho bisiesto
	bool dateIsReal();

	bool operator>(Date* rhs) {
		if (year > rhs->year) return true;
		else if (year < rhs->year) return false;
		else {
			if (month > rhs->month) return true;
			else if (month < rhs->month) return false;
			else {
				if (day > rhs->day) return true;
				else if (day < rhs->day) return false;
			}
			
		}
	}

	bool operator<(Date* rhs) {
		if (year > rhs->year) return false;
		else if (year < rhs->year) return true;
		else {
			if (month > rhs->month) return false;
			else if (month < rhs->month) return true;
			else {
				if (day > rhs->day) return false;
				else if (day <= rhs->day) return true;
			}

		}
	}
};

Date::Date()
{
	day = rand() % 31;
	month = rand() % 13;
	year = rand() % 2023;
}

Date::Date(int day, int month, int year)
{
	this->day = day;
	this->month = month;
	this->year = year;
}



Date::~Date() {}

int Date::get_year()
{
	return year;
}

int Date::get_month()
{
	return month;
}

int Date::get_day()
{
	return day;
}

void Date::set_year(int year)
{
	this->year = year;
}

void Date::set_day(int day)
{
	this->day = day;
}

void Date::set_month(int month)
{
	this->month = month;
}

string Date::getDate() { //concatenacion como con +
	string s;
	if(day < 10) s.append("0");
	s.append(to_string(day));
	s.append("/");
	s.append(to_string(month));
	if (month < 10) s.append("0");
	s.append("/");
	s.append(to_string(year));
	return s;
}

void Date::monthLetters() {
	cout << "\n" << day << " de " << months[month - 1] << ", " << year;
}

bool Date::leapYear() {
	//los bisiestos son divisibles entre 4, pero no por 100 a no ser que tambien lo sean entre 400
	if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) return true;
	else return false;
}

bool Date::dateIsReal() {
	if (month >= 1 && month <= 12) {
		switch (month) {
		case 1: case 3: case 5: case 7: case 8: case 10: case 12: //aprender con nudillos
			if (day >= 1 && day <= 31) return true;
			else return false;
			break;
		case 4: case 6: case 9: case 11:
			if (day >= 1 && day <= 30) return true;
			else return false;
			break;
		case 2:
			if ((day >= 1 && day <= 28) || (leapYear() && day == 29)) return true;
			else return false;
			break;
		}
	}
}