//============================================================================
// Name        : 2_1_BufferOverflow_use_string_instead.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string.h>
#include <algorithm>	//std::fill
#include <vector>       // std::vector

//-------------------------------------------------------------------
//prevents magic numbers in code
const int NUMB_ELEMENTS = 10;

//global to this file (Andrew Pohto question)
//allocate array of ints from 0 to NUMB_ELEMENTS-1
//with this syntax you do not know what is inside
//each element of the array
int myIntArray[NUMB_ELEMENTS];

char myCharArray[NUMB_ELEMENTS];
char myCharArrayLong[] = "what if this is more than 10 chars? Program could exit normally (worse possible situation) or you can get a runtime error that is immediately obvious";
//-------------------------------------------------------------------
//generic array explanation
void intArray(){

	//initialize the less than optimal way
	for (int var = 0; var < NUMB_ELEMENTS; ++var) {
		myIntArray[var] = 9;
	}

	//initialize a better way, notice that thius works with arrays
	std::fill_n(myIntArray, NUMB_ELEMENTS, 5);
}
void intVector(){
	std::vector<int> myvector;

	//initialize a better way, fill it all with 9's
	//more standard library goodness, but wait! I copied this code
	//from some website, what header do I use, enter the google, first hit
	//http://www.cplusplus.com/reference/algorithm/fill_n/
	//use <algorithm>
	std::fill_n (myvector.begin(),NUMB_ELEMENTS,9);     	// myvector: 9 9 9 9 9 9 9 9 9 9
	std::fill_n (myvector.begin()+3,3,1);   				// myvector: 9 9 9 1 1 1 9 9 9 9
}
//-------------------------------------------------------------------
//char array
void charArray()
{
	//initialize to 0 (memset copies bytes, VERY good function to know)
	memset(myCharArray,0, NUMB_ELEMENTS);

	//strlen measures until sees '\0'
	//so following will be 0 because of memset above
	int lenCharArray 	= strlen(myCharArray);

	//initialize to B
	memset(myCharArray,'B', NUMB_ELEMENTS);

	//now reads 10 (no '\0'
	lenCharArray 	= strlen(myCharArray);

	//OVERFLOW SAFE, write it (lenCharArray chars copied) note the n in strncpy
	//if you must use functions in string.h use strncpy NOT strcpy
	strncpy(myCharArray, myCharArrayLong, lenCharArray);
}
void testREF(int &myInt);
void testVAL(int myInt);
void test()
{
	int mine=3;
	testREF(mine);  //when return mine = 4
	testVAL(mine);  //when return mine = 4 (not 5)
}
void testREF(int &myInt)	//pass by value
{
	myInt=4;
}

void testVAL(int myInt)		//pass by reference
{
	myInt=5;
}

void charStrings()
{
	//this would work fine ALWAYS
	//since std::string will resize itself if needed
	std::string shortbuff = myCharArrayLong;
}
//lets break things
void overflow(){
	//watch the memory at &mylocalArray and &dontOverwriteMe
	char mylocalArray[NUMB_ELEMENTS];
	char secretPassword[NUMB_ELEMENTS];
	std::fill_n(mylocalArray, NUMB_ELEMENTS, '-');
	std::fill_n(secretPassword, NUMB_ELEMENTS, 'T');

	//OVERFLOW happens next statement because myCharArrayLong is longer than myCharArray
	//THIS IS THE REALLY DANGEROUS CHAR COPY METHOD, dont use it, always use strncpy or
	//better still std::string
	//on some compilers this will crash the program
	//on linux GNU it lets you write to mylocalArray and then it lets you write the space after
	//myLocalArray, here we overwrite what was stored in secretPassword.  If you know how much space
	//is between the 2 arrays then you know exactly what you have written to secretPassword, and thus you
	//know the secret password, think what the issues would be if you could do this to a web hosted site?
	//you overwrite the password with one of your choosing then log in
	strcpy(mylocalArray, myCharArrayLong);

	//this would work fine ALWAYS
	//since std::string will resize itself if needed
	std::string shortbuff = myCharArrayLong;
}
//-------------------------------------------------------------------

int main() {
	intArray();
	charArray();
	overflow();
}


