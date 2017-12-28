#include "File.h"

#include "Logging.h"
#include <sstream>
#include <iterator>

File::File()
    :   name    {""}
{
}

File::File(const std::string& filename)
    :   name    {filename}
{
}

std::string File::get_name() const 
{
    if(name != "")	
        return name;
    else 
        logging::log("No filename specified for get_name()", lstream::error);
}

void File::set_name(const std::string& filename)
{
    name = filename;
}

std::string File::read(const std::string& filename)
{
    if(filename == "" && name == "")
        logging::log("No filename", lstream::error);

    std::ifstream file { ((name == "") ? filename : name), std::ios::binary };

    if(file.fail())
        logging::log("Error opening file - maybe wrong path?:" + name + "\n", lstream::error);

    std::stringstream ss;
    ss << file.rdbuf();
    
    return ss.str();
}

std::vector<std::string> File::read_lines(const std::string& filename)
{
    if(filename == "" && name == "")
        logging::log("No filename", lstream::error);

    std::vector<std::string> lines;
    std::ifstream file { name == "" ? filename : name, std::ios::binary };

    if(file.fail())
        logging::log("Error opening file (maybe wrong path?):" + name + "\n", lstream::error);

    std::string line;
    while(std::getline(file, line))
    {
        lines.push_back(line);
    }

    return lines;
}

std::vector<std::string> File::read_words(const std::string& filename)
{
    if(filename == "" && name == "")
        logging::log("No filename", lstream::error);

    std::vector<std::string> lines;
    std::ifstream file{name == "" ? filename : name, std::ios::binary};

    if(file.fail())
        logging::log("Error opening file (maybe wrong path?):" + name + "\n", lstream::error);

    std::copy(std::istream_iterator<std::string>(file),
              std::istream_iterator<std::string>(),
              std::back_inserter(lines));

    return lines;
}

void File::write(const std::string& txt, const std::string& filename)
{
    if(filename == "" && name == "")
        logging::log("No filename for contents:\n  " + txt + "\n", lstream::error);

    std::ofstream file { name == "" ? filename : name };
    file << txt;
}
