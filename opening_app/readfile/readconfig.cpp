#include "readconfig.hpp" // Include the class declaration
#include <fstream>
#include <string>

// Definition of the private helper function
std::string readconfig::readValue(const std::string &key)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Could not open the config file: " << filename << std::endl;
        return "";
    }

    std::string line;
    while (std::getline(file, line))
    {
        size_t delimiterPos = line.find('=');
        if (delimiterPos != std::string::npos)
        {
            std::string currentKey = line.substr(0, delimiterPos);
            // You might want to trim currentKey here for robustness
            if (currentKey == key)
            {
                return line.substr(delimiterPos + 1);
            }
        }
    }

    std::cerr << "Key not found in config file: " << key << std::endl;
    return "";
}

// Definition of the public interface function
std::string readconfig::getFilePath(const std::string &key)
{
    // This calls the private helper function from within the class scope
    return readValue(key);
}
