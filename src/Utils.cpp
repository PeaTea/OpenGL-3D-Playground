#include "Utils.h"

#include <sstream>

namespace utils
{
    std::string discard(conststrref str, conststrref exclude)
    {
        std::stringstream stream {str};

        std::string buffer;
        for(int i{-1}; i < exclude.size(); ++i)
        {
            std::stringstream stream_buffer;
            while(std::getline(stream, buffer, exclude[i]))
            {
                stream_buffer << buffer;
            }
            stream.str(std::string{});
            stream.clear();
            stream << stream_buffer.str();
        }
        return stream.str();
    }

    std::vector<std::string> split(conststrref str, const char& exclude)
    {
        std::istringstream stream {str};
        std::string part;
        std::vector<std::string> parts;

        while(std::getline(stream, part, exclude))
        {
            parts.push_back(part);
        }

        return parts;
    }
}