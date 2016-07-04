/*
Shiwei Huang
Operating Systems: OS5
The purpose of the program: 
Simulate a working set memory management policy and generate some statistics. 
In addition, the generated statistics will be used to answer some question and graph the output.

Input: 
1. referenceString is given. 
2. Window size

Output:
1. In the terminal, total number of page faults, average working set size, average page fault rate will be generated with the given windowSize from 1 - 200.
*/



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

/*
Function purpose: the purpose of the setupstring function is to generate the entire referenceString.
The notion (2722)^n means repeat 2722 n times. 
Input: N constant preassigned
Output: the entire reference string is generated
Return value: function setupstring returns the referenceString that returned to the main function;
*/ 
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


/*
Function purpose: generateStatistics will generate all the information (total number of page fault, total working set size needed) for one window size;

Pre-condition: 
pass by value: referenceString from the main passed to referenceStringFn 
pass by value: windowSize from the main passed to windowSizeFn
pass by reference: workingSetArray from the main was initialized to '*'
pass by value: workingSetSize from the main always initialized to 0. WorkingSetSize documented at the current window size, from 1 to referenceString length, its workingSetSize.
pass by reference: workingSetArraySize[]. workingSetArraySize[] is an array to store the size of the current working set;
pass by reference: pageFaultStatus[]. pageFaultStatus[] was initialized to 0 in the main, initialized to there is no page fault. 

Post-condition: 
workingSetArray[] is documented to store the current working set for one specific window size at the current time i;
workingSetArraySize[] was modified to store the current working set size for one specific window size at the current time i;
pageFaultStatus[] was modifieid to store the pageFault status for one specific window size at the current time i. 0 meaning no page fault; 1 meaning has page fault;

Return value: void
*/ 
void generateStatistics(string referenceStringFn, int windowSizeFn, int workingSetArray[], int workingSetSizeFn, int workingSetArraySize[], int pageFaultStatus[]) {
	int referenceStringLength = referenceStringFn.length(); // the length of the referenceString;
    for (int i = 1; i < referenceStringLength; i++) {
         // algorithm is different when the current i is less than windowSize or larger than windowSize;
         // the following function is made to check whether there is character in this workingSetArray when (i < windowSize);
         if ( i < windowSizeFn ) {
            // This part of the function checks to see whether the character at referenceStringFn.at(i) exist in the workingSet.
            bool characterExistStatus = false; // initialize the current character doesn't exist in the workingSet;
            // the following function is to check whetherh the following character from the referenceString equal to any of the character in my workingSet;
            for ( int j = 0; j < windowSizeFn; j++ ) {
               if ( workingSetArray[j] == referenceStringFn.at(i) ) {
                  characterExistStatus = true; // modify character exist status. 'true' meaning this character exist in the working set.
                  break;
               }//if
            }
            //this part of the function puts the character which doesn't exist in the workingSet into the workingSetArray;
            if (characterExistStatus == false) {
               for (int j = 0; j < windowSizeFn; j++ ) {
                  if (workingSetArray[j] == '*') {
                     workingSetArray[j] = referenceStringFn.at(i);
                     break;
                  }
               }
               workingSetSizeFn++; // update workingSetArraySize;
               workingSetArraySize[i] = workingSetSizeFn; // store the workingSetArraySize in the array;
               pageFaultStatus[i]++; //update pageFault at i;
            }//if
            else { // characterExistStatus == true;
               //don't update workingSetArray;
               workingSetArraySize[i] = workingSetSizeFn; //workingSetArraySize at i equal the previous workingSetSize;
            }
         }// if < windowSize
         // the following part of the algorithm analysis the solution for workingSetArray size (and all those statistics) when (i > windowSize)
         else { // (i > windowSize)
            string subStr = referenceStringFn.substr( i - windowSizeFn+1, windowSizeFn ); //getting the subString based on the windowSize;
            if (referenceStringFn.at(i) == referenceStringFn.at(i - windowSizeFn) ) { // if the new character equal to the character at (i-windowSize), meaning there is no pageFault;
               // don't update workingSetArray;
               workingSetArraySize[i] = workingSetArraySize[i-1]; // use the old workingSetArraySize;
               // no pageFault, so don't update pageFault;
            }//if
            else { // if the new character doesn't equal to the character at (i-windowSize); (there are still two options to see whether there exist page fault or not)
               // reset my workignSetArray to all '*'
               for (int i = 0; i < windowSizeFn; i++ ) {
                  workingSetArray[i] = '*';
               }
               workingSetArray[0] = subStr.at(0); // put the first character from substring to my workingSet;
               int countUniqueElementsInWorkingSetArray = 1; // initialize unique elements in workingSetArray to 1 because at least one character from the substring is unique;
               // the following part of the function put the subString into the array with all unique elements;
               for ( int i = 1; i < windowSizeFn; i++ ) {
                  int curChar = subStr.at(i);
                  bool check = true; // initialize substring characters are all unique;
                  for ( int j = 0; j < i; j++ ) {
                     if (curChar == workingSetArray[j] ) {
                        check = false; // found same character; 
                        // don't do anything to my workingSetArray[i];
                     }
                  }
                     if ( check == true ) { // if the reading in character from subString is unique, then store this character in my workingSetArray;
                        workingSetArray[i] = curChar;
                        countUniqueElementsInWorkingSetArray++; //update number of unique elements in the workingSetArray;
                     }//if
               }//for

               /*
               The following part of the function is just to check whether my subStr[windowSize] matches with any previous element in my subStr;
               if ( matches ) {
                  do not increment y pageFaultStatus
               }
               else { //doesn't match
                  increment my pageFault Status
               }
               */
               int lastCharInSubStr = subStr.at(windowSizeFn -1);
               // check whether my last character in my subString matches with my current substring;
               // if (it matches) {I don't increment pageFault};
               // else {I increment pageFault};
               bool checkLastChar = false; // check whether last character under my substring matches with any characters under subString;
               // false means the last character doesn't exist under my subString;
               for (int j = 0; j < windowSizeFn - 1; j++ ) {
                  if (lastCharInSubStr == subStr.at(j)) {
                     checkLastChar = true;
                  }
               }
               if (checkLastChar == false) {// last character under my subString doesn't match with any character under my subString;
                  //incretment pageFault;
                  pageFaultStatus[i]++; //update my pageFault status in my array;
               }
               // else {
                  //don't do anything with my pageFaultStatus;

               // }
               workingSetArraySize[i] = countUniqueElementsInWorkingSetArray; //update number of character in my workingSetArray at i;
            }//else: if new character that I'm reading in doesn't equal to the character at (i - windowSize)
         }//else: i > windowSize
      }//for

}//void

/*
Function purpose: print the total number of page faults, average working set size, average page fault rate based on one window size;

Pre-condition: pageFaultStatus, workingSetArraySize, windowSize are modified from the previous generateStatistics function
pass by value: referenceStringFn is the referenceString passed from my main;
pass by reference: pageFaultStatus[] documented the pageFaultStatus from i to referenceString whether there are any page fault based on one window size;
pass by reference: workingSetArraySize[] documented the workingSetArray size from i to referenceString based on one window size;
pass by value: the current windowSize from the main is passed to windowSizeFn;

Post-condition: generates necessary statistics;

Return value: void
*/ 


void printStatistics(string referenceStringFn, int pageFaultStatus[], int workingSetArraySize[], int windowSizeFn) {
   int totalPageFault = 0; //initialize pageFault counter to 0;
   int referenceStringLength = referenceStringFn.length();
   for ( int i = 0; i < referenceStringLength; i++ ) {
         if (pageFaultStatus[i] == 1) { // 1 meaning there is a pageFault;
            totalPageFault++; // increment pageFault counter;
         }
   }
   int workingSetSizeCounter = 0; // initialize workingSet Size counter to 0;
   for (int i = 0; i < referenceStringLength; i++ ) {
         workingSetSizeCounter = workingSetSizeCounter + workingSetArraySize[i]; // increment the workingSet size from reading the workingSetSize array;
   }
   //the following part generates necessary statistics;
   float averageWorkingSetSize = (float) workingSetSizeCounter / (float) referenceStringLength;
   float averagePageFaultRate = (float) totalPageFault / (float) referenceStringLength;
   float oneOverAveragePageFaultRate = (float) 1 / averagePageFaultRate; 
   // cout << setw(3) << windowSizeFn << setw(7) << totalPageFault << setw(12) << setprecision(3) << fixed << averageWorkingSetSize  << setw(14) << setprecision(3) << fixed << averagePageFaultRate << setw(14) << setprecision(3) << fixed << oneOverAveragePageFaultRate << endl; 
   // cout << setw(3) << windowSizeFn << setw(7) << totalPageFault << setw(12) << setprecision(3) << fixed << averageWorkingSetSize  << setw(14) << setprecision(3) << fixed << averagePageFaultRate << setw(14) << setprecision(3) << fixed << oneOverAveragePageFaultRate << endl; 
   // cout << setw(3) << windowSizeFn << setw(14) << setprecision(3) << fixed << oneOverAveragePageFaultRate << endl; 
   cout << setw(14) << setprecision(3) << fixed << oneOverAveragePageFaultRate << endl; 
}



int main () {
   char omega [MAX];
   int omegalength;

   string referenceString = setupstring (omega, omegalength);
   //debug statement;
   cout << "the length of referenceString is: " << referenceString.length() << endl;
   for (int i = 0; i < referenceString.length(); i++ ) {
      cout << "[" << i << "]: " << referenceString.at(i) << " ";
   }
   cout << endl;


   int referenceStringLength = referenceString.length();
   int referenceStringArray[referenceStringLength]; // array to store reference string;
   for ( int i = 0; i < referenceStringLength; i++ ) {
      referenceStringArray[i] = referenceString.at(i); 
   }
   cout << "*****************************************************" << endl;
   cout << setw(3) << "W" << setw(7) << "P(W)" << setw(12) << "W(W)" << setw(14) << "F(W)" << setw(14) << "1/F(W)" << endl;

   for ( int windowSize = 1; windowSize < 201; windowSize++ ) {
      int workingSetSize = 0;
      int workingSetArray[windowSize];
      for (int i = 0; i < windowSize; i++ ) {
         workingSetArray[i] = '*'; // initialize workingSetArray to all '*' everytime in the for loop;
      }
      workingSetArray[0] = referenceString.at(0);
      int workingSetArraySize[referenceStringLength];
      int pageFaultStatus[referenceStringLength];

      for ( int i = 0; i < referenceStringLength; i++ ) {
      	pageFaultStatus[i] = 0; // initialize pageFaultStatus to 0 everytime in the for loop;
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
   	  

   }//end up for loop for various windowSize
   cout << "*****************************************************" << endl;


} //main




