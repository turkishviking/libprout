#include "utils/file.h"
namespace prout {


File::File(std::string path, std::string writeMode)
{
    std::ofstream::openmode mode;
    if(writeMode == "w")
        mode = std::ofstream::trunc;
    else
        mode = std::ofstream::app;
    file.open(path, std::ofstream::in | std::ofstream::out | mode);
}

std::string File::read()
{
    std::string res;
    if(file.is_open())
    {
        for(std::string line; std::getline(file, line) ; )
        {
            res += line;
        }
    }
    return res;
}

std::vector<std::string> File::readLines()
{
    std::vector<std::string> res;
    if(file.is_open())
    {
        for(std::string line; std::getline(file, line) ; )
        {
            res.push_back(line);
        }
    }
    return res;
}

void File::write(std::string line)
{
    if(file.is_open())
        file << line;
}

void File::write(std::vector<std::string> lines)
{
    if(file.is_open())
        for(auto &line : lines)
            file << line << "\n";
}

void File::close()
{
    file.close();
}

File::~File()
{
    file.close();
}

}
