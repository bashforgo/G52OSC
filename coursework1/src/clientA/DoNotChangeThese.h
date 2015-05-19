// IMPORTANT: DO NOT CHANGE THESE FUNCTIONS SINCE WE WILL REPLACE THEM TO TEST YOUR CODE

#ifndef DONOTCHANGETHESE_H
#define DONOTCHANGETHESE_H

// Include windows.h in case this header gets included into a file which doesn't,
// since it needs some API functions
#include <Windows.h>



// Simulate some time spent processing
// Time taken will depend upon the parameter used
void SimulateProcessingTime( int iDelay )
{
	ULONG64 ul64CycleTimeEnd; // Gets NOW and adds on delay to calculate end time
	QueryThreadCycleTime( GetCurrentThread(),&ul64CycleTimeEnd );
	ul64CycleTimeEnd += iDelay * 1000000;
// Note: to speed up processing, reduce the 1000000 above, or to slow it down increase the value
// We will modify this value in testing so feel free to do so yourself.

	ULONG64 ul64CycleTimeNow;
	do
	{
		QueryThreadCycleTime( GetCurrentThread(),&ul64CycleTimeNow );
	} while ( ul64CycleTimeNow < ul64CycleTimeEnd );
}

// Must be called at the start of each resource usage function so that
// we can test your implementation
void StartingFunction( int iFunctionID )
{
	// Our version adds code here to check your answer
}

// Must be called at the start of each resource usage function so that
// we can test your implementation
void EndingFunction( int iFunctionID )
{
	// Our version adds code here to check your answer
}

// Simulate using a resource
void UseResource( int iResourceID )
{
	// Our version adds code here to check your answer
	SimulateProcessingTime( 100 );
}

// Simulate using two resources simultaneously
void UseTwoResources( int iResourceID1,int iResourceID2 )
{
	// Our version adds code here to check your answer
	SimulateProcessingTime( 100 );
}

// This simulates the fact that you are starting to use a specific resource
// and you must not get any interference on that resource
int StartToUseResource( int iResourceID )
{
	// Our version adds code here to check your answer
	SimulateProcessingTime( 50 );
	return 0; // Our version returns a different number
}

// This simulates the fact that you stop using the resource so
// you do not care what another thread/process does with it now
void FinishUsingResource( int iResourceID, int iTemp )
{
	SimulateProcessingTime( 50 );
	// Our version adds code here to check your answer
}

#endif
