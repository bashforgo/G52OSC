// Only keep the main windows functions from windows.h:
#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#undef UNICODE


// Use 4 byte IP addresses - old mode
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1


// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

// Pick a port
#define DEFAULT_PORT 1337

#include "DoNotChangeThese.h"

#define THREAD_COUNT 5
#define RESOURCE_COUNT 6

struct DataClientToServer
{
	int processID;
	int resourceValues[RESOURCE_COUNT];
};

union WrapperDataClientToServer
{
	DataClientToServer a;
	char b[sizeof(DataClientToServer)];
};


struct shared
{
	volatile unsigned int resourceCounters[RESOURCE_COUNT];
	HANDLE resourceCrits[RESOURCE_COUNT];
};

SOCKET ConnectSocket;

volatile shared* pShared;

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

	//create a new wrapper
	WrapperDataClientToServer message;

	//say who we are
	message.a.processID = iProcessOrThreadID - 1 + THREAD_COUNT;

	//copy resource values
	for (int i = 0; i < RESOURCE_COUNT; i++)
	{
		message.a.resourceValues[i] = pShared->resourceCounters[i];
	}

	//send the message
	int result = send(ConnectSocket, message.b, (int)sizeof(message), 0);
	if (result == SOCKET_ERROR)
	{
		//and hope that it goes through
		printf("ConnectSocket shutdown failed with error: %d\n", WSAGetLastError());
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

volatile shared* GetSharedMemory()
{
	HANDLE mapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,    // use paging file
		NULL,                    // default security
		PAGE_READWRITE,          // read/write access
		0, sizeof(shared), // max size high,low DWORDs
		"Local\\Bxf03uShared"); // name of mapping object

	if (mapFile == NULL)
	{
		printf("Could not create file mapping object (%d).\n",
			GetLastError());
		return NULL;
	}
	
	volatile shared * _shared =
		(shared *)MapViewOfFile(
		mapFile,   // handle to map object
		FILE_MAP_ALL_ACCESS, // read/write permission
		0,
		0,
		sizeof(shared));

	if (_shared == NULL)
	{
		printf(TEXT("Could not map view of file (%d).\n"),
			GetLastError());
		CloseHandle(mapFile);
		return NULL;
	}

	return _shared;

}


void IncrementResourceAndEnterCriticalSection(int resourceId)
{
	WaitForSingleObject(pShared->resourceCrits[resourceId - 1], INFINITE);
	//since we are in the critical section we can safely increment
	++pShared->resourceCounters[resourceId - 1];
}

void EnterResourceCriticalSection(int resourceId)
{
	WaitForSingleObject(pShared->resourceCrits[resourceId - 1], INFINITE);
}

void LeaveResourceCriticalSection(int resourceId)
{
	ReleaseMutex(pShared->resourceCrits[resourceId - 1]);
}

int InitialiseServerConnection()
{
	WSADATA wsaData;
	//initialise WSA
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	struct sockaddr_in serveraddress;
	serveraddress.sin_family = AF_INET;
	serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1"); // Local machine
	serveraddress.sin_port = htons(DEFAULT_PORT);

	// Create a SOCKET for connecting to server
	ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ConnectSocket == INVALID_SOCKET)
	{
		printf("ConnectSocket socket failed with error: %ld\n", WSAGetLastError());
		return 2;
	}

	// Connect to server.
	iResult = connect(ConnectSocket, (sockaddr*)&serveraddress, sizeof(serveraddress));
	if (iResult == SOCKET_ERROR)
	{
		printf("ConnectSocket connect failed with error: %ld\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		ConnectSocket = INVALID_SOCKET;
		return 3;
	}

	return 0;
}

int CloseServerConnection()
{
	//close the socket
	closesocket(ConnectSocket);

	//clean up wsa
	WSACleanup();
	ConnectSocket = INVALID_SOCKET;
	return 0;
}

int main(int argc, char* argv[])
{
	Sleep(100);

	if (argc == 1)
	{
		//no arguments, this is the launcher

		//create and get the shared memory
		pShared = GetSharedMemory();


		//security to make mutexes inheritable to child processes
		auto inheritable = SECURITY_ATTRIBUTES
		{
			sizeof(SECURITY_ATTRIBUTES), NULL, TRUE
		};

		//create a mutex for each resource
		for (int i = 0; i < RESOURCE_COUNT; i++)
		{
			pShared->resourceCrits[i] = CreateMutex(&inheritable, FALSE, NULL);
		}


		//store process information and handles to wait for them
		PROCESS_INFORMATION processes[THREAD_COUNT];
		HANDLE processHandles[THREAD_COUNT];

		//string for launching processes
		char fullFilePath[1024];
		GetModuleFileName(NULL, fullFilePath, 1024);

		//create THREAD_COUNT processes
		for (int i = 0; i < THREAD_COUNT; i++)
		{
			char cmd[1024];
			//pass process number on command line
			sprintf_s(cmd, "%s %d", fullFilePath, i);

			//start it
			STARTUPINFO startInfo = { sizeof(startInfo) };
			if (!CreateProcess(
				fullFilePath, // Program
				cmd,// Command line
				NULL, NULL, TRUE,
				0, //I don't like a billion new windows, inherit the console
				NULL, NULL,
				&startInfo,
				&processes[i]))
			{
				printf("CreateProcess failed (%d).\n", GetLastError());
				return 1;
			}
			//save a handle for waiting
			processHandles[i] = processes[i].hProcess;
		}

		//wait for processes to die
		WaitForMultipleObjects(THREAD_COUNT, processHandles, TRUE, INFINITE);


		//close process handles
		for (int i = 0; i < THREAD_COUNT; i++)
		{
			CloseHandle(processHandles[i]);
			CloseHandle(processes[i].hThread);
		}

		//print resources and close the associated mutex
		printf("resources used:\n");
		for (int i = 0; i < RESOURCE_COUNT; i++)
		{
			printf("%d ", pShared->resourceCounters[i]);
			CloseHandle(pShared->resourceCrits[i]);
		}
		printf("\nPress ENTER to exit\n");
		while (getchar() != '\n')
			;

		return 0;
	}
	else if (argc == 2)
	{
		//argument received, child process

		//get the created shared memory
		pShared = GetSharedMemory();
	
		//initialise a connection to the server
		if (InitialiseServerConnection())
		{
			printf("server connection failed\n");
			getchar();
			return 1;
		}

		//function pointers to create processes programmatically
		LPTHREAD_START_ROUTINE procedures[] = { Procedure1, Procedure2, Procedure3, Procedure4, Procedure5 };

		//run the associated procedure
		procedures[atoi(argv[1])](NULL);

		//done, close server connection
		CloseServerConnection();

		return 0;
	}


	return 0;
}
