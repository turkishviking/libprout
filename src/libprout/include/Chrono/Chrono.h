//
// Created by arnoulr on 27/09/18.
//

#ifndef LIBPROUT_CHRONO_H
#define LIBPROUT_CHRONO_H

#include <utils/prout_utils.h>
#include <unordered_map>

namespace prout {

    struct chronoInfo {
        std::chrono::time_point<std::chrono::steady_clock,
        std::chrono::duration<long, std::ratio<1, 1000000000>>>  startTime;
        std::chrono::time_point<std::chrono::steady_clock,
        std::chrono::duration<long, std::ratio<1, 1000000000>>> stopTime;
    };

    class Chrono {

    private:
        static Chrono* _instance;

    public:
        static Chrono* get();

    private:
        Chrono();
        Chrono(const Chrono &) = delete;
        Chrono operator=(const Chrono &) = delete;

    public:
        void startChrono(const std::string &chronoName);
        void stopChrono(const std::string &chronoName);
        void printChrono(const std::string &chronoName);

    private:
        std::unordered_map<std::string, chronoInfo> _chronoMap;
    };

}

#endif //LIBPROUT_CHRONO_H
