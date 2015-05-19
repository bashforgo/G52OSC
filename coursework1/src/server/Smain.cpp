// Only keep the main windows functions from windows.h:
#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>


#define THREAD_COUNT 10
#define RESOURCE_COUNT 12
#define SOCKET_RESOURCE_COUNT 6

#undef UNICODE


// Use 4 byte IP addresses - old mode
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1


// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

// Pick a port
#define DEFAULT_PORT 1337

// And choose a size for the buffer for data - make it big enough for any input
#define DEFAULT_BUFLEN 512

struct DataForThread
{
	SOCKET ClientSocket;
	int iConnectionNumber;
};

struct DataClientToServer
{
	int processID;
	int resourceValues[SOCKET_RESOURCE_COUNT];
};

union WrapperDataClientToServer
{
	DataClientToServer a;
	char b[sizeof(DataClientToServer)];
};



int threadCounters[THREAD_COUNT];
int resourceCounters[RESOURCE_COUNT];

//colors for bars
HBRUSH getColoredBrush(int i)
{
	COLORREF color;
	switch (i % 4)
	{
	case 0:
		color = 0x00ff8d22;
		break;
	case 1:
		color = 0x003c02fa;
		break;
	case 2:
		color = 0x00fcd50d;
		break;
	case 3:
		color = 0x009900ff;
		break;
	}
	return CreateSolidBrush(color);
}

void drawBars(HWND hwnd, HDC hdc, int* arr, int arrLength)
{
	//fill the window with black (looks better IMO)
	RECT windowRect;
	GetClientRect(hwnd, &windowRect);
	FillRect(hdc, &windowRect, (HBRUSH)GetStockObject(BLACK_BRUSH)); //fill black

	//calculate the width for each bar, try to fill in all the space
	float barWidth = (float)windowRect.right / (float)arrLength;
	int max = 0;

	//find the maximum value in the array
	for (int i = 0; i < arrLength; i++)
	{
		if (max < arr[i]) max = arr[i];
	}
	if (max == 0) return;

	//a unit is this tall
	float barUnitHeight = (float)windowRect.bottom / (float)max;
	for (int i = 0; i < arrLength; i++)
	{
		if (arr[i] == 0) continue;
		//make the bars
		RECT barRect;

		//int conversion makes it have spaces between bars
		barRect.left = (int)(i * barWidth);
		barRect.right = (int)(barRect.left + barWidth);

		//distance from top
		float negHeight = (float)(max - arr[i]) * barUnitHeight;
		barRect.top = (int)negHeight;
		barRect.bottom = windowRect.bottom;

		//draw it
		HBRUSH brush = getColoredBrush(i);
		FillRect(hdc, &barRect, brush);
		DeleteObject(brush); // Free the brush resources
	}
}

LRESULT CALLBACK threadActivity(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
	{	// Added for the painting
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		{ // Draw rectangle
			drawBars(hwnd, hdc, threadCounters, THREAD_COUNT);
		} // End of draw
		EndPaint(hwnd, &ps);
		break;
	}

	default:
		if (WM_USER <= msg && msg <= WM_USER + THREAD_COUNT)
		{
			//update thread/process counter
			++threadCounters[msg - WM_USER];
			InvalidateRect(hwnd, NULL, FALSE);
			UpdateWindow(hwnd);
		}
		else
		{
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
	}
	return 0;
}


LRESULT CALLBACK resourceActivity(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
	{	// Added for the painting
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		{
			drawBars(hwnd, hdc, resourceCounters, RESOURCE_COUNT);
		} // End of draw
		EndPaint(hwnd, &ps);
		break;
	}
	default:
		if (WM_USER <= msg && msg <= WM_USER + RESOURCE_COUNT)
		{
			//update resource counters
			if (resourceCounters[msg - WM_USER] < (int)wParam) resourceCounters[msg - WM_USER] = wParam;
			InvalidateRect(hwnd, NULL, FALSE);
			UpdateWindow(hwnd);
		}
		else
		{
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
	}
	return 0;
}

DWORD WINAPI HandleConnection(LPVOID lpData)
{
	// Grab the info that was passed in ...
	DataForThread* pDataPassedIn = (DataForThread*)lpData;
	SOCKET ClientSocket = pDataPassedIn->ClientSocket;
	int iConnectionNumber = pDataPassedIn->iConnectionNumber;
	// And then delete the data that was passed in
	// (We could just keep using it and delete it later but this prevents forgetting to do so)
	free(pDataPassedIn); // Matches the malloc below (search for it if not sure)
	// Now all of our data is on the stack - so will be tidied up for us

	// We have our own buffer for receiving data
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	int iResult;

	// New for handling a struct-based system.
	int iReceiveIndex = 0; // Index into struct that we are getting
	WrapperDataClientToServer dataReceived = { 0 }; // Initialise the structure to 0

	// Receive until the peer shuts down the connection
	do
	{
		//receive data
		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
		{
			printf("Connection %d: Bytes received: %d\n", iConnectionNumber, iResult);

			// This code will handle the current message
			for (int i = 0; i < iResult; i++)
			{	// Copy the bytes in
				dataReceived.b[iReceiveIndex++] = recvbuf[i];
				// As soon as a message is completed then handle it
				if (iReceiveIndex >= sizeof(DataClientToServer))
				{ // We have a full message now so do something with it:
					iReceiveIndex = 0; // Go back to start for the next one.
					// Now any code to handle this message goes here:

					//just delegate the data as windows messages
					PostMessage(
						FindWindow("Bxf03uThreadActivity", NULL),
						WM_USER + dataReceived.a.processID, //proper number set in client
						NULL, NULL);

					for (int i = 0; i < SOCKET_RESOURCE_COUNT; i++)
					{
						PostMessage(
							FindWindow("Bxf03uResourceActivity", NULL),
							WM_USER + i + SOCKET_RESOURCE_COUNT,
							dataReceived.a.resourceValues[i], NULL);
					}



					// End of new code for reply
				} // End of if condition for the whole message having been received.
			} // End of for loop, looping through the received data

		}
		else if (iResult == 0)
		{
			//done, close the connection
			printf("Connection %d: Connection closing...\n", iConnectionNumber);
		}
		else
		{
			printf("ClientSocket recv failed with error: %d\n", WSAGetLastError());
			closesocket(ClientSocket);
			WSACleanup();
			return 1;
		}
	} while (iResult > 0);

	// shutdown the connection since we're done
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR)
	{
		printf("ClientSocket shutdown failed with error: %d\n", WSAGetLastError());
	}

	// cleanup
	closesocket(ClientSocket);
	return 0; // success
}


DWORD WINAPI SocketListener(LPVOID lpData)
{
	WSADATA wsaData;
	//initialise WSA
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct sockaddr_in localaddress;
	localaddress.sin_family = AF_INET;
	localaddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	localaddress.sin_port = htons(DEFAULT_PORT);

	// Create a SOCKET for connecting to server
	ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListenSocket == INVALID_SOCKET)
	{
		printf("socket failed with error: %ld\n", WSAGetLastError());
		WSACleanup();
		return 2;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, (SOCKADDR *)&localaddress, sizeof(localaddress));
	if (iResult == SOCKET_ERROR)
	{
		printf("bind failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 3;
	}

	//start listening
	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR)
	{
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 4;
	}

	int iConnectionNumber = 0;

	//wait for incoming connections and accept them as they come in:
	while (TRUE)
	{
		// Accept a client socket
		ClientSocket = accept(ListenSocket, NULL, NULL);
		if (ClientSocket == INVALID_SOCKET)
		{
			printf("accept failed with error: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			return 5;
		}

		//send some data to the new threads
		DataForThread* threadData = (DataForThread*)malloc(sizeof(DataForThread));
		threadData->ClientSocket = ClientSocket; // Socket to get data from
		threadData->iConnectionNumber = iConnectionNumber + 1; // number of this connection - add 1 to make it 1-based

		iConnectionNumber++;// Next connection will be 1 higher

		//create a thread to handle it so we can accept new connections
		HANDLE h = CreateThread(NULL, 0, HandleConnection, threadData, 0, NULL);
		CloseHandle(h); // We no longer need the handle to the thread - it is on its own
	}
}



int main()
{
	//////////////////////////////////////////////////////////////////////////
	//create the thread window

	WNDCLASSEX threadActivityWC;
	threadActivityWC.cbSize = sizeof(WNDCLASSEX);
	threadActivityWC.style = 0;
	threadActivityWC.lpfnWndProc = threadActivity; // CHANGES
	threadActivityWC.cbClsExtra = 0;
	threadActivityWC.cbWndExtra = 0;
	threadActivityWC.hInstance = GetModuleHandle(NULL);
	threadActivityWC.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	threadActivityWC.hCursor = LoadCursor(NULL, IDC_ARROW);
	threadActivityWC.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	threadActivityWC.lpszMenuName = NULL;
	threadActivityWC.lpszClassName = "Bxf03uThreadActivity";
	threadActivityWC.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&threadActivityWC))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	HWND threadActivityWH = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"Bxf03uThreadActivity", // NEEDS TO MATCH THE CLASS NAME ABOVE
		"Thread Progress",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 350, 500,
		NULL, NULL, GetModuleHandle(NULL), NULL);
	if (threadActivityWH == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	// Set position to not overlap the other one
	SetWindowPos(threadActivityWH, HWND_TOP, 0, 50, 0, 0, SWP_NOSIZE);
	ShowWindow(threadActivityWH, SW_SHOW);
	UpdateWindow(threadActivityWH);

	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	//now create the resource window

	WNDCLASSEX resourceActivityWC;
	resourceActivityWC.cbSize = sizeof(WNDCLASSEX);
	resourceActivityWC.style = 0;
	resourceActivityWC.lpfnWndProc = resourceActivity; // CHANGES
	resourceActivityWC.cbClsExtra = 0;
	resourceActivityWC.cbWndExtra = 0;
	resourceActivityWC.hInstance = GetModuleHandle(NULL);
	resourceActivityWC.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	resourceActivityWC.hCursor = LoadCursor(NULL, IDC_ARROW);
	resourceActivityWC.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	resourceActivityWC.lpszMenuName = NULL;
	resourceActivityWC.lpszClassName = "Bxf03uResourceActivity"; // CHANGES
	resourceActivityWC.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&resourceActivityWC))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	HWND resourceActivityWH = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"Bxf03uResourceActivity", // NEEDS TO MATCH THE CLASS NAME ABOVE
		"Resource Access",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 380, 500,
		NULL, NULL, GetModuleHandle(NULL), NULL);
	if (resourceActivityWH == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	// Set position to not overlap the other one
	SetWindowPos(resourceActivityWH, HWND_TOP, 360, 50, 0, 0, SWP_NOSIZE);
	ShowWindow(resourceActivityWH, SW_SHOW);
	UpdateWindow(resourceActivityWH);

	//////////////////////////////////////////////////////////////////////////


	//create a thread only listening to sockets
	HANDLE h = CreateThread(NULL, 0, SocketListener, NULL, 0, NULL);
	CloseHandle(h); // We no longer need the handle to the thread - it is on its own

	//this thread will listen to windows messages
	MSG Msg;
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}
