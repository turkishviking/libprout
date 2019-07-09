//
// Created by arnoulr on 26/09/18.
//

#ifndef PROJECT_THREADPOOL_H
#define PROJECT_THREADPOOL_H


#include <thread>
#include <vector>
#include <functional>
#include <mutex>
#include <queue>

namespace prout {

    template<class R, class ...A>
    class ThreadPool {

    public:
        ThreadPool(std::function<R(A...)> function)
                : _function(function) {
            for (int i = 0; i < 3; ++i) {
                _threadPool.push_back(std::thread(&ThreadPool::infiniteLoop, this));
            }
        }

        ~ThreadPool() {
            if (_stayAlive)
                waitUntilFinished();
        }

        void pushObject(A &&... obj) {
            _inputMutex.lock();
            _objectsToProcess.push(std::make_tuple(obj...));
            _inputMutex.unlock();
        }

        std::optional<R> retrieveObject() {
            if (!_objectsProcessed.empty()) {
                _outputMutex.lock();
                R result = _objectsProcessed.front();
                _objectsProcessed.pop();
                _outputMutex.unlock();
                return std::optional<R>(result);
            }
            return std::nullopt;
        }

        void waitUntilFinished() {
            _stayAliveMutex.lock();
            _stayAlive = false;
            _stayAliveMutex.unlock();
            for (auto &thread : _threadPool) {
                if (thread.joinable())
                    thread.join();
            }
        }

    private:
        void infiniteLoop() {
            bool loop = true;
            while (loop) {
                _inputMutex.lock();
                if (!_objectsToProcess.empty()) {
                    // Retrieving objects from the vector
                    std::tuple<A...> objectsTuple = _objectsToProcess.front();
                    _objectsToProcess.pop();
                    _inputMutex.unlock();
                    // Executing the function with the retrieved objects
                    R result = functionImplementation(objectsTuple, std::index_sequence_for<A...>{});
                    // Push the result of the function
                    _outputMutex.lock();
                    _objectsProcessed.push(result);
                    _outputMutex.unlock();
                } else
                    _inputMutex.unlock();
                _stayAliveMutex.lock();
                loop = _stayAlive;
                _stayAliveMutex.unlock();
            }
        }

        template<class Tuple, size_t... Indexes>
        R functionImplementation(Tuple &&tuple, std::index_sequence<Indexes...>) {
            return _function(std::get<Indexes>(tuple)...);
        }

    private:
        std::function<R(A...)> _function;
        std::vector<std::thread> _threadPool;
        std::queue<std::tuple<A...>> _objectsToProcess;
        std::queue<R> _objectsProcessed;
        std::mutex _inputMutex;
        std::mutex _outputMutex;
        std::mutex _stayAliveMutex;
        bool _stayAlive = true;
    };

}

#endif //PROJECT_THREADPOOL_H
