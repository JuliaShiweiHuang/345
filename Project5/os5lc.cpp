/*
Project 5
12/10/2015 -
Lithia Helmreich
Purpose of this program: This simulation simulates how the working set is used to determine which pages should be loaded into and out of memory given a specific reference string.
Input: There are two constants which can be changed, an int N which determines how many times the loops of the reference string 272722(28272272927222)^(n)272722(272733733(373338393373737333)^(n−i+1)3637322)^(n) should be repeated, where N = n, and max, which should be used in conjunction with the chosen N to make sure the char array holding the string will be large enough.
Output: The program creates a simulation based on a window size (here we generate simulations for every integer window size 1-200) and returns a table of statistics about the window size's performance on the reference string.
 */

#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <set>

using namespace std;

const int MAX = 2000; //constant determining size of char array holding reference string (in simulation class)
const int N   = 10; //number of times to repeat loops in generating reference string (in setupString method)

class simulation {
private:
    char omega[MAX]; //char array to hold reference string
    set <char> wSet; //set holding the current working set
    float omegaLen; //length of the reference string
    int wSize; //size of the window to use
    float totalPageFaults, totalWorkingSetSizes; //totals for stats

public:
    simulation(int windowSize) {
        /*pre: input- size of rolling window to use
        post: initializes simulation class with default values and reference string*/

        wSize = windowSize;
        totalPageFaults = totalWorkingSetSizes = 0;
        setupString();
    }

    void runSimulation(void);

    void readNext(int start, int end);

    void generateStatistics();

    void setupString();
};


void simulation::runSimulation() {
    /*pre: asume setupString() has been called and reference string produced
    post: calls readNext on each window in reference string to create working set
    and calls generate stats at end to print stats to console*/

    int curr; //current index of omega[]/reference string

    //work up till full window size is possible
    for (curr = 0; curr < wSize-1; curr++) {
        readNext(0, curr+1);
    }
    //complete the rest with full window size
    for (curr = 0; curr < omegaLen-wSize+1; curr++) {
        readNext(curr, curr+wSize);
    }

    generateStatistics(); //generate and print the stats for this simulation
}

void simulation::readNext(int start, int end) {
    /*pre: input- start and end of window to generate the working set for, using wSet to look at last working set generated
    post: tallys if there was a page fault for the new working set, erases old wSet and generates next one, adds new working set's size to total */

    char head = omega[end-1]; //current page reference
    totalPageFaults += !(wSet.count(head)); //add 1 to total page faults if there is NOT a match

    wSet.clear(); //erase old set and put in new window's worth
    for (int next = start; next < end; next++) {
        wSet.insert(omega[next]); //insert each character in window to set (duplicates will not be added)
    }

    totalWorkingSetSizes += wSet.size(); //add current window size to total tally
}

void simulation::generateStatistics() {
    /*pre: assuming simulation has finished running and final total tallys have been calculated
    post: prints line of table for current window size*/
    cout << setw(3) << wSize << setw(7) << totalPageFaults << setw(12) << (totalWorkingSetSizes / omegaLen) << setw(14) << (totalPageFaults / omegaLen) << endl; //print out stats for this simulation's line of the table
}

void simulation::setupString() {
    /*pre: assuming N constant preassigned
    post: creates reference string for simulation to use*/
    int i, j; //incrementers

    //concatinate each part of reference string into omega
    strcpy(omega, "272722");
    for (i = 0; i < N; i++)
      strcat(omega, "28272272927222");

    strcat(omega, "272722");

    for(i = 0; i < N; i++) {
      strcat (omega, "272733733");

      for(j = i; j < N; j++)
         strcat (omega, "373338393373737333");
      strcat (omega, "3637322");
    }

    omegaLen = strlen (omega); //set length of omega
}

int main()
{
    simulation * simP; //generate pointer to new simulations

    cout << setw(3) << "w" << setw(7) << "P(w)" << setw(12) << "W(w)" << setw(14) << "F(w)" << endl;
    cout << "--------------------------------------" << endl; //print out header to table

    //create new simulation and run it to generate each line of stats for table
    for (int i=1; i<=200; i++) {
        simP = new simulation(i);
        simP->runSimulation();
    }

    return 0;
};