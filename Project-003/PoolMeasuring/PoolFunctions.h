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

pools_t calculatePaintTime( pools_t pool )
{
	if ( true )
	{
		// This path runs a simulation that computes how long it will take to paint the pool.
		//		ASSUMPTIONS:		1 worker painting alone can paint 100 sq ft in one hour.			paintRate = 100 sq ft;
		//							Both workers working together can paint 200 sq ft in one hour.		paintRateTogether = paintRate * 2;

		// Variables Needed
		double areaLeftToPaint;
		double paintRate;
		double paintRateTogether;
		double paintRateTogether_InSeconds;
		bool workingTogether;
		int counter;

		// Set Variables
		areaLeftToPaint = pool.area;
		paintRate = 100;						//		100 sq ft per hour
		paintRateTogether = paintRate * 2;		//		200 sq ft per hour
		paintRateTogether_InSeconds = 18;		//		1/200 * 3600 = 18
		workingTogether = true;
		counter = 0;

		while ( areaLeftToPaint > 0 )	// The pool is not done being painted
		{
			if ( areaLeftToPaint < paintRateTogether)
			{
				// This is the final hour of painting
				pool.minutes = areaLeftToPaint * paintRateTogether_InSeconds;
				pool.minutes /= 60;
				areaLeftToPaint -= areaLeftToPaint;
			}
			else if ( !workingTogether && (areaLeftToPaint < paintRate))
			{
				// This is the final hour of filling
				pool.minutes = areaLeftToPaint * (paintRateTogether_InSeconds / 2);
				pool.minutes /= 60;
				areaLeftToPaint -= areaLeftToPaint;
			}
			else
			{
				if ( workingTogether )		
				{
					// Early Morning
					areaLeftToPaint -= paintRateTogether;
				}
				else	
				{
					// Afternoon
					areaLeftToPaint -= paintRate;
				}

				counter++;

				if ( counter >= 4 )
				{
					workingTogether = !workingTogether;
					counter = 0;
				}

				pool.hours++;

				// cout << areaLeftToPaint << endl;
				// cout << pool.hours << endl;
			}

			if ( pool.hours >= 8 )
			{
				pool.days++;
				pool.hours = 0;
			}
		}
	}

	return pool;
}

pools_t calculateFillTime( pools_t pool )
{
	if ( true )
	{
		// This path runs a simulation that computes how long it will take to fill the pool.
		//		ASSUMPTIONS:		1 hose filling painting alone can provide 1000 cubic gallons in one hour.	fillRate = 1000 cubic gallons;
		//							Both hoses filling together can provide 2000 cubic gallons in one hour.		fillRateTogether = paintRate * 2;

		// Variables Needed
		double areaLeftToFill;
		double fillRate;
		double fillRateTogether;
		double fillRateTogether_InSeconds;
		bool workingTogether;
		int counter;

		// Set Variables
		areaLeftToFill = pool.volume;
		fillRate = 1000;						//		1000 cubic gallons per hour
		fillRateTogether = fillRate * 2;		//		2000 cubic gallons per hour
		fillRateTogether_InSeconds = 1.8;		//		1/200 * 3600 = 18
		workingTogether = true;
		counter = 0;
		pool.days = 0;
		pool.hours = 0;
		pool.minutes = 0;

		while ( areaLeftToFill > 0 )	// The pool is not done being filled
		{
			cout << areaLeftToFill << "   " << pool.days << "   " << pool.hours << "   " << pool.minutes << endl;

			if ( workingTogether && (areaLeftToFill < fillRateTogether))
			{
				// This is the final hour of filling
				pool.minutes = areaLeftToFill * fillRateTogether_InSeconds;
				pool.minutes /= 60;
				areaLeftToFill -= areaLeftToFill;
			}
			else if ( !workingTogether && (areaLeftToFill < fillRate))
			{
				// This is the final hour of filling
				pool.minutes = areaLeftToFill * (fillRateTogether_InSeconds / 2);
				pool.minutes /= 60;
				areaLeftToFill -= areaLeftToFill;
			}
			else
			{
				if ( workingTogether )		
				{
					// Early Morning
					areaLeftToFill -= fillRateTogether;
				}
				else	
				{
					// Afternoon
					areaLeftToFill -= fillRate;
				}

				counter++;

				if ( counter >= 4 )
				{
					workingTogether = !workingTogether;
					counter = 0;
				}

				pool.hours++;
			}

			if ( pool.hours >= 8 )
			{
				pool.days++;
				pool.hours = 0;
			}
		}
	}

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