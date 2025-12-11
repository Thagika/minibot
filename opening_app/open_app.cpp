#include <windows.h>
#include <iostream>
#include <fstream>

#include "open_app.hpp"
#include "readfile/readconfig.hpp"
int openapp::startapp()
{

    STARTUPINFO si = {sizeof(si)};
    PROCESS_INFORMATION pi;

    readconfig configReader;

    std::string gamepath = configReader.getFilePath("gamePath");

    BOOL success = CreateProcess(
        gamepath.c_str(), //  (use NULL if passing the path in the second argument)
        NULL,             // lpCommandLine (NULL here means appPath is used from first argument)
        NULL, NULL,       // Process & thread security
        FALSE,            // Inherit handles
        0,                // Flags
        NULL,             // Env vars
        NULL,             // Working directory
        &si, &pi);        // Startup info & Process info

    if (!success)
    {
        MessageBox(NULL, "Failed to start application.", "Error", MB_OK);
        std::cerr << "CreateProcess failed. Error code: " << GetLastError() << std::endl;
        return 1;
    }

    std::cout << "Game started with Process ID: " << pi.dwProcessId << std::endl;

    // Wait for the game process to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Clean up handles when done waiting
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    std::cout << "Game process finished." << std::endl;
    return 0; // Indicate success
}

int openapp::get_startapp()
{
    return startapp();
}