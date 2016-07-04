#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <set>

using namespace std;

const int MAX = 2000;
const int N   = 10;

class simulation {
public:
    char omega[MAX];
    set <char> wSet;
    float omegaLen;
    int wSize;
    float totalPageFaults, totalWorkingSetSizes; //totals for stats

    simulation(int windowSize) {
        wSize = windowSize;
        totalPageFaults = totalWorkingSetSizes = 0;
        setupString();
    }

    void runSimulation() {
        int curr;

        //work up till full window size is possible
        for (curr = 0; curr < wSize-1; curr++) {
            readNext(0, curr+1);
        }
        //complete the rest with full window size
        for (curr = 0; curr < omegaLen-wSize+1; curr++) {
            readNext(curr, curr+wSize);
        }

        generateStatistics();
    }

    void readNext(int start, int end) {
        char head = omega[end-1]; //current page reference
        totalPageFaults += !(wSet.count(head)); //add 1 to total page faults if there is NOT a match

        wSet.clear(); //erase old set and put in new window's worth
        for (int next = start; next < end; next++) {
            wSet.insert(omega[next]);
        }

        totalWorkingSetSizes += wSet.size(); //add current window size to total tally
    }

    void generateStatistics() {
        cout << "Total page faults: " << totalPageFaults << endl;
        cout << "Average working set size: " << (totalWorkingSetSizes / omegaLen) << endl;
        cout << "Average page fault rate: " << (totalPageFaults / omegaLen) << endl;
    }

    void setupString() {
        int i, j;
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

        omegaLen = strlen (omega);
    }
};

int main()
{
    int windowSize = 200;

    simulation sim(windowSize);
    sim.runSimulation();

    return 0;
};