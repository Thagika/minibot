#ifndef READCONFIG_HPP
#define READCONFIG_HPP

#include <string>
#include <iostream> // Needed for std::cerr inside the definition

class readconfig
{
private:
    // We can define members here
    std::string filename = "path.cfg";

    // Declaration of the private helper function
    std::string readValue(const std::string &key);

public:
    // Declaration of the public interface function
    // This is the function you call from your main code
    std::string getFilePath(const std::string &key);
};

#endif // READCONFIG_HPP
