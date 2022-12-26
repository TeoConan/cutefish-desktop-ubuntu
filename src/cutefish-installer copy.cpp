#include <iostream>
#include <string.h>

#define str_max 255
#define action_install "install"
#define action_install_dependencies "install-dependencies"
#define action_build "build"
#define action_clean "clean"
#define action_help "help"

using namespace std;

int getActionId(char* action);
void mainInstall();
void mainInstallDependencies();
void mainBuild();
void mainHelp();
void mainClean();

int main(int argc, char **argv)
{
    char* action = "install";

    if (argc > 1)
    {
        action = argv[1];
    }

    switch(getActionId(action))
    {
        case 1:
            mainInstall();
            return 0;

        case 2:
            mainInstallDependencies();
            return 0;
        
        case 3:
            mainBuild();
            return 0;

        case 4:
            mainClean();
            return 0;

        case 5:
            mainHelp();
            return 0;
    }

    cout << "Default action : " << action << endl;
}

int getActionId(char* action) {
    if(strcmp(action, action_install) == 0)
    {
        return 1;
    }

    if(strcmp(action, action_install_dependencies) == 0)
    {
        return 2;
    }

    if(strcmp(action, action_build) == 0)
    {
        return 3;
    }

    if(strcmp(action, action_clean) == 0)
    {
        return 4;
    }

    if(strcmp(action, action_help) == 0)
    {
        return 5;
    }

    return 0;
}

void mainInstall()
{
    cout << "Installing dependencies..." << endl;
}

void mainClean()
{
    cout << "Cleaning..." << endl;
}