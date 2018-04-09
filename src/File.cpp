#include "File.h"
#include "OutUtils.h"

#include <sstream>
#include <iterator>

File::File(const std::string& filepath, bool create_new)
    :   m_path          {filepath}
{
    m_flags = ((create_new) ? std::ios::trunc : std::ios::app) | std::ios::out | std::ios::in;
    m_file.open(m_path, m_flags);
    if(m_file.fail())
    {
        logging::log("Failed to open file " + filepath, lstream::exception);
    }
}

File::File(const File& o)
{
    m_path = o.m_path;
    m_flags = o.m_flags;
}

File::~File()
{
    close();
}

std::string File::path() const 
{
    return m_path;
}

void File::path(const std::string& filepath, bool create_new)
{
    m_path = filepath;
    m_file.close();
    m_flags = ((create_new) ? std::ios::trunc : std::ios::app) | std::ios::out | std::ios::in;
    m_file.open(m_path, m_flags);
    if(m_file.fail())
    {
        logging::log("Failed to open file " + filepath, lstream::exception);
    }
}

std::string File::read(const bool& reset_fp)
{
    if(reset_fp) m_file.seekg(0);
    std::stringstream ss;
    ss << m_file.rdbuf();
    
    return ss.str();
}

std::vector<std::string> File::read_lines(const bool& reset_fp)
{
    if(reset_fp) m_file.seekg(0);
    std::vector<std::string> lines;

    std::string line;
    while(std::getline(m_file, line))
    {
        lines.push_back(line);
    }

    return lines;
}

std::vector<std::string> File::read_words(const bool& reset_fp)
{
    if(reset_fp) m_file.seekg(0);
    std::vector<std::string> lines;

    std::copy(std::istream_iterator<std::string>(m_file),
              std::istream_iterator<std::string>(),
              std::back_inserter(lines));

    return lines;
}

uint File::lines()
{
    return std::count(std::istream_iterator<char>(m_file),
                      std::istream_iterator<char>(),
                      '\n');
}

void File::write(const std::string& txt, const bool& reset_fp)
{
    if(reset_fp) m_file.seekp(0);
    m_file << txt;
}

void File::close()
{
    m_file.close();
}

void File::open()
{
    m_file.open(m_path, m_flags);
}

void File::clear()
{
    path(m_path, true);
}

void File::copy_to(conststrref filepath, bool create_new)
{
    File target {filepath, create_new};
    target.write(read());
}

void File::copy_from(conststrref filepath)
{
    File target {filepath};
    write(target.read());
}