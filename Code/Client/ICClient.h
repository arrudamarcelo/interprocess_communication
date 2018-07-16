#pragma once

/*
* Interprocess Communication example using named pipes
* Client adapted from "Named Pipe Client":
* https://docs.microsoft.com/en-us/windows/desktop/ipc/named-pipe-client
*/
#include <string> 
#include <windows.h> 

class ICClient
{
public:
	ICClient();
	~ICClient();

private:
	//pipe status mode
	DWORD _dwMode;

	//pipe handle
	HANDLE _hPipe;

	/*
	* Create the named pipe with the server
	* @param[in] Pipe name
	* return Success case return 1. Fail case return -1;
	*/
	int createPipe(LPTSTR lpszPipename);

	/*
	* Close the pipe when is no longer necessary
	* @param[in] Pipe name
	* return Success case return 1. Fail case return -1;
	*/
	bool closePipe();

	/*
	* Send message to the server using the named pipe
	*/
	int sendMessage(LPTSTR lpvMessage);

	/*
	* Handle the reply sent by the server
	*/
	void handleReply(LPTSTR lpvMessageType, TCHAR* chAnswer);

};

