#pragma once

/*
* Interprocess Communication example using named pipes
* Server adapted from "Named Pipe Server Using Overlapped I/O":
* https://docs.microsoft.com/en-us/windows/desktop/ipc/named-pipe-server-using-overlapped-i-o
*/
#include "../CoreObjects/ClassIOProcess.h"
#include "../CoreObjects/ClassKernelProcess.h"
#include <windows.h> 

class ICServer
{
public:
	ICServer();

private:
	
	int ICServer::initializePipe(LPTSTR lpszPipename);

};

