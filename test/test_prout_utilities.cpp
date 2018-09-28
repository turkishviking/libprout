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

    cout << "\n--- Testing replace function... ---" << endl;
    cout << "caca " << prout::replace("caca", "a", "ul") << endl;;

    cout << "\n--- Testing split string function... ---" << endl;
    cout << "pirs__sucks_ducks:" << endl;
    for(auto &words : prout::split("pirs__sucks_ducks", "_"))
        cout << words << endl;

    cout << "\n--- Testing file functions... ---" << endl;
    std::string path = "/tmp/test_prout";
    prout::File f(path, "w");
    cout << "writing caca in " << path << endl;
    f.write("caca");
    f.reload();
    cout << "reading " << path << endl;
    cout << f.read() << endl;
    f.close();

    prout::File f2(path, "w");
    cout << "writing list of 10 caca in " << path << endl;
    std::vector<std::string> caca;
    for(size_t i=0;i<10;i++)
    {
        f2.write("caca\n");
        caca.push_back("caca");
    }
    f2.reload();

    cout << "reading list of 10 caca in" << path << endl;
    for(auto line : f2.readLines())
        cout << line << endl;;
    f2.close();

    cout << "writing list of 10 caca as vector in " << path << endl;
    prout::File f3(path, "w");
    f3.write(caca);
    f3.reload();

    cout << "reading list of 10 caca in" << path << endl;
    for(auto line : f3.readLines())
        cout << line << endl;;
    f3.close();


    cout << "\n\n--- Testing chrono function... ---" << endl;
    testChrono();

    return 0;
}
