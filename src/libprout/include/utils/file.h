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
    File(std::string path, std::string writeMode="a");
    ~File();
    std::string read();
    std::vector<std::string> readLines();
    void write(std::string line);
    void write(std::vector<std::string> lines);
    void close();
    void reload();
private:
    std::fstream file;
    std::string fpath;
    std::ofstream::openmode mode;
};


}
#endif // FILE_H
