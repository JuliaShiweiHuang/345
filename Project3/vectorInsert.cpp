#include <iostream>
#include <vector>

using namespace std;

int main () {
	int intArray[7] = {1, 3, 5, 7, 9, 11, 13};
	vector <int> vecList (intArray, intArray+7);
	vector <int>::iterator intVecIter;

	intVecIter = vecList.begin();
	++ intVecIter;
	vecList.insert(intVecIter, 22);
}