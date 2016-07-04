#include <iostream>
#include <string>

// global constant;
const int windowSize = 5;
// global variable
int workingSetSize = 0;


using namespace std;
int main () {

	string referenceString = "ABCADABEABCDECE";
	int referenceStringLength = referenceString.length();
	cout << "Debugging statement: Reference String Length is: " << referenceStringLength << endl;

	// fill referenceString in an array;
	int referenceStringArray[referenceStringLength]; // array to store reference string;
	for ( int i = 0; i < referenceStringLength; i++ ) {
		referenceStringArray[i] = referenceString.at(i); 
	}

	//Debugging statement:
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
	// Debugging statemetn:
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
			if ( referenceString.at(i) != workingSetArray[i-1] ) { // debug. NEED TO FIX THIS STATEMENT;

				workingSetArray[i] = referenceString.at(i);
				
				cout << "Debugging statement, at " << i << ": workingSetArray is: ";
				for (int j = 0; j < windowSize; j++ ) {
					cout << workingSetArray[j] << " ";
				}
				cout << endl;

				// update workingSetArraySize;
				workingSetSize = workingSetSize + 1;
				workingSetArraySize[i] = workingSetSize;
				cout << "at " << i << ": workingSetArraySize is: " << workingSetArraySize[i] << endl;

				// update pageFault;
				pageFaultStatus[i]++;
				cout << "at " << i << ": pageFaultStatus is: " << pageFaultStatus[i] << endl;

			} // if 
			else { // the new character is repectative from the workingSetArraySize;
				// don't update workingSetArray;
				cout << "Debugging statement, at " << i << "workingSetArray is: ";
				for (int j = 0; j < windowSize; j++ ) {
					cout << workingSetArray[j] << " ";
				}
				cout << endl;

				//update workingSet ArraySize;
				workingSetArraySize[i] = workingSetSize;
				cout << "at " << i << ": workingSetSize is: " << workingSetSize << endl;

				// don't update PageFault;
				cout << "at " << i << ": pageFaultStatus is: " << pageFaultStatus[i] << endl;


			}


		}// i < windowSize;
		else { // i >= windowSize
			cout << i << " not yet" << endl;
		}




	} //for i from 1 to referenceStringLength;




















} //main