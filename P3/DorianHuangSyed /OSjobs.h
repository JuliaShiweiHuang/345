//OSjobs.h

#include <iostream>
#include <string>

using namespace std;
//Keeps track of job's state in system
enum jobState {QWAITING = 0, CPUREADY = 1, SKIP = 2, CPU = 3, IOREADY = 4, IO = 5, DONE = 6};

class Job
{
private:
	//each job will have these data members, as read from the input file 
	int startTime, jobID, IOprob, jobLength; 

	//generators
	int mainGenerator(int minVal, int range); 
	int generateIOprob();
	int generateIOtime(); 

public: 
	//these variables will change in simulation
	int timeInCPU, quantumLeft; 
	int IOtime, IOstampIn, IOstampOut, totalIOtime;
	int waitTime, whenLeftSystem; 
	jobState status; 

	//CTORS
	Job(); 
	Job(int inStartTime, int inPID, int inIOprob, int inLen ); //CTOR which uses given IOprob
	Job(int inStartTime, int inPID, int inLen); //CTOR which generates random IOprob
	
	// DTOR
	~Job (); 
	
	
	//Setters

	//reset quantum
	void setQuantum(int thisQuantum);
	//refresh IO stats
	void updateIOstats(); 
	//change status (dont need this)
	void updateStatus(jobState newStatus);
	
	//Getters
	void printStatus(); //to comand line
	string getStatus(); //return in string form 

	int getStartTime();
	int getJobID();
	int getIOprob();
	int getJobLen(); 


};
