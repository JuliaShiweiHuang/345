
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <queue>
#include <cstdlib>
#include <string>
#include <iomanip>

using namespace std;

const unsigned long int memorySize = 1048576; //size of memory for simulation

class process {
public:
    bool allocate; //true/false indicates process should be allocated/deallocated memory
    int processID; //process's ID
    unsigned long int size; //size of process
    unsigned long int startAddress; //starting address once placed into memory
    unsigned long int endAddress; //ending address once placed into memory

    process(bool a, int id, unsigned long int s) {
        //initialize values
        allocate = a;
        processID = id;
        size = s;
        startAddress = endAddress = 0;
    }
};

class simulation {
public:
    process * p; //pointer to current process we're working on
    process * f; //pointer to free space we're assigning process p to
    int i; //incrementer
    unsigned long int usedMemory, freeMemory, freeMemoryBlocks, avgFreeMemorySize; //variables for statistics
    vector <process *> ram; //vector holding processes in main memory
    queue <process *> input; //queue holding processes that need to be handled from input
    vector <process *> skipped; //vector holding processes that were skipped over
    bool pSkipped; //boolean indicated whether process was skipped or not (used in deallocation)

    simulation(string filename) {
        readInput(filename); //read in processes
        p = new process(0, -1, memorySize); //initialize ram with free space the size of total memory
        p->startAddress = 0;
        p->endAddress = memorySize-1;
        ram.push_back(p);

        usedMemory = freeMemory = freeMemoryBlocks = avgFreeMemorySize = 0; //initialize values to 0
    }

    void readInput(string filename) {
        size_t space1, space2; //spaces in line of input file
        bool allocate; //true if current process is to be allocated, false if deallocated
        int id; //ID of current process
        unsigned long int size; //size of current process
        process * p; //pointer to current process
        string line; //read in lines from input

        //open file to read
        ifstream FIN;
        FIN.open(filename.c_str());

        //exit if unable to read file
        if (!(FIN.is_open())) {
            cout << "Error reading file." << endl;
            FIN.close();
            exit(EXIT_FAILURE);
        }

        getline(FIN, line);
        while (line != "Q") { //until end of file
            space1 = line.find(" "); //find first space

            if (line.find("A") != std::string::npos) { //if "A" we're allocating
                allocate = 1;

                space2 = line.find(" ", space1+1); //find second space to differentiate ID and size
                id = atoi((line.substr(space1, space2)).c_str());
                size = atoi((line.substr(space2, line.size())).c_str());
            }
            else {
                allocate = 0; //else it's "D" we're deallocating, so no size variable
                size = 0;
                id = atoi((line.substr(space1, line.size())).c_str());
            }

            p = new process(allocate, id, size); //create new process with values
            input.push(p); //push to input queue

            getline(FIN, line);
        }

        FIN.close();
    }

    void printResults() {
        for (int i=0; i<ram.size(); i++) {
            if (ram[i]->processID != -1) {
                usedMemory += ram[i]->size; //sum up memory currently being used in ram
            }
            else {
                freeMemoryBlocks += 1; //sum up free memory blocks in ram
            }
        }
        freeMemory = memorySize - usedMemory; //calculate free memory remaining
        if (freeMemoryBlocks != 0) { //calculate average amount of free memory in a block
            avgFreeMemorySize = freeMemory / freeMemoryBlocks;
        }
        else {
            freeMemoryBlocks = 0;
        }

        //print out aligned table of statistics results
        cout << setw(24) << "MEMORY TABLE" << endl;
        cout << "------------------------------------" << endl;
        cout << setw(4) << "PID" << setw(10) << "Start" << setw(10) <<"End" << setw(10) << "Size" << endl;
        cout << "------------------------------------" << endl;
        for (int i=0; i<ram.size(); i++) {
            cout << setw(4) << ram[i]->processID << setw(10) << ram[i]->startAddress << setw(10) << ram[i]->endAddress << setw(10) << ram[i]->size << endl;
        }
        cout << "------------------------------------" << endl;
        cout << "Processes that did not fit in memory: " << endl;
        for (int i=0; i<skipped.size();i++) {
            cout << "PID: " << skipped[i]->processID << endl;
        }
        cout << "------------------------------------" << endl;
        cout << "Memory in use: " << usedMemory << " bytes" << endl;
        cout << "------------------------------------" << endl;
        cout << "Free memory remaining: " << freeMemory << " bytes" << endl;
        cout << "------------------------------------" << endl;
        cout << "Remaining free memory blocks: " << freeMemoryBlocks << endl;
        cout << "------------------------------------" << endl;
        cout << "Avg. size of free blocks: " << avgFreeMemorySize << " bytes" << endl << endl;
    }

    void runSimulation() {
        while (input.size() > 0) {
            p = input.front(); //get p from front of input queue
            if (p->allocate) {
                allocateMemory();
            }
            else {
                deallocateMemory();
            }
        }
    }

    void allocateMemory() {
        i = 0; //incrememter to find first available free space in ram
        bool foundFree = 0; //true indicates a free space has been found in ram
        bool noSpace = 0; //true indicates no free blocks available in ram

        while (!foundFree && !noSpace) { //find first free space of big enough size
            if (i < ram.size()) { //don't increment past end of ram
                if (ram[i]->processID != -1) { //skip if block is not free space
                    i++;
                }
                else { //block is a free space
                    if (ram[i]->size < p->size) { //skip if block size is too small
                        i++;
                    }
                    else {
                        foundFree = 1; //stop when we've found a good free spot
                    }
                }
            }
            else {
                noSpace = 1; //no good free space has been found
            }
        }

        if (noSpace) { //if no free space available, push to skipped vector
            skipped.push_back(p);
            input.pop();
        }
        else {
            f = ram[i]; //f = first free block in ram which we found will fit process

            if (f->size > p->size) { //if f has more space than p need's
                p->startAddress = f->startAddress; //p start address = f start address
                p->endAddress = (p->startAddress + p->size - 1); //p end address + size of p
                f->startAddress = (p->endAddress + 1); //free start is p end + 1
                f->size = (f->size - p->size); //free size is now old size - size of P

                ram.insert(ram.begin()+i, p); //insert into ram in front of f free space

                input.pop();
            }
            else { //f size == p size, replace f's -1 id with p's
                f->processID = p->processID;
                input.pop();
            }
        }
    }

    void deallocateMemory() {
        pSkipped = 0; //boolean determines whether we've skipped the process p or not
        for (int i=0; i<skipped.size(); i++) { //look for p in skipped vector
            if (skipped[i]->processID == p->processID) {
                pSkipped = 1;
            }
        }

        if (!pSkipped) {
            i = 0; //incrementer to find p in ram
            while ((i < ram.size()) && (ram[i]->processID != p->processID)) { //while i isn't past ram size and block isn't p
                i++;
            }

            ram[i]->processID = -1; //set process p's id to be -1 (free space now)

            if (i+1 < ram.size()) { //if block after old p in ram is free, join them
                if (ram[i+1]->processID == -1) {
                    ram[i]->size = ram[i]->size + ram[i+1]->size; //old p size = old p size + free block size
                    ram[i]->endAddress = ram[i+1]->endAddress; //old p end address = i+1 free block's end address
                    ram.erase(ram.begin()+i+1); //delete ram[i+1] so we now have 1 free block
                }
            }
            if (i-1 >= 0) { //if block before old p in ram is free, join them (same process as above but with i-1 and i instead of i and i+1)
                if (ram[i-1]->processID == -1) {
                    ram[i-1]->size = ram[i-1]->size + ram[i]->size;
                    ram[i-1]->endAddress = ram[i]->endAddress;
                    ram.erase(ram.begin()+i); //delete ram[i] == p
                }
            }
        }
        input.pop(); //remove p from input queue
    }
};

int main()
{
    //get in the filename from user
    string filename;
    cout << "Filename: ";
    cin >> filename;
    cout << endl;

    simulation sim = simulation(filename); //create a simulation with given filename
    sim.runSimulation(); //run the simulation
    sim.printResults(); //print the results of the simulation

    return 0;
}