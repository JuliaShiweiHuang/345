#include <iostream>
#include <string>

const int windowSize = 5;

using namespace std;
int main () {

	string referenceString = "ABCADABEABCDECE";
	int referenceStringLength = referenceString.length();
	cout << "Reference String Length is: " << referenceStringLength << endl;

	// put referenceString in an array;
	int referenceStringArray[referenceStringLength]; // array to store reference string;
	int workingSetArray[windowSize]; // array to store the current working set;
	int workingSetArraySize[referenceStringLength]; // array to store the size of the current working set;
	int pageFaultStatus[referenceStringLength]; // array to store the status of page fault. In addition, 0 means no page fault; 1 means page fault exists;
	// initialize pageFaultCounter to all 0;
	for ( int i = 0; i < referenceStringLength; i++ ) {
		pageFaultStatus[i] = 0; //initially set up to 0 meaning there is no page fault;
	}
	
	// using a for loop to put the referenceString string into my array;
	for ( int i = 0; i < referenceStringLength; i++ ) {
		referenceStringArray[i] = referenceString.at(i);
		// workingSetArray[i] = referenceString.at(i);
		// debug statement;
		// cout << "check " << i << ": " << referenceStringArray[i] << endl;
	}


	// initialize workingSetArray[] to '*';
	for ( int i = 0; i < windowSize; i++ ) {
		workingSetArray[i] = '*';
		workingSetArray[i] = referenceString.at(i);
	}







	for ( int i = 0; i < referenceStringLength; i++ ) {
		if ( i < windowSize ) { // if string at i is less than the window size;
			// int characterStorage = referenceString.at(i);

			// using a for loop to check the working set array whether already has reference at i;
			bool characterExistStatus; // characterExist represents whether there exists the same character from the workingsetArray as the referenceString at i;
			for ( int j = 0; j < windowSize; j++ ) {
				if ( workingSetArray[i] == referenceString.at(i) ) {
					characterExistStatus = true; //update characterExist status;
				}
				else {
					characterExistStatus = false;
					break; // once find there is the character match, then exit the for loop;
				}
			}

			if ( characterExistStatus == false ) { // if the workingSetArray doesn't havee the referenceString at i;
				//add referenceString.at(i) into workingSetArray[i];
				workingSetArray[i] = referenceString.at(i);
				pageFaultStatus[i] ++; //update pageFault status from 0 to 1 meaning there is page fault;
				
				//count number of characters in workingSetArray and update workingSetArraySize at i;
				int counterNumberOfCharacterInWorkingSet;
				for ( int a = 0; a < windowSize; a++ ) {
					if ( workingSetArray[i] != '*' ) {
						counterNumberOfCharacterInWorkingSet ++;
					}
				}
				workingSetArraySize[i] = counterNumberOfCharacterInWorkingSet; //put the counter number into the location i of the workingSet Array;
			}
			else { // the workingSetArray already has the referenceString at i;
				// don't add anything into working set;
				// don't do anything with pageFault counter. Meaning there is no page fault;
				// count number of characters in workingSetArray and update workingSetArraySize at i;
				int counterNumberOfCharacterInWorkingSet;
				for ( int a = 0; a < windowSize; a++ ) {
					if ( workingSetArray[i] != '*' ) {
						counterNumberOfCharacterInWorkingSet ++;
					}
				}
				workingSetArraySize[i] = counterNumberOfCharacterInWorkingSet; //put the counter number into the location i of the workingSet Array;
			}

		} // if string at i is less than the window size;
		else { // if string at i is more than the window size;
			for ( int j = windowSize; j < referenceStringLength; j++ ) {
				int characterStorage = referenceString.at(j);
				//get the substring from referenceString from (i-5) to i; 
				string referenceStringSubString = referenceString.substr(i-5, windowSize); //get the substring based on the window size;
				
				// check whether the working set array already have reference string i;
				bool characterExistStatus; // characterExist represents whether there exists the same character from the workingsetArray as the referenceString at i;
				for (int a = 0; a < windowSize; a++ ) {
					if ( workingSetArray[i] == referenceString.at(j) ) {
						characterExistStatus = true;
					}
					else {
						characterExistStatus = false;
						break;
					}
				}
				if ( characterExistStatus == false ) { // if the working set array doesn't have the referenceString at i;
					pageFaultStatus[i]++; //increment page fault counter;

					// write referenceStringSubString non-overlay character into workingSetArray;
					workingSetArray[0] = referenceStringSubString.at(0);
					int i = 1;
					for ( int stringCounter = 0; stringCounter < windowSize; stringCounter ++ ) {
						if ( referenceStringSubString.at(i) != workingSetArray[i-1] ) {
							workingSetArray[i] = referenceStringSubString.at(i);
							i++;
						} 
						else {
							i++;
						}
					}
					int counter = 0;
					for ( int i = 0; i < windowSize; i++ ) {
						if ( workingSetArray[i] != '*' ) {
							counter ++;
						}
					}

					workingSetArraySize[i] = counter;
				}
				
				else { // if working set already has the letter from the working set;
					// don't add anything to the working set array;
					// don't update the status for page fault;

					// write down the current working set;
					int i = 1;
					workingSetArray[0] = referenceStringSubString.at(0);
					for ( int stringCounter = 0; stringCounter < windowSize; stringCounter ++ ) {
						if ( referenceStringSubString.at(i) != workingSetArray[i-1] ) {
							workingSetArray[i] = referenceStringSubString.at(i);
							i++;
						}
						else {
							i++;
						}
					}

					// count number of characters in the workingSetArray and update the workingSetArraySize;
					int counter = 0;
					for ( int i = 0; i < windowSize; i++ ) {
						if ( workingSetArray[i] != '*' ) {
							counter ++;
						}
					}
					workingSetArraySize[i] = counter;

				}//else

			}//for
		} //else
	}//for

		
} //main










