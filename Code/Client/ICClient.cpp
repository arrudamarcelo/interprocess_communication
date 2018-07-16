//#include "stdafx.h"
#include "ICClient.h"

#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>
#include <variant>
#include "../CoreObjects/ClassIOProcess.h"
#include "../CoreObjects/ClassKernelProcess.h"

#define BUFSIZE 512

ICClient::ICClient()
{
	createPipe(TEXT("\\\\.\\pipe\\mynamedpipe"));
	sendMessage(TEXT("GET PROCESSES LIST"));
	sendMessage(TEXT("GET ClassIOProcess"));
	sendMessage(TEXT("GET ClassKernelProcess"));
	sendMessage(TEXT("GET ClassUnknown"));
}


ICClient::~ICClient()
{
	closePipe();
}

int ICClient::createPipe(LPTSTR lpszPipename)
{
	// Try to open a named pipe; wait for it, if necessary. 
	while (1)
	{
		_hPipe = CreateFile(
			lpszPipename,   // pipe name 
			GENERIC_READ |  // read and write access 
			GENERIC_WRITE,
			0,              // no sharing 
			NULL,           // default security attributes
			OPEN_EXISTING,  // opens existing pipe 
			0,              // default attributes 
			NULL);          // no template file 

							// Break if the pipe handle is valid. 

		if (_hPipe != INVALID_HANDLE_VALUE)
			break;

		// Exit if an error other than ERROR_PIPE_BUSY occurs. 

		if (GetLastError() != ERROR_PIPE_BUSY)
		{
			_tprintf(TEXT("Could not open pipe. GLE=%d\n"), GetLastError());
			return -1;
		}

		// All pipe instances are busy, so wait for 20 seconds. 

		if (!WaitNamedPipe(lpszPipename, 20000))
		{
			printf("Could not open pipe: 20 second wait timed out.");
			return -1;
		}
	}

	return 1;
}

bool ICClient::closePipe()
{
	return CloseHandle(_hPipe);
}

int ICClient::sendMessage(LPTSTR lpvMessage)
{
	// The pipe connected; change to message-read mode. 
	BOOL   fSuccess = FALSE;
	DWORD  cbRead, cbToWrite, cbWritten;
	TCHAR  chBuf[BUFSIZE];

	_dwMode = PIPE_READMODE_MESSAGE;
	fSuccess = SetNamedPipeHandleState(
		_hPipe,    // pipe handle 
		&_dwMode,  // new pipe mode 
		NULL,     // don't set maximum bytes 
		NULL);    // don't set maximum time 
	if (!fSuccess)
	{
		_tprintf(TEXT("SetNamedPipeHandleState failed. GLE=%d\n"), GetLastError());
		return -1;
	}

	// Send a message to the pipe server. 

	cbToWrite = (lstrlen(lpvMessage) + 1) * sizeof(TCHAR);
	_tprintf(TEXT("Sending %d byte message: \"%s\"\n"), cbToWrite, lpvMessage);

	fSuccess = WriteFile(
		_hPipe,                  // pipe handle 
		lpvMessage,             // message 
		cbToWrite,              // message length 
		&cbWritten,             // bytes written 
		NULL);                  // not overlapped 

	if (!fSuccess)
	{
		_tprintf(TEXT("WriteFile to pipe failed. GLE=%d\n"), GetLastError());
		return -1;
	}

	std::cout << "\nMessage sent to server: '" + std::string(lpvMessage) + "'\n" << std::endl;

	do
	{
		// Read from the pipe. 

		fSuccess = ReadFile(
			_hPipe,    // pipe handle 
			chBuf,    // buffer to receive reply 
			BUFSIZE * sizeof(TCHAR),  // size of buffer 
			&cbRead,  // number of bytes read 
			NULL);    // not overlapped 

		if (!fSuccess && GetLastError() != ERROR_MORE_DATA)
			break;

		handleReply(lpvMessage, chBuf);

	} while (!fSuccess);  // repeat loop if ERROR_MORE_DATA 

	if (!fSuccess)
	{
		_tprintf(TEXT("ReadFile from pipe failed. GLE=%d\n"), GetLastError());
		return -1;
	}

	std::cout << "---------------------------------------------------" << std::endl;
	printf("\n<End of message, press ENTER to continue execution>");
	_getch();

	return 0;
}

void ICClient::handleReply(LPTSTR lpvMessageType, TCHAR* chReplyMessage) {
	std::cout << "Message received from the server.\n" << std::endl;

	std::string messageType = std::move(lpvMessageType);
	std::cout << "Raw message: \n" << chReplyMessage << std::endl;
	if (messageType != "GET PROCESSES LIST") { //already printed above
		std::string replyMessage = std::move(chReplyMessage);
		if(messageType == "GET ClassIOProcess"){
			auto obj = ClassIOProcess();
			obj.deserialize(replyMessage);
			std::cout << "Class " << obj.className() + " created." << std::endl;
			obj.printAttribValues();
		}
		else if (messageType == "GET ClassKernelProcess") {
			auto obj = ClassKernelProcess();
			obj.deserialize(replyMessage);
			std::cout << "Class " << obj.className() + " created." << std::endl;
			obj.printAttribValues();
		}
		else {
			std::cout << replyMessage << std::endl;
		}
	}
}