#include "../lib/rang.hpp"
#include "./cutefish-installer.hpp"
#include <iostream>
#include <string>
#include <unistd.h>

using std::string;
using namespace std;
using namespace rang;

bool askYesNo()
{
    string answer;

    cout << "> ";
    cin >> answer;

    if (caseInsensitiveStringCompare(answer, "y") || caseInsensitiveStringCompare(answer, "yes"))
    {
        return true;
    }

    if (caseInsensitiveStringCompare(answer, "n") || caseInsensitiveStringCompare(answer, "no"))
    {
        return false;
    }

    cout << rang::fg::red << "Invalid input" << style::reset << endl;
    cout << "[Y]es [N]o" << endl;
    return askYesNo();
}

bool isRoot()
{
    if (getuid() == 0) {
        cout << rang::fg::green << "Running as root" << style::reset << endl;
        return true;
    } else {
        cout << rang::fg::red << "You must be root to run the installer, aborting" << style::reset << endl;
        exit(0);
        return false;
    }
}

string convertToString(string* a, int size, char* delimiter)
{
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        s = s + delimiter + a[i];
    }
    return s;
}

bool caseInsensitiveStringCompare(const string &str1, const string &str2)
{
    if (str1.size() != str2.size())
    {
        return false;
    }
    for (string::const_iterator c1 = str1.begin(), c2 = str2.begin(); c1 != str1.end(); ++c1, ++c2)
    {
        if (tolower(static_cast<unsigned char>(*c1)) != tolower(static_cast<unsigned char>(*c2)))
        {
            return false;
        }
    }
    return true;
}