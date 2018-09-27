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

static std::vector<std::string> listDirs(const std::string& dir)
{
    std::vector<std::string> files;
    std::shared_ptr<DIR> directory_ptr(opendir(dir.c_str()), [](DIR* dir){ dir && closedir(dir); });
    struct dirent *dirent_ptr;
    if (!directory_ptr)
    {
        std::cout << "Error opening : " << std::strerror(errno) << dir << std::endl;
        return files;
    }

    while ((dirent_ptr = readdir(directory_ptr.get())) != nullptr)
    {
        if( strcmp(dirent_ptr->d_name , ".") != 0 && strcmp(dirent_ptr->d_name , "..") != 0 )
            files.push_back(std::string(dirent_ptr->d_name));
    }
    return files;
}

static std::vector<std::string> listFiles(const std::string& name)
{
    std::vector<std::string> v;
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        if( strcmp(dp->d_name , ".") != 0 && strcmp(dp->d_name , "..") != 0 )
            v.push_back(dp->d_name);
    }
    closedir(dirp);

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





}

#endif // UTILS_H
