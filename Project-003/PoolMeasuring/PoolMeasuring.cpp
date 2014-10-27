/*
 *  Gwenn Flores
 *  Samer Kamel
 *  Frank DiCola
 *
 *  SSW 567
 *  Prof. Ardis
 *  Project Assignment 08
 *
 *  GOAL:   Create a program that can calculate the amount of time
 *			required to fill the pool.
 *
 *			a.) The program should compile into an executable file
 *			b.) The program should generate an output file
 *          c.) The program should obtain the day the pool will be completed 
 *				(starting work on April 1st, 2015 8:00:00 am)
 *
 */

#include "stdafx.h"
#include "PoolHeader.h"
#include "PoolFunctions.h"
#include <ctime>


using namespace std;

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

	double timeToPaint;
	double timeToFill;
	double totalTime;

	pools_t pool;

	

	// Find a file
    ifstream inputTextFile;
    inputTextFile.open ("input.txt");

	// Make an output file
	ofstream outputFile;
	outputFile.open ("output.txt");

	outputFile << "OUTPUT OF POOLMEASURING PROGRAM" << endl << endl;

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
		pool = initializePool(pool);
		
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

		if (pool.customer.empty()) {
			pool.customer = "n/a";
		}

		outputFile << "CUSTOMER:                      " << pool.customer << endl;

		// Calculate the area and volume if we have complete information
		if ( pool.length != "n/a" && pool.width != "n/a" && pool.shallowEnd != "n/a" && pool.deepEnd != "n/a" )
		{
			pool.area = calculateArea(pool.length, pool.width, pool.shallowEnd, pool.deepEnd);
			outputFile << "TOTAL POOL AREA:               " << fixed << setprecision(2) << pool.area << " squared feet" << endl;

			pool.volume = calculateVolume(pool.length, pool.width, pool.shallowEnd, pool.deepEnd);
			outputFile << "TOTAL GALLONS OF WATER:        " << fixed << setprecision(2) << pool.volume << " gallons per cubic feet" << endl;
		}
		else {
			outputFile << "TOTAL POOL AREA:               " << "Unable to compute due to incomplete data" << endl;
			outputFile << "TOTAL GALLONS OF WATER:        " << "Unable to compute due to incomplete data" << endl;
		}

		// Calculate time to paint area
		if ( pool.area > 0 ) {
			pool = calculatePoolTime("area", pool);
			outputFile << "TIME REQUIRED FOR PAINTING:    " << pool.days << " days, " << pool.hours << " hours, and " << pool.minutes << " minutes" << endl;
		}
		else {
			outputFile << "TIME REQUIRED FOR PAINTING:    " << "Unable to compute due to incomplete data" << endl;
		}
		
		

		// Calculate time to fill pool
		if( pool.volume > 0 ) {
			pool = calculatePoolTime("volume", pool);
			outputFile << "TIME REQUIRED TO FILL POOL:    " << pool.days << " days, " << pool.hours << " hours, and " << pool.minutes << " minutes" << endl;
		}
		else {
			outputFile << "TIME REQUIRED TO FILL POOL:    " << "Unable to compute due to incomplete data" << endl;
		}

		// Print the line
		printPoolInfo(pool);
		j++;

		

	

		timeToPaint = pool.area / 1200; 
		timeToFill = pool.volume / 12000; 
		totalTime = (((timeToPaint * 24) + (timeToFill * 24) + 8) *60 ) * 60; 
		
		time_t hold_time;
		//hold_time=1427860800 + totalTime;	//cout<<hold_time; //cout<<"The date is: "<<ctime(&hold_time);
		hold_time = 1427889600;

		//outputFile << "THE POOL WILL BE COMPLETED ON: " << ctime(&hold_time) << endl;
		outputFile << "START FROM THIS DATE:          " << ctime(&hold_time) << endl;
		outputFile << "\n\n\n";

    }

    // Close the files
    inputTextFile.close();
	outputFile.close();
	
	// Finally, pause and exit.
	cout << "Press enter to close this window." << endl;
	getchar();

	return 0;

	system("pause");
}