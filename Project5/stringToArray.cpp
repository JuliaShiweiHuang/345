#include <iostream>
#include <string>

using namespace std;
int main () {
	cout << "debug " << endl;
	string referenceString = "ADABE";
	char array[5];
	array[0] = referenceString.at(0);
	cout << "debug at array[0]  " << referenceString.at(0) << endl;
	int counterForUniqueElementsInArray = 1;

	for (int i = 1; i < 5; i++ ) {
		char substr = referenceString.at(i);
		bool check = true;
		for ( int j = 0; j < i; j++ ) {
			if ( substr == array[j] ) {
				check = false;
			}
		}
		if ( check == true ) { // new reading element is unique;
			array[i] = substr;
			cout << "debug at " << i << " " << array[i] << endl;
			counterForUniqueElementsInArray ++;
			cout << "debug at " << i << " " << " this is counter for unique elements " << counterForUniqueElementsInArray << endl;

		}

	}




}