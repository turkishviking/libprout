#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include <vector>

namespace prout
{


class File
{
public:
    File(std::string path, std::string writeMode="a")
    {
        if(writeMode == "w")
            mode = std::ofstream::in | std::ofstream::out | std::ofstream::trunc;
        else
            mode = std::ofstream::in | std::ofstream::out | std::ofstream::app;
        fpath = path;
        file.open(fpath, mode);
    }

    ~File()
    {
        file.close();
    }

    std::string read()
    {
        std::string str;
        if(file.is_open())
        {
            for(std::string line; std::getline(file, line) ; )
            {
                str += line;
            }
        }
        else
        {
            std::cerr << "try to read on closed file, exiting, you're fucking noob" << std::endl;
            exit(42);
        }
        return str;
    }

    std::vector<std::string> readLines()
    {
        std::vector<std::string> lines;
        if(file.is_open())
        {
            for(std::string line; std::getline(file, line) ; )
            {
                lines.push_back(line);
            }
        }
        else
        {
            std::cerr << "try to read on closed file, exiting, you're fucking noob" << std::endl;
            exit(42);
        }
        return lines;
    }

    template<typename type>
    void write(type line)
    {
        if(file.is_open())
            file << line;
        else
        {
            std::cerr << "try to write on closed file, exiting, you're fucking noob!" << std::endl;
            exit(42);
        }
    }

    template<typename type>
    void write(std::vector<type> lines)
    {
        if(file.is_open())
        {
            for(auto &line : lines)
                file << line << "\n";
        }
        else
        {
            std::cerr << "try to write on closed file, exiting, you're fucking noob!" << std::endl;
            exit(42);
        }
    }

    void close()
    {
        file.close();
    }

    void reload()
    {
        file.close();
        mode = std::ofstream::in | std::ofstream::out | std::ofstream::app;
        file.open(fpath, mode);
    }

    void clear()
    {
        file.close();
        mode = std::ofstream::in | std::ofstream::out | std::ofstream::trunc;
        file.open(fpath, mode);
    }
private:
    std::fstream file;
    std::string fpath;
    std::ofstream::openmode mode;
};


}
#endif // FILE_H
