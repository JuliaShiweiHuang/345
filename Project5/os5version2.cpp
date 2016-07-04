#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string.h>
#include <iomanip>


using namespace std;
int main () {
	cout << setw(3) << "W" << setw(7) << "P(W)" << setw(12) << "W(W)" << setw(14) << "F(W)" << endl;
	cout << "*****************************************************" << endl;

	for ( int windowSize = 1; windowSize < 201; windowSize ++ ) {
		int workingSetSize = 0;
		string referenceString = "272722282722729272222827227292722228272272927222282722729272222827227292722228272272927222282722729272222827227292722228272272927222282722729272222727222727337333733383933737373333733383933737373333733383933737373333733383933737373333733383933737373333733383933737373333733383933737373333733383933737373333733383933737373333733383933737373333637322272733733373338393373737333373338393373737333373338393373737333373338393373737333373338393373737333373338393373737333373338393373737333373338393373737333373338393373737333363732227273373337333839337373733337333839337373733337333839337373733337333839337373733337333839337373733337333839337373733337333839337373733337333839337373733336373222727337333733383933737373333733383933737373333733383933737373333733383933737373333733383933737373333733383933737373333733383933737373333637322272733733373338393373737333373338393373737333373338393373737333373338393373737333373338393373737333373338393373737333363732227273373337333839337373733337333839337373733337333839337373733337333839337373733337333839337373733336373222727337333733383933737373333733383933737373333733383933737373333733383933737373333637322272733733373338393373737333373338393373737333373338393373737333363732227273373337333839337373733337333839337373733336373222727337333733383933737373333637322";
		int referenceStringLength = referenceString.length();
		int referenceStringArray[referenceStringLength]; // array to store reference string;
		for ( int i = 0; i < referenceStringLength; i++ ) {
			referenceStringArray[i] = referenceString.at(i); 
		}

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

		// update workingSetArraySize;
		for (int i = 0; i < windowSize; i++ ) {
			if ( workingSetArray[i] != '*' ) {
				workingSetSize ++;
			}
		}
		workingSetArraySize[0] = workingSetSize;
	
		//update pageFault;
		pageFaultStatus[0] ++;

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
							workingSetArray[j] = referenceString.at(i);
							break;
						}
					}
					// update workingSetArraySize;
					workingSetSize ++;
					workingSetArraySize[i] = workingSetSize;
					// update pageFault;
					pageFaultStatus[i] ++;
				} //if

				else { // characterExistStatus == true;
					//don't update workingSetArray;
					//workingSetArraySize;
					workingSetArraySize[i] = workingSetSize;
					// don't update pageFault;
				} //else
			}//if ( i < windowSize )
			else { // i >= windowSize;
				string subStr = referenceString.substr(i - windowSize+1, windowSize);
				if ( referenceString.at(i) == referenceString.at(i - windowSize) ) {
					// don't update workingSetArray;
					// use the old workingSetArraySize;
					workingSetArraySize[i] = workingSetArraySize[i-1];
					// no pageFault;
					// so don't update pageFault;
					
				}
				else { //referenceString.at(i) != referenceString.at(i - windowSize)
					// since I already have the subsString;
					// Put the subString into the array with all unique elements;
					for (int i = 0; i < windowSize; i++ ) {
						workingSetArray[i] = '*';
					}
					workingSetArray[0] = subStr.at(0);
					int countUniqueElementsInWorkingSetArray = 1; // update unique elements in workingSetArray;

					for ( int i = 1; i < windowSize; i++ ) {
						int curChar = subStr.at(i);
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
				
					int lastCharInSubStr = subStr.at(windowSize-1);
					bool checkLastChar = false; // check whether last character under my substring matches with any characters under subString;

					for (int j = 0; j < windowSize-1; j++ ) {
						if (lastCharInSubStr == subStr.at(j)) {
							checkLastChar = true;
						}
					}
					if (checkLastChar == false) {// last character under my subString doesn't match with any character under my subString;
						pageFaultStatus[i]++;
					}
					workingSetArraySize[i] = countUniqueElementsInWorkingSetArray;
				} //else

			}

		}//giant for loop

		int totalPageFault = 0;
		for (int i = 0; i < referenceStringLength; i++ ) {
			if (pageFaultStatus[i] == 1) {
				totalPageFault ++;
			}
		}

		int workingSetSizeCounter = 0;
		for (int i = 0; i < referenceStringLength; i++ ) {
			workingSetSizeCounter = workingSetSizeCounter + workingSetArraySize[i];
		}
		float averageWorkingSetSize = (float) workingSetSizeCounter / (float) referenceStringLength;
		float averagePageFaultRate = (float) totalPageFault / (float) referenceStringLength;
		cout << setw(3) << windowSize << setw(7) << totalPageFault << setw(12) << setprecision(3) << fixed << averageWorkingSetSize  << setw(14) << setprecision(3) << fixed << averagePageFaultRate << endl; 
		


	}
		cout << "*****************************************************" << endl;


} //main;















