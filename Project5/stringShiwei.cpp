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
void generateStatistics(int referenceStringLengthFn, string referenceStringFn, int pageFaultStatusFn[], int workingSetArraySizeFn[]);
void printStatistics( int referenceStringLengthFn, int pageFaultStatusFn[], int workingSetArraySizeFn[] );

int main () {
   char omega [MAX];
   int omegalength;

   string referenceString = setupstring (omega, omegalength);
   // cout << "debug statement, this is referenceString: " << endl;
   // cout << referenceString << endl;

   int referenceStringLength = referenceString.length();
   // cout << "Debugging statement: Reference String Length is: " << referenceStringLength << endl;

   // store referenceString in an array;
   int referenceStringArray[referenceStringLength]; // array to store reference string;
   for ( int i = 0; i < referenceStringLength; i++ ) {
      referenceStringArray[i] = referenceString.at(i); 
   }

   int pageFaultStatus[referenceStringLength];
   // initialize pageFaultCounter to all 0;
   for ( int i = 0; i < referenceStringLength; i++ ) {
      pageFaultStatus[i] = 0;
   }
   int workingSetArraySize[referenceStringLength];




   generateStatistics(referenceStringLength, referenceString, pageFaultStatus, workingSetArraySize);
   printStatistics(referenceStringLength, pageFaultStatus, workingSetArraySize);


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
void generateStatistics(int referenceStringLengthFn, string referenceStringFn, int pageFaultStatus[], int workingSetArraySize[]) {
   for ( int windowSize = 199; windowSize < 200; windowSize++ ) {
      int workingSetSize = 0;
      int workingSetArray[windowSize];
      // fill workingSetArray with "*";
      for (int i = 0; i < windowSize; i++ ) {
         workingSetArray[i] = '*';
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
               for ( int i = 1; i < windowSize; i++ ) {
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
               
            }//else
         }//else
      }//for

   } //for loop for windowSize from 1 - 201;

}//void


void printStatistics( int referenceStringLengthFn, int pageFaultStatus[], int workingSetArraySize[] ) {
   cout << setw(3) << "W" << setw(7) << "P(W)" << setw(12) << "W(W)" << setw(14) << "F(W)" << endl;
   cout << "*****************************************************" << endl;


   for ( int windowSize = 1; windowSize < 200; windowSize++ ) {
      int totalPageFault = 0;
      for ( int i = 0; i < referenceStringLengthFn; i++ ) {
         if (pageFaultStatus[i] == 1) {
            // cout << "168:   " << pageFaultStatus[i] << " ";
            totalPageFault++;
         }
      }

      int workingSetSizeCounter = 0;
      for (int i = 0; i < referenceStringLengthFn; i++ ) {
         workingSetSizeCounter = workingSetSizeCounter + workingSetArraySize[i];
      }
      float averageWorkingSetSize = (float) workingSetSizeCounter / (float) referenceStringLengthFn;
      float averagePageFaultRate = (float) totalPageFault / (float) referenceStringLengthFn;
      cout << setw(3) << windowSize << setw(7) << totalPageFault << setw(12) << setprecision(3) << fixed << averageWorkingSetSize  << setw(14) << setprecision(3) << fixed << averagePageFaultRate << endl; 
      
   }//for
   cout << "*****************************************************" << endl;

}






/*

shiweis-mbp:Desktop Shiwei$ ./a.out
  W   P(W)        W(W)          F(W)
*****************************************************
  1    879           1      0.675115
  2    333     1.67435       0.25576
  3    313     1.92934      0.240399
  4    292      2.1682       0.22427
  5    237     2.39017      0.182028
  6    236     2.56989       0.18126
  7    208     2.74808      0.159754
  8    208     2.90476      0.159754
  9    153     3.06144      0.117512
 10    153     3.17588      0.117512
 11    153     3.29032      0.117512
 12    153     3.40476      0.117512
 13    153      3.5192      0.117512
 14    135     3.63364      0.103687
 15    135     3.73426      0.103687
 16    135     3.83487      0.103687
 17    135     3.93548      0.103687
 18     45      4.0361     0.0345622
 19     45     4.06682     0.0345622
 20     45     4.09754     0.0345622
 21     45      4.1275     0.0345622
 22     45     4.15745     0.0345622
 23     45      4.1874     0.0345622
 24     45     4.21736     0.0345622
 25     45     4.24731     0.0345622
 26     45     4.27727     0.0345622


*/





