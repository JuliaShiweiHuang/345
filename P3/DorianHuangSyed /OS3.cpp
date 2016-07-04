/* 
Operating Systems: Project 3 "Working the System"
Programers: Meghan Dorian, Shiwei Huang, Muneeba Syed
We have abided by the Wheaton Honor
Code in this work. 
----------------------------------------------------
PURPOSE:Run a simulation software using Round Robin CPU scheduling algorithm.
		The system is designed for one CPU and includes a ready queue, 
		 an IO queue, an IO to run jobs. 
INPUT: 
1.  A user inputted .txt file containing number of jobs (separated by line) 
	   with numbers indicating their start time (ms), PID, 
	   probability of IO request, and job length (ms).
2.  User will also input the simulation time (s), the 
	   quantum size (ms), and the degree of multiprogramming.
3.  Name of output file (without extension)

OUTPUT: 
Output to screen includes 
0. Detailed stats of each job after completed simulation
1. Number of jobs completed during the simulation
2. NUmber of jobs still in system
3. Number of jobs skipped
4. Average job length excluding I/O time
5. Average turnaround time
6. Average wait time per process
7. Percentage of times when CPU is busy
----------------------------------------------------
NOTES: 
1. We are using Discrete time method 
2. For calculating the statistics part, assumptions include: 
#4. Average job length: Average CPU time for all completed jobs
#5. Average turnaround time: Total time spent in system for completed jobs
#6. Average waiting time per process: Endtime - jobLength from File - starttime from file
#7. Percentage of time when CPU is busy: the time when CPU status is FULL / total simulation time
 
----------------------------------------------------
*/ 

//---Libraries--------------------------------
#include <iostream>
#include <fstream>
#include <stdio.h> //printf
#include <math.h> //fmod
#include "OSjobs.h" //Job class
#include <string>
#include <queue>
#include <stdlib.h>
#include <iomanip>

using namespace std; 

//---Function Prototypes-----------------------------
int readFile(string infileName); 
void output2file(Job * jobArray, int size);
void outputStatus(Job *statusArray, int size, int simTime);
void simulation(Job * DoneArray, int simTime, int quantum ,int multiprog); 
//---Globals-----------------------------------------
//this float will help us to calculate the percentage of time the CPU is busy
float cpuCounterWhenUtilized = 0; 
//constants
//these are used to initialize the CPU
const int IDLETIME = 4; 
const int FULL = -1;
const int EMPTY = 0;
//boolean flag
bool IOProb_From_File = true;
//Create Queues of Jobs 
queue<Job> IncomingJobQ; 
queue<Job> ReadyQueue; 
queue<Job> IOQueue;

//===============================================
int main ()
{
	srand((unsigned)time(NULL)); //seed generator

	//user input variables
	int simtime, //total simulation time (seconds)
	    quantumsize, // in milliseconds
	    degree; // number of jobs allowed in system at once
	string filename; //name of input file
	
	int totalNumJobs; //num jobs in file


	//Fetching user input
	cout << "Enter input file: ";
	cin >> filename; 
	cout << "Enter total simulation time (s): "; 
	cin >> simtime; 
	simtime = simtime *1000; //convert to milliseconds
	cout << "Enter quantum size (integer ms): ";
	cin >> quantumsize; 
	cout << "Enter degree of multiprogramming: "; 
	cin >> degree; 
	
	//get the total number of jobs from the first line in the file
	totalNumJobs = readFile(filename); 

	//initialize empty done array
	Job * DoneJobArray = new Job[totalNumJobs];
	//run simulation
	simulation(DoneJobArray, simtime, quantumsize, degree);
	//make output to file
	output2file(DoneJobArray, totalNumJobs);

	//output to screen the necessary statistics 
	outputStatus(DoneJobArray, totalNumJobs, simtime);
	

	cout << "DONE!" << endl;
	return 0; 
}//end main()
//==================================================

int readFile(string infileName)
{
	/* 
	 * This function takes a user-input string as its parameter. 
	 * It opens and reads (or exits if file is not found) the .txt file,
	 * and puts all jobs into the incomingJobQ (not part of the system). 
	 * This function returns the total number of jobs (first line in the file)
	 * as an int to be used in other functions.  
	 * 
	 */
	
	//values from file
	int numEntries;
	int fStartTime, fPID, fIOprob, fJobLen; 

	ifstream FIN; 
	FIN.open(infileName.c_str()); //open file
	//check for success/failure
	if (FIN.fail())
	{
		cout << infileName << " not found." << endl;
		exit(-1); 
	}
	else 
	{
		FIN >> numEntries; 
		for (int i = 0; i < numEntries; i++)
		{
			//read in the parameters for each job 
			FIN >> fStartTime >> fPID >> fIOprob >> fJobLen;  
			
			//check for which Job CTOR to use
			if(IOProb_From_File)
			{
				Job newJob(fStartTime, fPID, fIOprob, fJobLen); //create a new instance of Job
				IncomingJobQ.push(newJob); //push to incoming job queue
			}
			else //disregard IO from file and use CTOR which generates it
			{
				Job newJob(fStartTime, fPID, fJobLen); //create a new instance of Job
				IncomingJobQ.push(newJob); //push to incoming job queue
			} 
			
		}//end for each entry in file
		FIN.close();  
	}//end else got file
	return numEntries; 

} // end readFile()
//==================================================



void simulation(Job * DoneArray, int simTime, int quantum ,int multiprog)
{
	/* This function takes as its input pointer to an array, and the
	 * variables of simulation time (ms), quantum (ms), and degree of 
	 * multiprogramming. 
	 * This function runs the actual simulation itself. 
	 * It first checks if any jobs need to be skipped, or if it is time 
	 * to add any jobs from the incomingJobQ to the system.
	 * Any jobs with a condition of skipped or completed are sent to the 
	 * DoneArray, which is later used to produce statistics. 
	 * Since this uses discrete time method, it checks every ms the state
	 * of the CPU and IO, and the status of the jobs in there (if any). 
	 * When the simulation is over, it checks the status of the jobs 
	 * currently in the system and then prints the final statistics to
	 * the screen. 
	 */
	 
	 
	//initialize CPU and IO representations
	Job CPUJob, IOJob; 
	//initialize the states of the CPU and IO 
	int CPUstate = EMPTY;
	int IOstate = EMPTY;  
	int jobsinsystem = 0; // initialize numjobs currently in system

	int done_i = 0; // starting index for DoneArray

	int dice; //for rolling IOevent each millisecond

	//---BEGIN SIMULATION!!!----------------
	for (int currentTime = 1; currentTime <= simTime; currentTime ++ )
	{
		//cleaning IncomingJobQ of skipped jobs
		while ( (!IncomingJobQ.empty()) && (IncomingJobQ.front().getStartTime() < currentTime) )
		{
			IncomingJobQ.front().status = SKIP; //change status 
			DoneArray[done_i] = (IncomingJobQ.front()); //store in array 
			done_i++; //move the counter 
			IncomingJobQ.pop(); //remove from queue
		}//end while IncomingQ is not empty and front's start time < current time 

		//Check if new jobs can enter system 
		while ((jobsinsystem < multiprog) && (IncomingJobQ.front().getStartTime() == currentTime))
		{ 
			IncomingJobQ.front().status = CPUREADY; //change status
			ReadyQueue.push(IncomingJobQ.front()); //push job to ready queue
			IncomingJobQ.pop(); //remove from incoming queue
			jobsinsystem++; //increment jobs in system
		}
		

		//---checking the CPU state-----
		if (CPUstate == EMPTY) //add job to CPU...
		{
			if (!ReadyQueue.empty())//...if there's a job ready for it 
			{
				ReadyQueue.front().status = CPUREADY; //change status 
				CPUJob = ReadyQueue.front(); //move job to CPU
				CPUJob.setQuantum(quantum); //give it a quantum
				ReadyQueue.pop(); //remove from ready queue
				CPUstate = FULL; // change CPU state

			}
			
		}//end if CPU is empty

		//new "if" because want to work on new job as soon as it enters CPU 
		if (CPUstate == FULL) // working on job in CPU
		{
			cpuCounterWhenUtilized++; //increment the CPU counter
			//-----generate dice 1-100-----
			dice = (rand() % 100) + 1;

			if(dice <= CPUJob.getIOprob()) // if less than job's prob, go to IOQueue
			{
				CPUJob.status = IOREADY; //change status
				CPUJob.IOstampIn = currentTime; //mark when enters IO 
				IOQueue.push(CPUJob); // push to IO queue
				CPUstate = IDLETIME; //start swap-job time
			}//end if going to IO queue  

			else // no IO, stays in CPU
			{
				//work on the job for one ms
				CPUJob.timeInCPU++; 
				CPUJob.quantumLeft--;
				
				//check if job finished
				if (CPUJob.timeInCPU == CPUJob.getJobLen()) 
				{
					CPUJob.status = DONE; //change status 
					CPUJob.whenLeftSystem = currentTime; //mark when left system 
					DoneArray[done_i] = CPUJob; //add to done array 
					done_i++;
					jobsinsystem --; //job is no longer in the system
					CPUstate = IDLETIME; //start swap-job time

				}//end if job finished

				//check if quantum ran out
				else if (CPUJob.quantumLeft == 0) 
				{

					//check if this job can have another quantum
					if(!ReadyQueue.empty()) //has to leave
					{
						CPUJob.status = CPUREADY; //change status
						ReadyQueue.push(CPUJob); //push job to end of ready queue  
						CPUstate = IDLETIME; //start swap-job time
						
					}//end if jobs are waiting for CPU
					else // no jobs waiting in Ready queue, so it can have another quantum 
					{
						CPUJob.setQuantum(quantum);
					}//end else job can have another quantum 


				}//end else if quantum ran out

			}//end else no IO 

		} // end if CPU is full
		
		else  //CPU is switching jobs (CPUstate > 0)
		{
			if(CPUstate != EMPTY)
			{
				CPUstate--; //decrement the idling counter 
			}
		}//end else CPU is switching jobs

		//---checking the IO state------
		if (IOstate == EMPTY) //add job to IO
		{
			if (!IOQueue.empty())//...if there's a job waiting for it
			{
				IOQueue.front().status = IO; //change status
				IOJob = IOQueue.front(); //move job to IO
				IOQueue.pop(); //remove from IO queue 
				IOstate = FULL; //change state

			}//end if IO queue not empty

		}//end if IO state is empty 
		
		//new if so can work on new job right away
		if (IOstate == FULL) //work on IO
		{
			IOJob.IOtime--; //work on job

			//check if finished with IO 
			if (IOJob.IOtime == 0)
			{
				IOJob.status = CPUREADY; //change status
				IOJob.IOstampOut = currentTime; //mark when leaves IO
				IOJob.totalIOtime += IOJob.IOstampOut - IOJob.IOstampIn; //calculate and store total time in IO
				IOJob.updateIOstats(); //generate new IO prob and time
				ReadyQueue.push(IOJob); //push to ready queue
				IOstate = EMPTY; //change state
			}//end if finished with IO

		}//end if IO state is full
			


	}//end for each millisecond of simulation

	//---Simulation Over!!!-------------------------

	//clean out system of remaining jobs
	cout << "\n\nEnd of simulation run time\n"; 

	//check CPU
	if (CPUstate == FULL)
	{
		DoneArray[done_i] = CPUJob; 
		done_i++;

	}//end if job still in CPU

	//check IO

	if (IOstate == FULL)
	{
		DoneArray[done_i] = IOJob; 
		done_i++;
	}//end if job still in IO

	//cleaning Ready Queue
	while (!ReadyQueue.empty())
	{
		DoneArray[done_i] = ReadyQueue.front(); 
		done_i++;
		ReadyQueue.pop();
	}//end while jobs in ready queue

	//cleaning IO Queue
	while (!IOQueue.empty())
	{
		DoneArray[done_i] = IOQueue.front(); 
		done_i++;  
		IOQueue.pop(); 
	}//end while jobs in ready queue

	while (!IncomingJobQ.empty())
	{

		DoneArray[done_i] = IncomingJobQ.front(); 
		done_i++;  
		IncomingJobQ.pop();
	} //end while jobs still in incoming queue
	

}//end simulation()
//==================================================
void output2file(Job * jobArray, int size)
{
	/* This function takes the final results of the simulation, and 
	 * outputs it to a csv file for the user to look at. 
	 * It takes as input the array of jobs, and the total number of jobs
	 * It shows each job's ID, job length, status (at the end of the simulation), 
	 * its start time, end time, wait time, and time in IO. 
	 */
	 
	string COMMA = ",";
	string fileExt = ".csv";

	string outFileName;
	ofstream FOUT; 

	cout << "Enter name of output file: " << endl;
	cin >>  outFileName; 
	outFileName = outFileName + fileExt; 

	FOUT.open(outFileName.c_str());

	if (FOUT.fail())
	{
		cout << outFileName << " failed to open." << endl;
	}
	else
	{
		FOUT << "Job ID, Job Length, Status, Start Time, Time Spent in CPU, End Time, Wait Time, IO Time," << endl;
		for (int i = 0; i < size; i++)
			{
				 
				FOUT << jobArray[i].getJobID() << COMMA \
					<< jobArray[i].getJobLen() << COMMA \
					<< jobArray[i].getStatus() << COMMA \
					<< jobArray[i].getStartTime() << COMMA \
					<< jobArray[i].timeInCPU << COMMA \
					<< jobArray[i].whenLeftSystem << COMMA \
					<< jobArray[i].waitTime << COMMA \
					<< jobArray[i].totalIOtime << COMMA << endl;    
			}//end for each job in array
			FOUT.close(); 
	}
}//end output2file()
//=================================================================


void outputStatus(Job * statusArray, int size, int simTime)
{	
	/* This function outputs the statistics to the command line for 
	 * the user to see immediately.
	 * It takes as input an array and the total number of jobs. 
	 * It outputs the number of completed jobs, number of jobs still
	 * in the system, number of skipped jobs, the average job length
	 * time excluding time in IO, average turnaround time, and the average
	 * wait time. 
	 * 
	 * 
	 */
	 
	cout << "************************RESULT***********************" << endl;
	cout << endl;
	cout << "------------------Begin detailed result------------------" << endl;
	cout << endl;
	int countNumberOfJobsCompleted = 0;
	int countNumberOfJobsSkipped = 0;
	int countNumberOfJobsStillInSystem = 0;
	
	// part 1 - 3 calculation
	for ( int i = 0; i < size; i++ ) {
		cout << setw(30) << "JOB #" << statusArray[i].getJobID() << endl;
		cout << "Job length is: " << statusArray[i].getJobLen() << " ms" << endl;
		cout << "Status: " << statusArray[i].getStatus() << endl;
		cout << "Start time (from file): " << statusArray[i].getStartTime() << endl;
		cout << "End time: ";
		if (statusArray[i].whenLeftSystem == 0){
			cout << "Job was not completed" << endl;
		}
		else{
		     cout << statusArray[i].whenLeftSystem << endl;
		}
		cout << endl;

		if ( statusArray[i].getStatus() == "DONE" ) {
			countNumberOfJobsCompleted++;
		}

		if ( statusArray[i].getStatus() == "SKIP" ) {
			countNumberOfJobsSkipped++;
		}

		if ( (statusArray[i].getStatus() != "DONE") && (statusArray[i].getStatus() != "SKIP") ) {
			// cout << "debug: cout status " << statusArray[i].getStatus() << endl;
			countNumberOfJobsStillInSystem++;
		}

	}

	// end part 1-3 calculation

// part 4: calculate average job length excluding I/O time
	float thisJobLength;
	float totalJobLengthSum = 0;
	float averageJobLength;
	for ( int i = 0; i < size; i++ ) {
		if ( statusArray[i].getStatus() == "DONE" ) {
			thisJobLength = statusArray[i].getJobLen();
			totalJobLengthSum = totalJobLengthSum + thisJobLength;
		}
	
	}
	averageJobLength = totalJobLengthSum / countNumberOfJobsCompleted;
// end part 4

// part 5: calculate average turnaround time

	float thisJobTurnAroundTime = 0;
	float totalJobTurnAroundTime = 0;
	float averageJobTurnAroundTime;
	for ( int i = 0; i < size; i++ ) {
		if ( statusArray[i].getStatus() == "DONE" ) {
			thisJobTurnAroundTime = statusArray[i].whenLeftSystem - statusArray[i].getStartTime() + 1;
			totalJobTurnAroundTime = totalJobTurnAroundTime + thisJobTurnAroundTime;
		}

	}
	averageJobTurnAroundTime = totalJobTurnAroundTime / countNumberOfJobsCompleted;

// end part 5: calculate average turnaround time

// part 6: calculate average wait time per process
	float thisJobWaitTime;
	float totalProcessWaitTime = 0;
	float averageWaitTImePerProcess;
	for ( int i = 0; i < size; i++ ) {
		if ( statusArray[i].getStatus() == "DONE" ) {
			thisJobWaitTime = (statusArray[i].whenLeftSystem - statusArray[i].getStartTime()) - statusArray[i].getJobLen()- statusArray[i].totalIOtime;
			totalProcessWaitTime = totalProcessWaitTime + thisJobWaitTime;
		}
	}
	averageWaitTImePerProcess = totalProcessWaitTime / countNumberOfJobsCompleted;

// end part 6

// begin part 7
	float cpuUtilization = (cpuCounterWhenUtilized / simTime) * 100;
	
// end part 7

	cout << "------------------End detailed result------------------" << endl;
	cout << endl;

	cout << "1. Number of jobs completed during the simulation is: " << countNumberOfJobsCompleted << endl;
	cout << "2. Number of jobs still in system is: " << countNumberOfJobsStillInSystem << endl;
	cout << "3. Number of jobs skipped is: " << countNumberOfJobsSkipped << endl;

	cout << "4. Average job length excluding I/O time is: " << averageJobLength << " ms" << endl;
	cout << "5. Average turnaround time is: " << averageJobTurnAroundTime << " ms" << endl;
	cout << "6. Average wait time per process is: "  << averageWaitTImePerProcess << " ms" << endl;
	cout << "7. Percentage of time CPU is busy (CPU utilization) is: " << cpuUtilization << "%" << endl;
	cout << endl;
	cout << "*******************END RESULT***********************" << endl;
	cout << endl;
	
}
