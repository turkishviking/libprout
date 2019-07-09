//
// Created by arnoulr on 27/09/18.
//

#ifndef LIBPROUT_CHRONO_H
#define LIBPROUT_CHRONO_H

#include "prout_utils.h"
#include <unordered_map>
#include <mutex>
#include <thread>

namespace prout {

    struct chronoInfo {
        std::chrono::time_point<std::chrono::steady_clock,
        std::chrono::duration<long, std::ratio<1, 1000000000>>>  startTime;
        std::chrono::time_point<std::chrono::steady_clock,
        std::chrono::duration<long, std::ratio<1, 1000000000>>> stopTime;
    };

    class Chrono {

    private:
        static Chrono& instance()
        {
            static Chrono instance;
            return instance;
        }

    public:
        static Chrono& get()
        {
            // Note the constructor of std::once_flag
            // is a constexpr and is thus done at compile time
            // thus it is immune to multithread construction
            // issues as nothing is done at runtime.
            static std::once_flag flag;

            // Make sure all threads apart from one wait
            // until the first call to instance has completed.
            // This guarantees that the object is fully constructed
            // by a single thread.
            std::call_once(flag, [] { instance(); });

            // Now all threads can go get the instance.
            // as it has been constructed.
            return instance();
        }

    private:
        Chrono(){}
        Chrono(const Chrono &) = delete;
        Chrono operator=(const Chrono &) = delete;

    public:
        void startChrono(const std::string &chronoName)
        {
            std::lock_guard<std::mutex> lock(chronoMutex);
            if (_chronoMap.find(chronoName) != _chronoMap.end()) {
                auto a = std::chrono::steady_clock::now();
                _chronoMap.at(chronoName).startTime = std::chrono::steady_clock::now();
            }
            else {
                chronoInfo  info;
                info.startTime = std::chrono::steady_clock::now();
                _chronoMap.insert(std::pair(chronoName, info));
            }
        }
        void stopChrono(const std::string &chronoName)
        {
            std::lock_guard<std::mutex> lock(chronoMutex);
            if (_chronoMap.find(chronoName) != _chronoMap.end()) {
                _chronoMap.at(chronoName).stopTime = std::chrono::steady_clock::now();
            }
        }
        void printChrono(const std::string &chronoName)
        {
            std::lock_guard<std::mutex> lock(chronoMutex);
            if (_chronoMap.find(chronoName) != _chronoMap.end()) {
                auto diff = _chronoMap.at(chronoName).stopTime - _chronoMap.at(chronoName).startTime;
                std::cout << "Chrono \"" << chronoName << "\" : " << std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;
            }
        }

    private:
        std::unordered_map<std::string, chronoInfo> _chronoMap;
        std::mutex chronoMutex;
    };

}

#endif //LIBPROUT_CHRONO_H
