// This file contains:

// 1: Code for you to copy into your main program file
// 2: Code for you to copy-paste into your windows procedures to avoid having to write drawing code yourself


// You MUST include this header file at the top of your main program file and MUST NOT modify the contents of the header file.
// We will use our own version of this header file for the marking.
#include "DoNotChangeThese.h"
#include <stdio.h>

#define THREAD_COUNT 5
#define RESOURCE_COUNT 6

volatile unsigned int resourceCounters[RESOURCE_COUNT];
CRITICAL_SECTION resourceCrits[RESOURCE_COUNT];


// The following functions should all be in your main program file that you included the header above into
// IMPORTANT: You may ADD to the following functions but you MUST NOT delete anything
// Our tests on your final code will need everything that was there before and will use this to test your code.

void IncrementResourceAndEnterCriticalSection(int);
void EnterResourceCriticalSection(int);
void LeaveResourceCriticalSection(int);

//1
void TestCase1()
{
	StartingFunction(1); // Do not remove - for testing purposes

	IncrementResourceAndEnterCriticalSection(1);
	UseResource(1);	// Do not remove - for testing purposes
	LeaveResourceCriticalSection(1);

	EndingFunction(1); // Do not remove - for testing purposes
}

//2
void TestCase2()
{
	StartingFunction(2); // Do not remove - for testing purposes

	IncrementResourceAndEnterCriticalSection(2);
	UseResource(2);	// Do not remove - for testing purposes
	LeaveResourceCriticalSection(2);

	EndingFunction(2); // Do not remove - for testing purposes
}


//3
void TestCase3()
{
	StartingFunction(3); // Do not remove - for testing purposes

	IncrementResourceAndEnterCriticalSection(3);
	UseResource(3);	// Do not remove - for testing purposes
	LeaveResourceCriticalSection(3);

	EndingFunction(3); // Do not remove - for testing purposes
}

//4
void TestCase4()
{
	StartingFunction(4); // Do not remove - for testing purposes

	IncrementResourceAndEnterCriticalSection(4);
	UseResource(4);	// Do not remove - for testing purposes
	LeaveResourceCriticalSection(4);

	EndingFunction(4); // Do not remove - for testing purposes
}

//5
void TestCase5()
{
	StartingFunction(5); // Do not remove - for testing purposes

	IncrementResourceAndEnterCriticalSection(5);
	UseResource(5);	// Do not remove - for testing purposes
	LeaveResourceCriticalSection(5);

	EndingFunction(5); // Do not remove - for testing purposes
}

//(1,2)
void TestCase6()
{
	StartingFunction(6); // Do not remove - for testing purposes

	IncrementResourceAndEnterCriticalSection(1);
	IncrementResourceAndEnterCriticalSection(2);
	UseTwoResources(1, 2);	// Do not remove - for testing purposes
	LeaveResourceCriticalSection(1);
	LeaveResourceCriticalSection(2);

	EndingFunction(6); // Do not remove - for testing purposes
}

//(2,3)
void TestCase7()
{
	StartingFunction(7); // Do not remove - for testing purposes

	IncrementResourceAndEnterCriticalSection(2);
	IncrementResourceAndEnterCriticalSection(3);
	UseTwoResources(2, 3);	// Do not remove - for testing purposes
	LeaveResourceCriticalSection(2);
	LeaveResourceCriticalSection(3);

	EndingFunction(7); // Do not remove - for testing purposes
}

//3+(5,6)-3
void TestCase8()
{
	StartingFunction(8); // Do not remove - for testing purposes

	// TODO - add extra code to increment your value for resource 3
	IncrementResourceAndEnterCriticalSection(3);
	int iTemp = StartToUseResource(3); // Do not remove - for testing purposes
	// TODO - add extra code to increment your value for resources 5 and 6
	IncrementResourceAndEnterCriticalSection(5);
	IncrementResourceAndEnterCriticalSection(6);
	UseTwoResources(5, 6);  // Do not remove - for testing purposes
	FinishUsingResource(3, iTemp); // Do not remove - for testing purposes
	LeaveResourceCriticalSection(3);
	LeaveResourceCriticalSection(5);
	LeaveResourceCriticalSection(6);

	EndingFunction(8); // Do not remove - for testing purposes
}

//4+(1,2)-4
void TestCase9()
{
	StartingFunction(9); // Do not remove - for testing purposes

	// TODO - add extra code to increment your value for resource 4
	EnterResourceCriticalSection(1);
	EnterResourceCriticalSection(2);
	IncrementResourceAndEnterCriticalSection(4);
	int iTemp = StartToUseResource(4); // Do not remove - for testing purposes
	TestCase6(); // Do not remove - for testing purposes
	FinishUsingResource(4, iTemp); // Do not remove - for testing purposes
	LeaveResourceCriticalSection(1);
	LeaveResourceCriticalSection(2);
	LeaveResourceCriticalSection(4);


	EndingFunction(9); // Do not remove - for testing purposes
}

//1+(2,3)-1
void TestCase10()
{
	StartingFunction(10); // Do not remove - for testing purposes

	// TODO - add extra code to increment your value for resource 1
	IncrementResourceAndEnterCriticalSection(1);
	int iTemp = StartToUseResource(1); // Do not remove - for testing purposes
	EnterResourceCriticalSection(2);
	EnterResourceCriticalSection(3);
	TestCase7(); // Do not remove - for testing purposes
	FinishUsingResource(1, iTemp); // Do not remove - for testing purposes
	LeaveResourceCriticalSection(1);
	LeaveResourceCriticalSection(2);
	LeaveResourceCriticalSection(3);


	EndingFunction(10); // Do not remove - for testing purposes
}

//3+4+(5,6)-3-4
void TestCase11()
{
	StartingFunction(11); // Do not remove - for testing purposes

	// TODO - add extra code to increment your value for resource 3
	IncrementResourceAndEnterCriticalSection(3);
	int iTemp3 = StartToUseResource(3); // Do not remove - for testing purposes
	// TODO - add extra code to increment your value for resource 4
	IncrementResourceAndEnterCriticalSection(4);
	int iTemp4 = StartToUseResource(4); // Do not remove - for testing purposes
	// TODO - add extra code to increment your value for resources 5 and 6
	IncrementResourceAndEnterCriticalSection(5);
	IncrementResourceAndEnterCriticalSection(6);
	UseTwoResources(5, 6);  // Do not remove - for testing purposes
	FinishUsingResource(3, iTemp3); // Do not remove - for testing purposes
	FinishUsingResource(4, iTemp4); // Do not remove - for testing purposes
	LeaveResourceCriticalSection(3);
	LeaveResourceCriticalSection(4);
	LeaveResourceCriticalSection(5);
	LeaveResourceCriticalSection(6);

	EndingFunction(11); // Do not remove - for testing purposes
}

//5+3-5
void TestCase12()
{
	StartingFunction(12); // Do not remove - for testing purposes

	// TODO - add extra code to increment your value for resource 5
	EnterResourceCriticalSection(3);
	IncrementResourceAndEnterCriticalSection(5);
	int iTemp = StartToUseResource(5); // Do not remove - for testing purposes
	TestCase3(); // Do not remove - for testing purposes
	FinishUsingResource(5, iTemp); // Do not remove - for testing purposes
	LeaveResourceCriticalSection(3);
	LeaveResourceCriticalSection(5);

	EndingFunction(12); // Do not remove - for testing purposes
}

//1,(2,3),[3+(5,6)-3]
void TestCase13()
{
	StartingFunction(13); // Do not remove - for testing purposes

	EnterResourceCriticalSection(1);
	TestCase1(); // Do not remove - for testing purposes
	LeaveResourceCriticalSection(1);

	EnterResourceCriticalSection(2);
	EnterResourceCriticalSection(3);
	TestCase7(); // Do not remove - for testing purposes
	LeaveResourceCriticalSection(2);

	EnterResourceCriticalSection(5);
	EnterResourceCriticalSection(6);
	TestCase8(); // Do not remove - for testing purposes
	LeaveResourceCriticalSection(3);
	LeaveResourceCriticalSection(5);
	LeaveResourceCriticalSection(6);

	EndingFunction(13); // Do not remove - for testing purposes
}

//4+5+6-4-5-6
void TestCase14()
{
	StartingFunction(14); // Do not remove - for testing purposes

	// TODO - add extra code to increment your value for resource 4
	IncrementResourceAndEnterCriticalSection(4);
	int iTemp4 = StartToUseResource(4); // Do not remove - for testing purposes
	// TODO - add extra code to increment your value for resource 5
	IncrementResourceAndEnterCriticalSection(5);
	int iTemp5 = StartToUseResource(5); // Do not remove - for testing purposes
	// TODO - add extra code to increment your value for resource 6
	IncrementResourceAndEnterCriticalSection(6);
	int iTemp6 = StartToUseResource(6); // Do not remove - for testing purposes

	FinishUsingResource(4, iTemp4); // Do not remove - for testing purposes
	FinishUsingResource(5, iTemp5); // Do not remove - for testing purposes
	FinishUsingResource(6, iTemp6); // Do not remove - for testing purposes
	LeaveResourceCriticalSection(4);
	LeaveResourceCriticalSection(5);
	LeaveResourceCriticalSection(6);

	EndingFunction(14); // Do not remove - for testing purposes
}

//4+5+6,1,(2,3),(1,2)-4-5-6
void TestCase15()
{
	StartingFunction(15); // Do not remove - for testing purposes

	// TODO - add extra code to increment your value for resource 4
	EnterResourceCriticalSection(1);
	EnterResourceCriticalSection(2);
	EnterResourceCriticalSection(3);
	IncrementResourceAndEnterCriticalSection(4);
	int iTemp4 = StartToUseResource(4); // Do not remove - for testing purposes
	// TODO - add extra code to increment your value for resource 5
	IncrementResourceAndEnterCriticalSection(5);
	int iTemp5 = StartToUseResource(5); // Do not remove - for testing purposes
	// TODO - add extra code to increment your value for resource 6
	IncrementResourceAndEnterCriticalSection(6);
	int iTemp6 = StartToUseResource(6); // Do not remove - for testing purposes

	TestCase1(); // Do not remove - for testing purposes
	TestCase7(); // Do not remove - for testing purposes
	TestCase6(); // Do not remove - for testing purposes

	FinishUsingResource(4, iTemp4); // Do not remove - for testing purposes
	FinishUsingResource(5, iTemp5); // Do not remove - for testing purposes
	FinishUsingResource(6, iTemp6); // Do not remove - for testing purposes

	LeaveResourceCriticalSection(1);
	LeaveResourceCriticalSection(2);
	LeaveResourceCriticalSection(3);
	LeaveResourceCriticalSection(4);
	LeaveResourceCriticalSection(5);
	LeaveResourceCriticalSection(6);


	EndingFunction(15); // Do not remove - for testing purposes
}

void InitialCode(int iDelay)
{
	StartingFunction(-1); // Do not remove - for testing purposes
	SimulateProcessingTime(iDelay);
	EndingFunction(-1); // Do not remove - for testing purposes
}

void RemainderCode(int iDelay)
{
	StartingFunction(-2); // Do not remove - for testing purposes
	SimulateProcessingTime(iDelay); // Do not remove - for testing purposes
	EndingFunction(-2); // Do not remove - for testing purposes
}

void SendDataToServer(int iProcessOrThreadID)
{
	StartingFunction(-3); // Do not remove - for testing purposes

	//just send data to the message queue
	PostMessage(::FindWindow("Bxf03uThreadActivity", NULL), WM_USER + iProcessOrThreadID - 1, NULL, NULL); //starts at 1

	for (int i = 0; i < RESOURCE_COUNT; i++)
	{
		PostMessage(::FindWindow("Bxf03uResourceActivity", NULL), WM_USER + i, resourceCounters[i], NULL);
	}

	EndingFunction(-3); // Do not remove - for testing purposes
}


// Thread 1 should run this
DWORD WINAPI Procedure1(LPVOID lpParm)
{
	InitialCode(1000); // Do not remove - for testing purposes

	for (int i = 0; i < 100; i++) // Do not remove - for testing purposes
	{ // Do not remove - for testing purposes
		TestCase1(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase6(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase11(); // Do not remove - for testing purposes
		RemainderCode(500); // Do not remove - for testing purposes
		SendDataToServer(1); // Do not remove - for testing purposes
	} // Do not remove - for testing purposes
	return 1;
}

// Thread 2 should run this
DWORD WINAPI Procedure2(LPVOID lpParm)
{
	InitialCode(1000); // Do not remove - for testing purposes

	for (int i = 0; i < 100; i++) // Do not remove - for testing purposes
	{ // Do not remove - for testing purposes
		TestCase2(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase7(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase12(); // Do not remove - for testing purposes
		RemainderCode(500); // Do not remove - for testing purposes
		SendDataToServer(2); // Do not remove - for testing purposes
	}
	return 1;
}

// Thread 3 should run this
DWORD WINAPI Procedure3(LPVOID lpParm)
{
	InitialCode(1000); // Do not remove - for testing purposes

	for (int i = 0; i < 100; i++) // Do not remove - for testing purposes
	{ // Do not remove - for testing purposes
		TestCase3(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase8(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase13(); // Do not remove - for testing purposes
		RemainderCode(500); // Do not remove - for testing purposes
		SendDataToServer(3); // Do not remove - for testing purposes
	} // Do not remove - for testing purposes
	return 1;
}

// Thread 4 should run this
DWORD WINAPI Procedure4(LPVOID lpParm)
{
	InitialCode(1000); // Do not remove - for testing purposes

	for (int i = 0; i < 100; i++) // Do not remove - for testing purposes
	{ // Do not remove - for testing purposes
		TestCase4(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase9(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase14(); // Do not remove - for testing purposes
		RemainderCode(500); // Do not remove - for testing purposes
		SendDataToServer(4); // Do not remove - for testing purposes
	} // Do not remove - for testing purposes
	return 1;
}

// Thread 5 should run this
DWORD WINAPI Procedure5(LPVOID lpParm)
{
	InitialCode(1000); // Do not remove - for testing purposes

	for (int i = 0; i < 100; i++) // Do not remove - for testing purposes
	{ // Do not remove - for testing purposes
		TestCase5(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase10(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase15(); // Do not remove - for testing purposes
		RemainderCode(500); // Do not remove - for testing purposes
		RemainderCode(500); // Do not remove - for testing purposes
		SendDataToServer(5); // Do not remove - for testing purposes
	} // Do not remove - for testing purposes
	return 1;
}


void IncrementResourceAndEnterCriticalSection(int resourceId)
{
	EnterCriticalSection(&resourceCrits[resourceId - 1]);
	//since we are in the critical section we can safely increment
	++resourceCounters[resourceId - 1];
}

void EnterResourceCriticalSection(int resourceId)
{
	EnterCriticalSection(&resourceCrits[resourceId - 1]);
}

void LeaveResourceCriticalSection(int resourceId)
{
	LeaveCriticalSection(&resourceCrits[resourceId - 1]);
}

int main(int argc, char* argv[])
{
	Sleep(100);

	//function pointers to create threads programmatically
	LPTHREAD_START_ROUTINE procedures[] = { Procedure1, Procedure2, Procedure3, Procedure4, Procedure5 };
	
	//create a CRITICAL_SECTION for each resource
	for (int i = 0; i < RESOURCE_COUNT; i++)
	{
		InitializeCriticalSection(&resourceCrits[i]);
	}

	//storing threads to wait for them
	HANDLE threads[THREAD_COUNT];
	
	for (int i = 0; i < THREAD_COUNT; i++)
	{
		threads[i] = CreateThread(NULL, 0, procedures[i], 0, 0, NULL);
	}

	//wait until threads die
	WaitForMultipleObjects(THREAD_COUNT, threads, TRUE, INFINITE);


	//threads dead, close handles
	for (int i = 0; i < THREAD_COUNT; i++)
		CloseHandle(threads[i]);

	//print resources and delete the associated CRITICAL_SECTION
	printf("resources used:\n");
	for (int i = 0; i < RESOURCE_COUNT; i++)
	{
		printf("%d ", resourceCounters[i]);
		DeleteCriticalSection(&resourceCrits[i]);
	}
	printf("\n");


	printf("Press ENTER to exit\n");
	while (getchar() != '\n')
		;
}
