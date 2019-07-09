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
#include <experimental/filesystem>

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


namespace prout
{


template <class ... Args>
void print(Args &&... args)
{
    print_(std::forward<Args>(args)...);
    std::cout << std::endl;
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
    for (auto & p : std::experimental::filesystem::directory_iterator(pathName))
    {
        if(std::experimental::filesystem::is_directory(p))
        {
            std::experimental::filesystem::path path = p.path();
            v.push_back(path.u8string());
        }
    }
    return v;
}

static std::vector<std::string> listFiles(const std::string& pathName)
{
    std::vector<std::string> v;
    for (auto & p : std::experimental::filesystem::directory_iterator(pathName))
    {
        if(std::experimental::filesystem::is_regular_file(p))
        {
            std::experimental::filesystem::path path = p.path();
            v.push_back(path.u8string());
        }
    }
    return v;
}


static void makeFolder(const std::string& folder)
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

static std::string replace(const std::string& str, const std::string& from, const std::string& to) {
    std::string out = str;
    size_t start_pos = 0;
    while((start_pos = out.find(from, start_pos)) != std::string::npos) {
        out.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return out;
}

static std::vector<std::string> split(const std::string &str, const std::string delimiter)
{
    std::string out = str;
    size_t pos = 0;
    std::string token;
    std::vector<std::string> result;
    while ((pos = out.find(delimiter)) != std::string::npos) {
        token = out.substr(0, pos);
        if(token != "")
            result.push_back(token);
        out.erase(0, pos + delimiter.length());
    }
    result.push_back(out);
    return result;
}


}

#endif // UTILS_H
