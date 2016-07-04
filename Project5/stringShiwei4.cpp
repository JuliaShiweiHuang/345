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
void generateStatistics(string referenceStringFn, int windowSizeFn, int workingSetArray[], int workingSetSizeFn, int workingSetArraySize[], int pageFaultStatus[]);
void printStatistics(string referenceStringFn, int pageFaultStatus[], int workingSetArraySize[], int windowSizeFn);

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


void generateStatistics(string referenceStringFn, int windowSizeFn, int workingSetArray[], int workingSetSizeFn, int workingSetArraySize[], int pageFaultStatus[]) {
	int referenceStringLength = referenceStringFn.length();
    for (int i = 1; i < referenceStringLength; i++) {
         if ( i < windowSizeFn ) {
            bool characterExistStatus = false;
            for ( int j = 0; j < windowSizeFn; j++ ) {
               if ( workingSetArray[j] == referenceStringFn.at(i) ) {
                  characterExistStatus = true;
                  break;
               }//if
            }
            if (characterExistStatus == false) {
               for (int j = 0; j < windowSizeFn; j++ ) {
                  if (workingSetArray[j] == '*') {
                     workingSetArray[j] = referenceStringFn.at(i);
                     break;
                  }
               }
               workingSetSizeFn++;
               workingSetArraySize[i] = workingSetSizeFn;
               pageFaultStatus[i]++; //update pageFault;
            }//if
            else {
               workingSetArraySize[i] = workingSetSizeFn;
            }
         }// if < windowSize
         else { // (i > windowSize)
            string subStr = referenceStringFn.substr( i - windowSizeFn+1, windowSizeFn );
            if (referenceStringFn.at(i) == referenceStringFn.at(i - windowSizeFn) ) {
               workingSetArraySize[i] = workingSetArraySize[i-1];
            }//if
            else {
               for (int i = 0; i < windowSizeFn; i++ ) {
                  workingSetArray[i] = '*';
               }
               workingSetArray[0] = subStr.at(0);
               int countUniqueElementsInWorkingSetArray = 1;
               for ( int i = 1; i < windowSizeFn; i++ ) {
                  int curChar = subStr.at(i);
                  bool check = true;
                  for ( int j = 0; j < i; j++ ) {
                     if (curChar == workingSetArray[j] ) {
                        check = false;
                     }
                  }
                     if ( check == true ) {
                        workingSetArray[i] = curChar;
                        countUniqueElementsInWorkingSetArray++;
                     }//if
               }//for
               int lastCharInSubStr = subStr.at(windowSizeFn -1);
               bool checkLastChar = false;
               for (int j = 0; j < windowSizeFn - 1; j++ ) {
                  if (lastCharInSubStr == subStr.at(j)) {
                     checkLastChar = true;
                  }
               }
               if (checkLastChar == false) {
                  pageFaultStatus[i]++;
               }
               workingSetArraySize[i] = countUniqueElementsInWorkingSetArray;
            }//else
         }//else
      }//for

}



void printStatistics(string referenceStringFn, int pageFaultStatus[], int workingSetArraySize[], int windowSizeFn) {
   // cout << setw(3) << "W" << setw(7) << "P(W)" << setw(12) << "W(W)" << setw(14) << "F(W)" << endl;
   // cout << "*****************************************************" << endl;
   int totalPageFault = 0;
   int referenceStringLength = referenceStringFn.length();
   for ( int i = 0; i < referenceStringLength; i++ ) {
         if (pageFaultStatus[i] == 1) {
            totalPageFault++;
         }
   }
   int workingSetSizeCounter = 0;
   for (int i = 0; i < referenceStringLength; i++ ) {
         workingSetSizeCounter = workingSetSizeCounter + workingSetArraySize[i];
   }
   float averageWorkingSetSize = (float) workingSetSizeCounter / (float) referenceStringLength;
   float averagePageFaultRate = (float) totalPageFault / (float) referenceStringLength;
   cout << setw(3) << windowSizeFn << setw(7) << totalPageFault << setw(12) << setprecision(3) << fixed << averageWorkingSetSize  << setw(14) << setprecision(3) << fixed << averagePageFaultRate << endl; 


}




int main () {
   char omega [MAX];
   int omegalength;

   string referenceString = setupstring (omega, omegalength);
   int referenceStringLength = referenceString.length();
   int referenceStringArray[referenceStringLength]; // array to store reference string;
   for ( int i = 0; i < referenceStringLength; i++ ) {
      referenceStringArray[i] = referenceString.at(i); 
   }
   cout << "*****************************************************" << endl;
   cout << setw(3) << "W" << setw(7) << "P(W)" << setw(12) << "W(W)" << setw(14) << "F(W)" << endl;

   for ( int windowSize = 1; windowSize < 201; windowSize++ ) {
      int workingSetSize = 0;
      int workingSetArray[windowSize];
      for (int i = 0; i < windowSize; i++ ) {
         workingSetArray[i] = '*';
      }
      workingSetArray[0] = referenceString.at(0);
      int workingSetArraySize[referenceStringLength];
      int pageFaultStatus[referenceStringLength];
      for ( int i = 0; i < referenceStringLength; i++ ) {
      	pageFaultStatus[i] = 0;
   	  }
   	  for ( int i = 0; i < windowSize; i++ ) {
         if ( workingSetArray[i] != '*' ) {
            workingSetSize ++;
         }
      }

      workingSetArraySize[0] = workingSetSize;
      pageFaultStatus[0] ++; //update pageFault;

      generateStatistics(referenceString, windowSize, workingSetArray, workingSetSize, workingSetArraySize, pageFaultStatus);
   	printStatistics(referenceString, pageFaultStatus, workingSetArraySize, windowSize);
   	  

   }
   cout << "*****************************************************" << endl;


} //main





