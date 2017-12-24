#include "File.h"

#include "Logging.h"
#include <sstream>

File::File()
    :   name    {""}
{
}

File::File(const std::string& filename)
    :   name    {filename}
{
}

std::string File::get_contents() 
{
    if(contents != "")	return contents;
    else
    {
        read();
        return contents;
    }
}

std::string File::get_name() const 
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

        in_file.open(name, std::ios::binary);
        if(in_file.fail())
        {
            throw std::runtime_error("Error opening file (maybe wrong path?):" + name + "\n");
        }

        std::stringstream ss;
        ss << in_file.rdbuf();
        contents = ss.str();

        in_file.close();
    } 
    else
    {
        throw std::runtime_error("No filename specified");
    }
}

template <typename T>
void File::write(const T& txt)
{
    if(name != "")
    {
        std::ofstream file { name };
        file << txt;
        file.close();
    }
    else
    {
        throw std::runtime_error("No filename specified for contents: " + std::to_string(txt) + "\n");
    }
}
