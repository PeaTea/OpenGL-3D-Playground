#ifndef FILE_H
#define FILE_H

#pragma once

#include <string>
#include <fstream>
#include <vector>

#include "Types.h"

class File
{
public:
    File(const std::string& filepath, bool create_new = false);
    ~File();

    std::string path() const;
    void path(const std::string& filepath, bool create_new = false);

    std::string read();
    std::vector<std::string> read_lines();
    std::vector<std::string> read_words();

    void write(const std::string& txt);
    void close();
    void open();
    void clear();
    void copy_to(conststrref filepath, bool create_new = false);
    void copy_from(conststrref filepath);

private:
    std::string m_path;
    std::fstream m_file;
    int m_flags;

    bool m_not_read;
    bool m_not_written;
};

#endif