#ifndef UTILS_H
#define UTILS_H

#include <chrono>

namespace prout
{


static long getTimeStamp()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::system_clock::now().time_since_epoch()).count();
}





}

#endif // UTILS_H
