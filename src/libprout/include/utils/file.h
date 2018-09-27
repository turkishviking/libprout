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
private:
    std::fstream file;
};


}
#endif // FILE_H
