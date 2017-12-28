#ifndef FILE_H
#define FILE_H

#include <string>
#include <fstream>
#include <vector>

class File
{
public:
    File();
    File(const std::string& filename);

    std::string get_name() const;

    void set_name(const std::string& filename);
    std::string read(const std::string& filename = "");
    std::vector<std::string> read_lines(const std::string& filename = "");
    std::vector<std::string> read_words(const std::string& filename = "");

    void write(const std::string& txt, const std::string& filename = "");

private:
    std::string name;
};

#endif