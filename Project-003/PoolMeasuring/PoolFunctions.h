/*
 *  Gwenn Flores
 *  Samer Kamel
 *  Frank DiCola
 *
 *  SSW 567
 *  Prof. Ardis
 *  Project Assignment 07
 *
 *  GOAL:   Create a series of functions used
 *			to calculate pool data.
 */

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct pools_t
{
	string length;
	string width;
	string shallowEnd;
	string deepEnd;
	string customer;
	double area;
	double volume;
	int days;
	int hours;
	int minutes;
};

pools_t initializePool(pools_t pool) {

	pool.length = "n/a";
	pool.width = "n/a";
	pool.shallowEnd = "n/a";
	pool.deepEnd = "n/a";
	pool.customer = "n/a";
	pool.area = 0;
	pool.volume = 0;
	pool.days = 0;
	pool.hours = 0;
	pool.minutes = 0;
	return pool;
}

double calculateArea(string l, string w, string s, string d) {

	double shallowArea;
	double deepArea;
	double sidesArea;
	double bottomArea;
	double difference = stod(d) - stod(s);					// cout << "Difference: " << difference << endl;
	double area;

	shallowArea = stod(w) * stod(s);						// cout << "Shallow: " << shallowArea << endl;
	deepArea = stod(w) * stod(d);							// cout << "Deep: " << deepArea << endl;
	sidesArea = stod(l) * stod(s);							// cout << "Sides (P1): " << sidesArea << endl;
	sidesArea = sidesArea + ((difference * stod(l)) / 2);	// cout << "Sides (P2): " << sidesArea << endl;
	sidesArea *= 2;											// cout << "Sides (P3): " << sidesArea << endl;
	bottomArea = pow(difference, 2) + pow(stod(l), 2);		// cout << "Bottom (P1): " << bottomArea << endl;
	bottomArea = stod(w) * sqrt(bottomArea);				// cout << "Bottom (P2): " << bottomArea << endl;
		// cout << "Area is going to be equal to: " << shallowArea << " + " << deepArea << " + " << sidesArea << " + " << bottomArea << ", ok?" << endl;
	area = shallowArea + deepArea + sidesArea + bottomArea;
		// cout << "Area is: " << area << endl;

	return area;
};

double calculateVolume(string l, string w, string s, string d) {

	double v1;
	double v2;
	double volume;
	double length = stod(l);
	double width = stod(w);
	double shallowEnd = stod(s);
	double deepEnd = stod(d);

	v1 = length * width * (shallowEnd - 0.5);
	v2 = (length * width * (deepEnd - shallowEnd)) / 2;

	volume = (v1 + v2) * 7.48; // gallons per cubic foot

	return volume;
}

pools_t calculatePoolTime(string var, pools_t pool) {

	double days;
	double hours;
	double minutes;
	double temp;

	if(var == "area") {
		days = pool.area / 266.67;
	}
	else if(var == "volume") {
		days = pool.volume / 266.67;
	}
	pool.days = days;

	hours = modf(days, &temp) * 24;
	pool.hours = hours;

	minutes = modf(hours, &temp) * 60;
	pool.minutes = minutes;

	return pool;
}

void printPoolInfo(pools_t pool) {
	cout << 
		"LENGTH: " << pool.length << 
		" WIDTH: " << pool.width << 
		" SHALLOW: " << pool.shallowEnd << 
		" DEEP: " << pool.deepEnd <<
		" CUSTOMER: " << pool.customer 
		<< endl;
}