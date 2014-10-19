/*
 *  Frank DiCola
 *  SSW 567
 *  Prof. Ardis
 *  Project Assignment 02
 *
 *  GOAL:   Create a series of functions used
 *			to evaluate data and back those
 *			functions up with successful unit tests.
 */

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

bool isPositiveInteger( string s )
{
	int i = 0;
	int sSize;

	sSize = s.size();
	
	// cout << "S has size of " << sSize << "." << endl;
	
	// Is the string a positive integer?
	if (!s.empty())
	{
		// cout << "NOT EMPTY" << endl;
		
		while (i < sSize)
		{
			// cout << s[i] << endl;
	
			if (s[i] == 45)
			{
				cout << "  -ERROR: Negative number provided in " << s << "." << endl;
				return false;
			}
			if (s[i] < 48 || s[i] > 57)
			{
				cout << "  -ERROR: Non-number character encountered in " << s << "." << endl;
				return false;
			}

			i++;
		}

		// cout << s << " is a number, you guys!" << endl;

		return true;
	}


	// Warning
	cout << "  -ERROR: Input value was empty." << endl;

	return false;
}

bool isGreaterThan( string s1, string s2 )
{
	if ( !s1.empty() && isPositiveInteger(s1))
	{
		if (s2.empty() || !isPositiveInteger(s2) || stoi(s1) >= stoi(s2))
			return true;
	}
	else
	{
		cout << "  -ERROR: First value (" << s1 << ") is not a positive integer." << endl;
	}

	return false;
}

bool isLessThan( string s1, string s2 )
{
	if ( !s1.empty() && isPositiveInteger(s1))
	{
		if (s2.empty() || !isPositiveInteger(s2) || stoi(s1) <= stoi(s2))
			return true;
	}
	else
	{
		cout << "  -ERROR: First value (" << s1 << ") is not a positive integer." << endl;
	}

	return false;
}

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