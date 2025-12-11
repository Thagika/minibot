#include <windows.h>
#include <iostream>
#include <tlhelp32.h>
#include <cstdio>
#include "opening_app/open_app.hpp"

DWORD FindProcessByName(const char *name)
{
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (Process32First(snapshot, &entry))
    {
        do
        {
            if (!_stricmp(entry.szExeFile, name))
            {
                CloseHandle(snapshot);
                return entry.th32ProcessID;
            }
        } while (Process32Next(snapshot, &entry));
    }

    CloseHandle(snapshot);
    return 0;
}

// Find the main window handle for a given process ID

struct HandleData
{
    DWORD pid;
    HWND hwnd; // This will store the result
};

HWND FindWindowFromPID(DWORD pid)
{
    HandleData data = {pid, NULL}; // Initialize hwnd to NULL

    // Define the callback function inline or separately
    // The callback uses reinterpret_cast to access the HandleData struct
    EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL
                {
                    // Cast the LPARAM back to our struct pointer type
                    HandleData *pData = reinterpret_cast<HandleData *>(lParam);
                    DWORD winPID = 0;

                    // Get the PID of the window being enumerated
                    GetWindowThreadProcessId(hwnd, &winPID);

                    // Check if PIDs match and the window is visible
                    if (winPID == pData->pid && IsWindowVisible(hwnd))
                    {
                        pData->hwnd = hwnd; // Store result safely in the pointed-to struct
                        return FALSE;       // Stop searching by returning FALSE
                    }
                    return TRUE; // Continue searching by returning TRUE
                },
                // Pass a pointer to the 'data' struct, explicitly cast to LPARAM
                reinterpret_cast<LPARAM>(&data));

    // Return the HWND found within the struct
    return data.hwnd;
}

HWND TrackWindow(DWORD pid)
{
    HWND hwnd = NULL;

    while (true)
    {
        hwnd = FindWindowFromPID(pid);
        if (hwnd != NULL)
            return hwnd;

        Sleep(7000);
    }
}

bool ResizeAndReposition(HWND hwnd, int x, int y, int width, int height)
{
    return SetWindowPos(
        hwnd,
        HWND_TOP,
        x, y,
        width, height,
        SWP_SHOWWINDOW);
}

int main()
{
    std::cout << "Hello, Windows!" << std::endl;

    openapp::get_startapp();

    DWORD gamePID = 0;
    while (gamePID == 0)
    {
        Sleep(200);
        gamePID = FindProcessByName("Asphalt9_gdk_x64_rtl.exe");
    }
    std::cout << "Game process ID: " << gamePID << std::endl;

    HWND hwnd = TrackWindow(gamePID);

    std::cout << "Found window handle: " << hwnd << std::endl;

    ResizeAndReposition(hwnd, 0, 0, 800, 400);

    std::cout << "Window resized and repositioned.\n";

    return 0;
}
