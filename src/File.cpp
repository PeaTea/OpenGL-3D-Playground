#include "File.h"

File::File()
{
}

File::File(const std::string& filename)
{
    name = filename;
    read();
}

std::string File::get_contents()
{
    if(contents != "")	return contents;
    else throw std::runtime_error("File has not yet been read!");
}

std::string File::get_name()
{
    if(name != "")	return name;
    else throw std::runtime_error("Filename has not yet been set!");
}

void File::set_name(const std::string& filename)
{
    name = filename;
}

void File::read()
{
    if(name != "")
    {
        std::ifstream in_file;
        std::string line;

        in_file.open(name);
        if(in_file.fail())
        {
            throw std::runtime_error("Error opening file (maybe wrong path?):" + name + "\n");
        }

        while(getline(in_file, line))
        {
            contents += (line + "\n");
        }

        in_file.close();
    } 
    else
    {
        throw std::runtime_error("Filename has not yet been set!");
    }
}
