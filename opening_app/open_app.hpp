
#ifndef OPEN_APP_HPP
#define OPEN_APP_HPP

#include <string>
#include <windows.h>

class openapp
{
private:
    openapp() = delete; // Delete default constructor
    static int startapp();

public:
    static int get_startapp();
};

#endif // READCONFIG_HPP