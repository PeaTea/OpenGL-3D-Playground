#include "Logging.h"

#include "File.h"
#include <iostream>

namespace logging
{
    void log(const std::string& msg, lstream log_stream)
    {
        char* streams[3] = { "INFO", "WARNING", "ERROR" };
        std::cout << streams[(int)log_stream] << ": " << msg << std::endl;
        if((int)log_stream == 2)
        {
            std::cin.get();
            std::exit(1);
        }
    }

    void log_to_file(const std::string& msg, const std::string& filename)
    {
        File out(filename);
        out.write(msg);
    }
}