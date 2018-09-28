//
// Created by arnoulr on 27/09/18.
//

#include <mutex>
#include "utils/Chrono.h"

std::mutex chronoMutex;

prout::Chrono *prout::Chrono::_instance = nullptr;

prout::Chrono *prout::Chrono::get() {
    std::lock_guard<std::mutex> lock(chronoMutex);
    if (_instance == nullptr)
        _instance = new Chrono();
    return _instance;
}

prout::Chrono::Chrono() {}

void prout::Chrono::startChrono(const std::string &chronoName) {
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

void prout::Chrono::stopChrono(const std::string &chronoName) {
    std::lock_guard<std::mutex> lock(chronoMutex);
    if (_chronoMap.find(chronoName) != _chronoMap.end()) {
        _chronoMap.at(chronoName).stopTime = std::chrono::steady_clock::now();
    }
}

void prout::Chrono::printChrono(const std::string &chronoName) {
    std::lock_guard<std::mutex> lock(chronoMutex);
    if (_chronoMap.find(chronoName) != _chronoMap.end()) {
        auto diff = _chronoMap.at(chronoName).stopTime - _chronoMap.at(chronoName).startTime;
        std::cout << "Chrono \"" << chronoName << "\" : " << std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;
    }
}