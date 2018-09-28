//
// Created by arnoulr on 28/09/18.
//

#include <libprout.h>
#include <unistd.h>

void testChrono()
{
    std::cout << "Launching Chrono for \"Test 1\"" << std::endl;
    prout::Chrono::get()->startChrono("Test 1");
    std::cout << "Sleeping 1s" << std::endl;
    sleep(1);
    std::cout << "Stopping Chrono for \"Test 1\"" << std::endl;
    prout::Chrono::get()->stopChrono("Test 1");
    prout::Chrono::get()->printChrono("Test 1");
}