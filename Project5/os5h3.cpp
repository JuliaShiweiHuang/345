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
	char referenceStringArray[referenceStringLength]; // array to store reference string;
	for ( int i = 0; i < referenceStringLength; i++ ) {
		referenceStringArray[i] = referenceString.at(i); 
	}

	//Debugging statement:
	cout << "Cout my referenceString" << endl;
	for (int i = 0; i < referenceStringLength; i++) {
		cout << referenceString.at(i) << " ";
	}
	cout << endl;


	char workingSetArray[windowSize]; // array to store the current working set;
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

			} //else
		}//if ( i < windowSize )
		else {
			cout << i << " not yet" << endl;
		}


	}//giant for loop



} //main;















