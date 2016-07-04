#include <iostream>
#include <string>

// global constant;
const int windowSize = 4;
// global variable
int workingSetSize = 0;


using namespace std;
int main () {

	// string referenceString = "ABCADABEABCDECE";
	string referenceString = "272722282722729272222827227292722228272272927222282722729272222827227292722228272272927222282722729272222827227292722228272272927222282722729272222727222727337333733383933737373333733383933737373333733383933737373333733383933737373333733383933737373333733383933737373333733383933737373333733383933737373333733383933737373333733383933737373333637322272733733373338393373737333373338393373737333373338393373737333373338393373737333373338393373737333373338393373737333373338393373737333373338393373737333373338393373737333363732227273373337333839337373733337333839337373733337333839337373733337333839337373733337333839337373733337333839337373733337333839337373733337333839337373733336373222727337333733383933737373333733383933737373333733383933737373333733383933737373333733383933737373333733383933737373333733383933737373333637322272733733373338393373737333373338393373737333373338393373737333373338393373737333373338393373737333373338393373737333363732227273373337333839337373733337333839337373733337333839337373733337333839337373733337333839337373733336373222727337333733383933737373333733383933737373333733383933737373333733383933737373333637322272733733373338393373737333373338393373737333373338393373737333363732227273373337333839337373733337333839337373733336373222727337333733383933737373333637322";
	int referenceStringLength = referenceString.length();
	cout << "Debugging statement: Reference String Length is: " << referenceStringLength << endl;

	// fill referenceString in an array;
	int referenceStringArray[referenceStringLength]; // array to store reference string;
	for ( int i = 0; i < referenceStringLength; i++ ) {
		referenceStringArray[i] = referenceString.at(i); 
	}

	//Debugging statement:
	cout << "Cout my referenceString" << endl;
	for (int i = 0; i < referenceStringLength; i++) {
		cout << referenceString.at(i) << " ";
	}
	cout << endl;


	int workingSetArray[windowSize]; // array to store the current working set;
	//fill workingSetArray with '*';
	for (int i = 0; i < windowSize; i++ ) {
		workingSetArray[i] = '*';
	}


	int workingSetArraySize[referenceStringLength]; // array to store the size of the current working set;
	int pageFaultStatus[referenceStringLength]; // array to store the status of page fault. In addition, 0 means no page fault; 1 means page fault exists;
	// initialize pageFaultCounter to all 0;
	for ( int i = 0; i < referenceStringLength; i++ ) {
		pageFaultStatus[i] = 0; //initially set up to 0 meaning there is no page fault;
	}

	//put the first character from referenceString to workingSetArray;
	workingSetArray[0] = referenceStringArray[0];

	// Debugging statement:
	cout << "at 0, workingSetArray: " << workingSetArray[0] << endl;

	// update workingSetArraySize;
	for (int i = 0; i < windowSize; i++ ) {
		if ( workingSetArray[i] != '*' ) {
			workingSetSize ++;
		}
	}
	workingSetArraySize[0] = workingSetSize;


	//Debugging statement:
	cout << "at 0, workingSetArraySize: " << workingSetArraySize[0] << endl;

	//update pageFault;
	pageFaultStatus[0] ++;
	cout << "at 0, pageFaultStatus: " << pageFaultStatus[0] << endl;

	for (int i = 1; i < referenceStringLength; i++ ) {
		if ( i < windowSize ) {
			// function to check whether there is character in this workingSetArray;
			bool characterExistStatus = false;
			for ( int j = 0; j < windowSize; j++ ) {
				if (workingSetArray[j] == referenceString.at(i)) {
					characterExistStatus = true;
					break;
				}
			}
			if (characterExistStatus == false) {
				for (int j = 0; j < windowSize; j++ ) {
					if (workingSetArray[j] == '*') {
						cout << "this is j: " << j << " and this is the workingSetArray at j: " << workingSetArray[j] << endl;
						cout << "this is referencestring at i " << "and i is: " << i << " and referencestring is: " << referenceString.at(i) << endl;
						cout << "and j stops at: " << j << endl;
						workingSetArray[j] = referenceString.at(i);
						break;
					}
				}
				// workingSetArray[i] = referenceString.at(i); // need to debug this part
				
				cout << endl;
				cout << "at " << i << " characterExistStatus is: " << characterExistStatus << endl;
				cout << "A) debugging statement, at " << i << " : workingSetArray is: ";
				for (int j = 0; j < windowSize; j++ ) {
					cout << j << ": " << workingSetArray[j] << " ";
				}
				cout << endl;

				// update workingSetArraySize;
				workingSetSize ++;
				workingSetArraySize[i] = workingSetSize;
				cout << "at " << i << " :workingSetArraySize is: " << workingSetArraySize[i] << endl;

				// update pageFault;
				pageFaultStatus[i] ++;
				cout << "at " << i << " :pageFaultStatus is: " << pageFaultStatus[i] << endl;
				cout << endl;
			} //if

			else { // characterExistStatus == true;
				//don't update workingSetArray;
				cout << endl;
				cout << "at " << i << " characterExistStatus is: " << characterExistStatus << endl;
				cout << "B) debugging statement, at " << i << " : workingSetArray is: ";
				for ( int j = 0; j < windowSize; j++ ) {
					cout << workingSetArray[j] << " ";
				} //for
				cout << endl;

				//workingSetArraySize;
				workingSetArraySize[i] = workingSetSize;
				cout << "at " << i << " :workingSetSize is: " << workingSetSize << endl;

				// don't update pageFault;
				cout << "at " << i << " :pageFault is: " << pageFaultStatus[i] << endl;
				cout << endl;
			} //else
		}//if ( i < windowSize )
		else { // i >= windowSize;
			string subStr = referenceString.substr(i - windowSize+1, windowSize);
			if ( referenceString.at(i) == referenceString.at(i - windowSize) ) {
				// debugging statement;
				cout << "This is referenceString at i and i is " << i << " " << referenceString.at(i) << endl;
				cout << "This is referenceString at i - windowSize " << referenceString.at(i - windowSize) << endl;
				// don't update workingSetArray;
				// use the old workingSetArraySize;
				workingSetArraySize[i] = workingSetArraySize[i-1];
				cout << "at " << i << " workingSetArray size is: " << workingSetArraySize[i] << endl;

				// debug statement to see what is the elements in my current working set array;
				for ( int j = 0; j < windowSize; j++ ) {
					cout << workingSetArray[j] << " ";
				} //for
				cout << endl;


				// no pageFault;
				// so don't update pageFault;
				cout << "at " << i << " pageFault is " << pageFaultStatus[i] << endl;
				cout << endl;
			}
			else { //referenceString.at(i) != referenceString.at(i - windowSize)
				// since I already have the subsString;
				// Put the subString into the array with all unique elements;
				cout << "at " << i << ": the referenceString.at(i) is: " << referenceString.at(i) << endl;
				for (int i = 0; i < windowSize; i++ ) {
					workingSetArray[i] = '*';
				}
				cout << "at " << i << ": my substring is: " << subStr << endl;
				workingSetArray[0] = subStr.at(0);
				cout << "my workingSetArray[0] is: " << workingSetArray[0] << endl;
				int countUniqueElementsInWorkingSetArray = 1; // update unique elements in workingSetArray;

				// debug statement;
				// before fill the rest of my string from 1-4; first check with my workingSetArray;
				cout << "this is before filling the rest of the string in the workingSetArray." << endl;
				for (int j = 0; j < windowSize; j++ ) {
					cout << workingSetArray[j] << " ";
				}
				cout << endl;

				for ( int i = 1; i < windowSize; i++ ) {
					int curChar = subStr.at(i);
					cout << "at " << i << ", my curChar is: " << curChar << endl;
					bool check = true;
					for ( int j = 0; j < i; j++ ) {
						if ( curChar == workingSetArray[j] ) {
							check = false;
						}
					}
					if ( check == true ) {
						workingSetArray[i] = curChar;
						countUniqueElementsInWorkingSetArray ++;
					} //if
				} //for


				// this is just to check whether my subStr[windowSize] matches with any previous element in my subStr;
				// if ( matches ) {
				// 	do not increment y pageFaultStatus
				// }
				// else {
				// 	increment my pageFault Status
				// }
				int lastCharInSubStr = subStr.at(windowSize-1);
				cout << "my last character in my substring is: " << lastCharInSubStr << endl;
				// check whether my last character in my subString matches with my current substring;
				// if (it matches) {I don't increment pageFault};
				// else {I increment pageFault};
				bool checkLastChar = false; // check whether last character under my substring matches with any characters under subString;
				// false means the last character doesn't exist under my subString;

				for (int j = 0; j < windowSize-1; j++ ) {
					if (lastCharInSubStr == subStr.at(j)) {
						cout << "at " << j << ", my subStr at j is: " << subStr.at(j) << endl;
						checkLastChar = true;
					}
				}
				if (checkLastChar == false) {// last character under my subString doesn't match with any character under my subString;
					//incretment pageFault;
					cout << "debug statement: check whether I go through if Statement" << endl;
					pageFaultStatus[i]++;
					cout << "this is my pageFaultStatus at i = " << i << " and page fault is: " << pageFaultStatus[i] << endl;
				}
				cout << "at i = " << i << ", my pageFaultStatus is: " << pageFaultStatus[i] << endl;
				// else {
					//don't do anything with my pageFaultStatus;

				// }
				// check with the pageFaultStatus;
				
				cout << "at " << i << " pageFaultStatus is: " << pageFaultStatus[i] << endl;
				cout << endl;

				// debug statement;
				// this is after filling the subString in my array
				cout << "this is after filling the subString in my array" << endl;
				for (int j = 0; j < windowSize; j++ ) {
					cout << workingSetArray[j] << " ";
				}
				cout << endl;

				workingSetArraySize[i] = countUniqueElementsInWorkingSetArray;
				// debug statement;
				cout << "at " << i << " workingSetArraySize is: " << workingSetArraySize[i] << endl;
				

			} //else

		}


	}//giant for loop


	cout << "***************************" << endl;
	cout << "total number of page faults:" << endl;
	int totalPageFault = 0;
	for (int i = 0; i < referenceStringLength; i++ ) {
		if (pageFaultStatus[i] == 1) {
			totalPageFault ++;
		}
	}
	cout << "total page fault is: " << totalPageFault << endl;

	int workingSetSizeCounter = 0;
	for (int i = 0; i < referenceStringLength; i++ ) {
		workingSetSizeCounter = workingSetSizeCounter + workingSetArraySize[i];
	}
	cout << "total workingSetSize is: " << workingSetSizeCounter << endl;	
	cout << "average working set size: " << endl;
	float averageWorkingSetSize = (float) workingSetSizeCounter / (float) referenceStringLength;
	cout << "averageWorkingSetSize is: " << averageWorkingSetSize << endl;

	cout << "average page fault rate is: " << endl;
	float averagePageFaultRate = (float) totalPageFault / (float) referenceStringLength;
	cout << "average page fault rate is: " << averagePageFaultRate << endl;
	cout << "***************************" << endl;



} //main;















