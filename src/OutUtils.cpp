#include "OutUtils.h"

#include "File.h"

namespace logging
{
    constexpr char* streams[] = { "INFO", "WARNING", "EXCEPTION", "FATAL_ERROR" };

    void log(const std::string& msg, lstream log_stream)
    {
        if(log_stream == lstream::exception)
            throw std::runtime_error("FATAL_ERROR: " + msg + "\n");
        else
            std::cout << streams[(int)log_stream] << ": " << msg << '\n';
        if(log_stream == lstream::fatal_error)
            std::exit(1);
    }

    void log_to_file(const std::string& msg, const std::string& filename, lstream log_stream)
    {
        File out(filename, true);
        std::string output = ": " + msg;
        out.write(streams[(int)log_stream] + output);
    }
}

namespace output
{

}