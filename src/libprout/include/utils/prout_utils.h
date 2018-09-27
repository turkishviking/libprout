#ifndef UTILS_H
#define UTILS_H
#include <vector>
#include <chrono>
#include <iostream>
#include <dirent.h>
#include <sstream>
#include <algorithm>
#include <memory>
#include <sys/stat.h>
#include <cstring>
#include <filesystem>

namespace prout
{

namespace
{

    template <class T>
    void print_(T &&arg)
    {
      std::cout << arg << ' ';
    }
    template <class T, class ... Args>
    void print_(T && val, Args &&... args)
    {
      print_(std::forward<T>(val));
      print_(std::forward<Args>(args)...);
    }


}

template <class ... Args>
void print(Args &&... args)
{
  print_(std::forward<Args>(args)...);
}

static long getTimeStamp()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::system_clock::now().time_since_epoch()).count();
}

static std::string getUUID()
{
    return std::to_string((std::chrono::duration_cast<std::chrono::nanoseconds>
            (std::chrono::system_clock::now().time_since_epoch()).count()));
}

static std::vector<std::string> listDirs(const std::string& pathName)
{
    std::vector<std::string> v;
    for (auto & p : std::filesystem::directory_iterator(pathName))
    {
        if(p.is_directory())
        {
            std::filesystem::path path = p.path();
            v.push_back(path.u8string());
        }
    }
    return v;
}

static std::vector<std::string> listFiles(const std::string& pathName)
{
    std::vector<std::string> v;
    for (auto & p : std::filesystem::directory_iterator(pathName))
    {
        if(p.is_regular_file())
        {
            std::filesystem::path path = p.path();
            v.push_back(path.u8string());
        }
    }
    return v;
}


static void makeFolder(std::string folder)
{
    if (mkdir(folder.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1)
    {
        if( errno == EEXIST ) {
            // alredy exists
        } else {
            // something else
            std::cout << "cannot create images folder error:" << strerror(errno) << std::endl;
            throw std::runtime_error(strerror(errno));
        }
    }
}

static std::string replace(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}



}

#endif // UTILS_H
