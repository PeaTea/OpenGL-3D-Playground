#pragma once

#include "Timer.h"
#include "File.h"

#include <sstream>

/*
 *ptest   : Performance tests
 *test    : Functionality tests
 */

void ptest_files_write()
{
    {
        RAIITimer timer = "Class: File";
        File f{"testw.txt", true};
        for(int i{1000000}; i > 0; --i)
        {
            f.write("example\n");
        }
    }

    {
        RAIITimer timer2 = "std::fstream";
        std::fstream f{"testw2.txt", std::ios::in | std::ios::out | std::ios::trunc};
        for(int i{1000000}; i > 0; --i)
        {
            f << "example\n";
        }
    }
}

void ptest_files_read()
{
    {
        RAIITimer timer = "Class: File";
        File f{"testr.txt"};
        f.copy_to("testrcpy.txt", true);
    }

    {
        RAIITimer timer = "std::fstream";
        std::ifstream file{"testr.txt"};
        std::ofstream file2{"testrcpy2.txt"};
        file2 << file.rdbuf();
    }
}

void test_files_multiple_read()
{
    {
        RAIITimer timer = "Class: File";
        File f1 {"testr.txt"};
        output::print(f1.read());
        output::print(f1.read());
        output::print(f1.read());
    }
}

void test_files_read_line()
{
    {
        RAIITimer timer = "Class: File";
        File f1 {"testr.txt"};
        const uint& i = 0;
        output::print(f1.read_lines()[i]);
    }
}