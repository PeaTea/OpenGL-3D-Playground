#ifndef FILE_H
#define FILE_H

#pragma once

#include <string>
#include <fstream>
#include <vector>

#include "Types.h"

const std::string FILE_FAILED_TO_OPEN = "Failed to open file: ";

class File
{
public:
    File(conststrref filepath, bool create_new = false);
    ~File();
    File(const File& o);

    std::string path() const;
    void path(conststrref filepath, bool create_new = false);

    std::string read(const bool& reset_fp = false);
    std::vector<std::string> read_lines(const bool& reset_fp = false);
    std::vector<std::string> read_words(const bool& reset_fp = false);

    uint lines();

    void write(conststrref txt, const bool& reset_fp = false);
    void close();
    void open();
    void clear();
    void copy_to(conststrref filepath, bool create_new = false);
    void copy_from(conststrref filepath);

private:
    std::string m_path;
    std::fstream m_file;
    int m_flags;
};


namespace file
{
    bool exists(conststrref filename);
}

#endif