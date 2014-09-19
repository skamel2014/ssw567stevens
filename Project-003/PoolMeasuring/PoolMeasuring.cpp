/*
 *  NAMES GO HERE
 *  Samer Kamel
 *  Frank DiCola
 *
 *  SSW 567
 *  Prof. Ardis
 *  Project Assignment 03
 *
 *  GOAL:   Create a program that reads sample test data
 *          and evaluates each line it reads.
 *
 *		I have created my own set of "rules" for the data:
 *			a.) Length, width, shallow end, and deep end must be positive integers
 *			b.) Length, width, shallow end, and deep end must not contain non-numeric characters
 *			c.) Length must be greater than width.
 *			d.) Length is always greater than an empty value for width.
 *			e.) Shallow end must be smaller than deep end.
 *			f.) Shallow end is always less than an empty value for depth.
 *			g.) The customer's name does not have to be a "name" - it can be whatever garbage is
 *				left after the numeric data has been recorded.
 *			f.) Values that do not fit this criteria are displayed as "n/a" for "not available" to
 *				indicate that they are missing and must be acquired from the customer.
 *
 *
 *
 *
 *
 *
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
	pools_t pool;
	
	// Frank DiCola
    cout << "Pool Measuring -- A Work In Progress" << endl;
    cout << "               by Frank DiCola" << endl;
    cout << endl << endl;

	// Find a file
    ifstream inputTextFile;
    inputTextFile.open ("input.txt");

    // Loop through it until we reach the end
    cout << " = = = File Start = = = " << endl;
    while(!inputTextFile.eof())
    {
		getline(inputTextFile, lineToPrint);
		cout << "Entry " << j << ":   " << lineToPrint << endl;
		
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

		
		// Print the line
		cout << 
			"LENGTH: " << pool.length << 
			" WIDTH: " << pool.width << 
			" SHALLOW: " << pool.shallowEnd << 
			" DEEP: " << pool.deepEnd <<
			" CUSTOMER: " << pool.customer 
			<< endl << endl;;

		j++;
    }

    // Close the file
    inputTextFile.close();
    cout << " = = =  File End  = = = " << endl;
    cout << endl << endl << endl << endl << endl;
	
	// Finally, pause and exit.
	cout << "Press enter to close this window." << endl;
	getchar();

	return 0;
}
