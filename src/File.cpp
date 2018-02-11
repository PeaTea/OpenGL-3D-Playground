#include "File.h"
#include "OutUtils.h"

#include <sstream>
#include <iterator>

File::File(const std::string& filepath, bool create_new)
    :   m_path  {filepath}
{
    m_flags = ((create_new) ? std::ios::trunc : std::ios::app) | std::ios::out | std::ios::in;
    m_file.open(m_path, m_flags);
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
}

std::string File::read()
{
    if(m_not_read)
    {
        m_file.seekg(0);
        m_not_read = false;
        m_not_written = true;
    }

    std::stringstream ss;
    ss << m_file.rdbuf();
    
    return ss.str();
}

std::vector<std::string> File::read_lines()
{
    if(m_not_read)
    {
        m_file.seekg(0);
        m_not_read = false;
        m_not_written = true;
    }

    std::vector<std::string> lines;

    std::string line;
    while(std::getline(m_file, line))
    {
        lines.push_back(line);
    }

    return lines;
}

std::vector<std::string> File::read_words()
{
    if(m_not_read)
    {
        m_file.seekg(0);
        m_not_read = false;
        m_not_written = true;
    }

    std::vector<std::string> lines;

    std::copy(std::istream_iterator<std::string>(m_file),
              std::istream_iterator<std::string>(),
              std::back_inserter(lines));

    return lines;
}

void File::write(const std::string& txt)
{
    if(m_not_written)
    {
        m_file.seekp(m_file.tellg());
        m_not_written = false;
        m_not_read = true;
    }

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