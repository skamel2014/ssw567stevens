/*
 *  Gwenn Flores
 *  Samer Kamel
 *  Frank DiCola
 *
 *  SSW 567
 *  Prof. Ardis
 *  Project Assignment 04
 *
 *  GOAL:   Create a program that can calculate the amoun of time
 *			required to paint the bottom and sides of the pool.
 *
 *			a.) The program should compile into an executable file
 *			b.) The program should generate an output file
 *
 */

#include "stdafx.h"
#include "PoolHeader.h"

using namespace std;

struct pools_t
{
	string length;
	string width;
	string shallowEnd;
	string deepEnd;
	string customer;
	double area;
	int days;
	int hours;
	int minutes;
};

string FindValue( int* ptr, string s )
{
	int len = s.length();
	string ret;

	ret.clear();

	while (*ptr < len)
	{
		if (s[*ptr] == 32)
		{
			*ptr = *ptr + 1;
			break;
		}

		ret = ret + s[*ptr];
		*ptr = *ptr + 1;
		}

	return ret;
}

int main(int argc, char** argv)
{
	string lineToPrint;
	string portion;
	string tempLength;
	string tempWidth;
	string tempShallowEnd;
	string tempDeepEnd;
	int linePos;
	int* linePosPTR;
	int lineLength;
	int j = 1;
	int workerRate = 1200;
	pools_t pool;
	

	// Find a file
    ifstream inputTextFile;
    inputTextFile.open ("input.txt");

	// Make an output file
	ofstream outputFile;
	outputFile.open ("output.txt");
	outputFile << "OUTPUT of POOLMEASURING PROGRAM" << endl << endl;

    // Loop through it until we reach the end
    while(!inputTextFile.eof())
    {
		getline(inputTextFile, lineToPrint);
		// cout << "Entry " << j << ":   " << lineToPrint << endl;
		
		linePos = 0;
		linePosPTR = &linePos;
		lineLength = lineToPrint.length();
		tempLength.clear();
		tempWidth.clear();
		tempShallowEnd.clear();
		tempDeepEnd.clear();
		pool.length = "n/a";
		pool.width = "n/a";
		pool.shallowEnd = "n/a";
		pool.deepEnd = "n/a";
		pool.customer = "n/a";
		pool.area = 0;
		pool.days = 0;
		pool.hours = 0;
		pool.minutes = 0;
		
		// LENGTH
		tempLength = FindValue(linePosPTR, lineToPrint);
		// cout << "Temporary Length: " << tempLength << endl;
		
		// WIDTH
		tempWidth = FindValue( linePosPTR, lineToPrint );
		// cout << "Temporary Width: " << tempWidth << endl;

		// SHALLOW END
		tempShallowEnd = FindValue(linePosPTR, lineToPrint);
		// cout << "Temporary Shallow End: " << tempShallowEnd << endl;
		
		// DEEP END
		tempDeepEnd = FindValue( linePosPTR, lineToPrint );
		// cout << "Temporary Deep End: " << tempDeepEnd << endl;

		// CUSTOMER
		pool.customer = lineToPrint.substr(linePos);
		// cout << "Temporary Customer: " << pool.customer << endl;


		// If these values be worthy, enter them into our struct.
		// Is length greater than width?
		if (isGreaterThan(tempLength, tempWidth))
		{	
			// Is length a positive integer?
			if (isPositiveInteger(tempLength))
				pool.length = tempLength;
			
			// Is width a positive integer?
			if (isPositiveInteger(tempWidth))
				pool.width = tempWidth;
		}
		if (isLessThan(tempShallowEnd, tempDeepEnd))
		{
			// Is shallow end a positive integer?
			if (isPositiveInteger(tempShallowEnd))
				pool.shallowEnd = tempShallowEnd;
		
			// Is deep end a positive integer?
			if (isPositiveInteger(tempDeepEnd))
				pool.deepEnd = tempDeepEnd;
		}
		if (pool.customer.empty())
			pool.customer = "n/a";

		// Calculate the Pool Area if we have complete information
		if ( pool.length != "n/a" && pool.width != "n/a" && pool.shallowEnd != "n/a" && pool.deepEnd != "n/a" )
		{
			double shallowArea;
			double deepArea;
			double sidesArea;
			double bottomArea;
			double difference = stod(pool.deepEnd) - stod(pool.shallowEnd);

			shallowArea = stod(pool.width) * stod(pool.shallowEnd);				// cout << "Shallow: " << shallowArea << endl;
			deepArea = stod(pool.width) * stod(pool.deepEnd);					// cout << "Deep: " << deepArea << endl;
			sidesArea = stod(pool.length) * stod(pool.shallowEnd);				// cout << "Sides (P1): " << sidesArea << endl;
			sidesArea = sidesArea + ((difference * stod(pool.length)) / 2);		// cout << "Sides (P2): " << sidesArea << endl;
			sidesArea *= 2;														// cout << "Sides (P3): " << sidesArea << endl;
			bottomArea = pow(difference, 2) + pow(stod(pool.length), 2);		// cout << "Bottom (P1): " << bottomArea << endl;
			bottomArea = stod(pool.width) * sqrt(bottomArea);					// cout << "Bottom (P2): " << bottomArea << endl;
			pool.area = shallowArea + deepArea + sidesArea + bottomArea;
		}

		// Calculate the Time if we have an Area already
		if ( pool.area > 0 )
		{
			pool.days = pool.area / workerRate;
			pool.hours = fmod(pool.area, workerRate);
			pool.minutes = (fmod(pool.hours, 100.0) / 100) * 60;
			pool.hours /= 100;
		}
		
		// Print the line
		   cout << 
			"LENGTH: " << pool.length << 
			" WIDTH: " << pool.width << 
			" SHALLOW: " << pool.shallowEnd << 
			" DEEP: " << pool.deepEnd <<
			" CUSTOMER: " << pool.customer 
			<< endl;

		j++;


		// Program Output
		outputFile << "CUSTOMER:         " << pool.customer << endl;

		if ( pool.area == 0 )
			outputFile << "TOTAL POOL AREA:  " << "Unable to compute due to incomplete data" << endl;
		else
			outputFile << "TOTAL POOL AREA:  " << fixed << setprecision(2) << pool.area << " feet" << endl;

		if ( pool.days == 0 && pool.hours == 0 && pool.minutes == 0 )
			outputFile << "TIME REQUIRED:    " << "Unable to compute due to incomplete data" << endl;
		else
			outputFile << "TIME REQUIRED:    " << fixed << setprecision(0) << pool.days << " days, " << pool.hours << " hours, and " << pool.minutes << " minutes" << endl;
		
		outputFile << "\n\n\n";
    }

    // Close the files
    inputTextFile.close();
	outputFile.close();
	
	// Finally, pause and exit.
	cout << "Press enter to close this window." << endl;
	getchar();

	return 0;
}
