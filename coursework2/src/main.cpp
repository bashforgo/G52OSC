#include <sys/wait.h> //waitpid
#include <sys/time.h> //timeval
#include <sys/mman.h> //mman shared memory
#include <sys/types.h> //pid_t
#include <sys/resource.h> // setpriority
#include <stdio.h> //printf
#include <sched.h> // setaffinity
#include <string.h> //strcpy
#include <stdlib.h>
#include <unistd.h>

#define NUMBER_OF_PROCESSES 15
#define MAX_EXPERIMENT_DURATION 1500
#define SVG_HEIGHT 30


long int getDifferenceInMilliSeconds(struct timeval start, struct timeval end);


int main() {
	//initialise time structs
	struct timeval startTime, currentTime;
	gettimeofday(&startTime, NULL);
	srand(startTime.tv_sec);

	//share memory for storing "run-times"
	int* runTimes = (int*)mmap(NULL,
		sizeof(int) * NUMBER_OF_PROCESSES * MAX_EXPERIMENT_DURATION,
		PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED, -1, 0);

	int numCores = sysconf(_SC_NPROCESSORS_ONLN);
	int coreToUse = rand() % numCores;
	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	CPU_SET(coreToUse, &cpuset);
	sched_setaffinity(getpid(), sizeof(cpu_set_t), &cpuset);
	//children will inherit this


	pid_t pid;
	for (int i = 0; i < NUMBER_OF_PROCESSES+1; ++i) //create one more process for ps
	{
		pid = fork();
		if(pid < 0) {
			printf("Could not create process\n");
		}
		else if(pid == 0 && i == NUMBER_OF_PROCESSES)
		{
			// system("ps -l -H > PROCESSLIST1.TXT");
			return 0;
		}
		else if(pid == 0)
		{
			//// child process "function"
			setpriority(PRIO_PROCESS, getpid(), i);
			int diff;
			do
			{
				gettimeofday(&currentTime,NULL);
				//get time since start
				diff = getDifferenceInMilliSeconds(startTime, currentTime);
				
				//log the time into shared memory
				runTimes[diff * NUMBER_OF_PROCESSES + i] = i+1;
			} while (diff < MAX_EXPERIMENT_DURATION);
			return 0;
			//// child process ends here
		}
	}



	int status;
	while (-1 != (pid = waitpid(-1, &status, WUNTRACED)))
	{
		// printf("waiting %d\n", pid);
		// wait until all children die
	}




	printf("<!DOCTYPE html>\n<html>\n<body>\n\n<svg width=\"%d\" height=\"%d\">\n",
		MAX_EXPERIMENT_DURATION, NUMBER_OF_PROCESSES*SVG_HEIGHT);
	for (int i = 0; i < MAX_EXPERIMENT_DURATION; ++i)
	{
		for (int j = 0; j < NUMBER_OF_PROCESSES; ++j)
		{
			// print "run-time" results

			//////////////////////////////////////////////////////////////////////////
			//csv format

			// if (runTimes[i * NUMBER_OF_PROCESSES + j]) // if not 0
			// {
			// 	printf("%d, %d\n", i, runTimes[i * NUMBER_OF_PROCESSES + j]);
			// }
			//////////////////////////////////////////////////////////////////////////
			
			
			
			//////////////////////////////////////////////////////////////////////////
			//svg format
			char color[6];
			switch(runTimes[i * NUMBER_OF_PROCESSES + j] % 4) //4 colors in a round-robin fashion
			{
				case 0:
					strcpy(color, "228dff");
					break;
				case 1:
					strcpy(color, "fa023c");
					break;
				case 2:
					strcpy(color, "0dd5fc");
					break;
				case 3:
					strcpy(color, "ff0099");
					break;
			}
			int procNum;
			if (procNum = runTimes[i * NUMBER_OF_PROCESSES + j]) //if not 0
			{
				printf(
					"  <rect x=\"%d\" y=\"%d\" width=\"1\" height=\"%d\" style=\"fill:#%s\" />\n",
					i, (procNum-1)*SVG_HEIGHT, SVG_HEIGHT, color);
			}
			//////////////////////////////////////////////////////////////////////////

		}
	}
	printf("  Sorry, your browser does not support inline SVG.\n</svg>\n\n</body>\n</html>\n");

	//end of parent
	return 0;
}


long int getDifferenceInMilliSeconds(struct timeval start, struct timeval end)
{
	int seconds = end.tv_sec - start.tv_sec;
	int useconds = end.tv_usec - start.tv_usec;
	int mtime = (seconds * 1000 + useconds / 1000.0);
	return mtime;
}