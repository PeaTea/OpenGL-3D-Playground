#ifndef FILE_H
#define FILE_H

#include <string>
#include <fstream>

class File
{
public:
    File();
    File(const std::string& filename);

    std::string get_contents();
    std::string get_name();

    void set_name(const std::string& filename);
    void read();

private:
    std::string name;
    std::string contents;
};

#endif