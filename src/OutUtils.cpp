#include "OutUtils.h"

#include "File.h"

namespace logging
{
    constexpr char* streams[3] = { "INFO", "WARNING", "ERROR" };

    void log(const std::string& msg, lstream log_stream)
    {
        std::cout << streams[(int)log_stream] << ": " << msg << '\n';
        if((int)log_stream == 2)
        {
            std::cin.get(); 
            std::exit(1);
        }
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