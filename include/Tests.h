#pragma once

#include "Timer.h"
#include "File.h"

#include <sstream>

void test_files_write()
{
    {
        RAIITimer timer = "class";
        File f{"testw.txt", true};
        for(int i{10000000}; i > 0; i--)
        {
            f.write("example\n");
        }
    }

    {
        RAIITimer timer2 = "ofstream";
        std::fstream f{"testw2.txt", std::ios::in | std::ios::out | std::ios::trunc};
        for(int i{10000000}; i > 0; i--)
        {
            f << "example\n";
        }
    }
}

void test_files_read()
{
    {
        RAIITimer timer = "class";
        File f{"testr.txt"};
        f.copy_to("testrcpy.txt", true);
    }

    {
        RAIITimer timer = "ofstream";
        std::ifstream file{"testr.txt"};
        std::ofstream file2{"testrcpy2.txt"};
        file2 << file.rdbuf();
    }
}