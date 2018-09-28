#include <libprout.h>
#include <iostream>

using namespace std;

void testChrono();

int main()
{
    cout << "--- Testing Timestamp... ---" << endl;
    cout << prout::getTimeStamp() << endl;

    cout << "\n--- Testing UUID... ---" << endl;
    cout << prout::getUUID() << endl;

    cout << "\n--- Testing listDirs... ---" << endl;
    for(auto dir : prout::listDirs("/tmp"))
    {
        cout << dir << endl;
    }

    cout << "\n--- Testing listFiles... ---" << endl;
    for(auto file : prout::listFiles("/tmp"))
    {
        cout << file << endl;
    }

    cout << "\n--- Testing making folder... ---" << endl;
    prout::makeFolder("testFolder");

    cout << "\n--- Testing print function... ---" << endl;
    prout::print("bite", 255, 'g');


    cout << "\n\n--- Testing chrono function... ---" << endl;
    testChrono();

    return 0;
}
