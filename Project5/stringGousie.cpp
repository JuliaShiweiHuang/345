#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

const int MAX = 2000;
const int N   = 10;

string setupstring (char [], int&); //function to generate reference string;
void generateStatistics(int referenceStringLengthFn, string referenceStringFn);

int main () {
   char omega [MAX];
   int omegalength;

   string referenceString = setupstring (omega, omegalength);
   cout << "debug statement, this is referenceString: " << endl;
   cout << referenceString << endl;

   int referenceStringLength = referenceString.length();
   cout << "Debugging statement: Reference String Length is: " << referenceStringLength << endl;

   // store referenceString in an array;
   int referenceStringArray[referenceStringLength]; // array to store reference string;
   for ( int i = 0; i < referenceStringLength; i++ ) {
      referenceStringArray[i] = referenceString.at(i); 
   }
   cout << "before gene" << endl;
   generateStatistics(referenceStringLength, referenceString);
   cout << "after gene" << endl;


   return 0;
}


// function to generate reference string;
string setupstring (char omega[], int& omegalen) {
   int i, j;

   strcpy (omega, "272722");
   for (i = 0; i < N; i++)
      strcat (omega, "28272272927222");

   strcat (omega, "272722");

   for (i = 0; i < N; i++) {
      strcat (omega, "272733733");
 
      for (j = i; j < N; j++)
         strcat (omega, "373338393373737333");
      strcat (omega, "3637322");
   }

   omegalen = strlen (omega);
   return omega;
}

// input: referenceStringLengthFn which is pass by value from my main
void generateStatistics(int referenceStringLengthFn, string referenceStringFn) {
   for ( int windowSize = 1; windowSize < 201; windowSize++ ) {
      int workingSetSize = 0;
      int workingSetArray[windowSize];
      // fill workingSetArray with "*";
      for (int i = 0; i < windowSize; i++ ) {
         workingSetArray[i] = '*';
      }
   
      int workingSetArraySize[referenceStringLengthFn];
      int pageFaultStatus[referenceStringLengthFn];
      // initialize pageFaultCounter to all 0;
      for ( int i = 0; i < referenceStringLengthFn; i++ ) {
         pageFaultStatus[i] = 0;
      }

      workingSetArray[0] = referenceStringFn.at(0);
      for ( int i = 0; i < windowSize; i++ ) {
         if ( workingSetArray[i] != '*' ) {
            workingSetSize ++;
         }
      }
      workingSetArraySize[0] = workingSetSize;
      pageFaultStatus[0] ++; //update pageFault;

      for (int i = 1; i < referenceStringLengthFn; i++) {
         if ( i < windowSize ) {
            bool characterExistStatus = false;
            for ( int j = 0; j < windowSize; j++ ) {
               if ( workingSetArray[j] == referenceStringFn.at(i) ) {
                  characterExistStatus = true;
                  break;
               }//if
            }
            if (characterExistStatus == false) {
               for (int j = 0; j < windowSize; j++ ) {
                  if (workingSetArray[j] == '*') {
                     workingSetArray[j] = referenceStringFn.at(i);
                     break;
                  }
               }
               //update workingSetArraySize;
               workingSetSize++;
               workingSetArraySize[i] = workingSetSize;
               pageFaultStatus[i]++; //update pageFault;
            }//if
            else {
               workingSetArraySize[i] = workingSetSize;
            }
         }// if < windowSize
         else { // (i > windowSize)
            string subStr = referenceStringFn.substr( i - windowSize+1, windowSize );
            if (referenceStringFn.at(i) == referenceStringFn.at(i - windowSize) ) {
               workingSetArraySize[i] = workingSetArraySize[i-1];
            }//if
            else {
               for (int i = 0; i < windowSize; i++ ) {
                  workingSetArray[i] = '*';
               }
               workingSetArray[0] = subStr.at(0);
               int countUniqueElementsInWorkingSetArray = 1;
               for (int i = 1; i < windowSize; i++ ) {
                  int curChar = subStr.at(i);
                  bool check = true;
                  for ( int j = 0; j < i; j++ ) {
                     if (curChar == workingSetArray[j] ) {
                        check = false;
                     }
                     if ( check == true ) {
                        workingSetArray[i] = curChar;
                        countUniqueElementsInWorkingSetArray++;
                     }//if
                  }//for

                  int lastCharInSubStr = subStr.at(windowSize -1);
                  bool checkLastChar = false;
                  for (int j = 0; j < windowSize - 1; j++ ) {
                     if (lastCharInSubStr == subStr.at(j)) {
                        checkLastChar = true;
                     }
                  }
                  if (checkLastChar == false) {
                     pageFaultStatus[i]++;
                  }
                  workingSetArraySize[i] = countUniqueElementsInWorkingSetArray;
               }
            }
         }//else
      }//for


   } //for loop for windowSize from 1 - 201;



}//void





