#include "Logging.h"

#include "File.h"
#include <iostream>

namespace logging
{
    template <typename T>
    void log(const T& msg, lstream log_stream)
    {   
        char* streams[3] = {"INFO", "WARNING", "ERROR"};

        std::cout << streams[(int)log_stream] << msg << std::endl;
    }

    template <typename T>
    bool log_to_file(const T& msg, const std::string& filename)
    {
        File out(filename);
        out.write(msg);
    }
}