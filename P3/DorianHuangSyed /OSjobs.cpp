// OSjobs.cpp 


#include <iostream>
#include <string>
#include <stdio.h>  
#include <stdlib.h> 
#include <time.h>
#include "OSjobs.h" //job class

using namespace std; 


//probability const
const int MIN_IO_PROB = 0; 
const int RANGE_IO_PROB = 6; 
const int MIN_IO_TIME = 5; 
const int RANGE_IO_TIME = 21; 

//===CTORS===================
Job::Job()
{}
//-----------------------
Job::Job(int inStartTime, int inPID, int inIOprob, int inLen)
{
	//This constructor uses the given IO probability and assigns variables 
	startTime = inStartTime;
	jobID = inPID;
	jobLength = inLen;
	
	IOprob = inIOprob;
	IOtime = generateIOtime(); 
	
	//initialize variables
	timeInCPU = 0;
	quantumLeft = 0;

	IOstampIn = 0; 
	IOstampOut = 0;
	totalIOtime = 0;

	waitTime = 0;
	whenLeftSystem = 0;

	//all jobs start with the enum of QWAITING, which means waiting for the ReadyQ
	status = QWAITING;
}
//-----------------------
Job::Job(int inStartTime, int inPID, int inLen)
{
	//This constructor takes three parameters, so it generates its own IO probability and time 
	startTime = inStartTime;
	jobID = inPID;
	jobLength = inLen;
	
	IOprob = generateIOprob();
	IOtime = generateIOtime();
	
	timeInCPU = 0;
	quantumLeft = 0;

	IOstampIn = 0; 
	IOstampOut = 0;
	totalIOtime = 0; 

	waitTime = 0;
	whenLeftSystem = 0;
	
	status = QWAITING;

}
Job::~Job()
{}
//=========================================
//===Private generators=========================
int Job::mainGenerator(int minVal, int range)
{
	return (rand() % range)+minVal; 
}
//-----------------------
int Job::generateIOprob()
{
	return mainGenerator(MIN_IO_PROB, RANGE_IO_PROB); 
}
//-----------------------
int Job::generateIOtime()
{
	return mainGenerator(MIN_IO_TIME, RANGE_IO_TIME); 
}
//=========================================
//===Public functions=========================
//---Setters-----------------------------------
void Job::setQuantum(int thisQuantum)
{
	quantumLeft = thisQuantum; 
}
//-----------------------
void Job::updateIOstats()
{
	IOprob = generateIOprob(); 
	IOtime = generateIOtime();
}
//-----------------------
void Job::updateStatus(jobState newStatus)
{
	status = newStatus;
}
//-----------------------
//-----------------------
//-----------------------
//---Getters----------------------------------
void Job::printStatus()
{ 
	switch (status)
	{
	case QWAITING:
		cout << "WAITING FOR Q" << endl; 
		break;

	case CPUREADY: 
		cout << "CPU READY" << endl; 
		break;

	case SKIP:
		cout << "SKIP" << endl; 
		break;

	case CPU:
		cout << "CPU" << endl; 
		break;

	case IOREADY:
		cout << "IO READY" << endl; 
		break; 

	case IO:
		cout << "IO" << endl;
		break;

	case DONE:
		cout << "DONE" << endl; 
		break;
	
	default:
		cout << "Error in status" << endl; 

	}
}
//-----------------------
string Job::getStatus()
{ 
	string returningStr; 
	switch (status)
	{
	case QWAITING:
		returningStr = "WAITING FOR Q"; 
		break;

	case CPUREADY: 
		returningStr = "CPU READY"; 
		break;

	case SKIP:
		returningStr = "SKIP"; 
		break;

	case CPU:
		returningStr = "CPU"; 
		break;

	case IOREADY:
		returningStr = "IO READY"; 
		break; 

	case IO:
		returningStr = "IO";
		break;

	case DONE:
		returningStr = "DONE"; 
		break;
	
	default:
		returningStr = "Error in status"; 

	}
	return returningStr;
}
//-----------------------
int Job::getStartTime()
{
	return startTime;
}
//-----------------------
int Job::getJobID()
{
	return jobID;
}
//-----------------------
int Job::getIOprob()
{
	return IOprob; 
}
//-----------------------
int Job::getJobLen()
{
	return jobLength;
}
//-----------------------
