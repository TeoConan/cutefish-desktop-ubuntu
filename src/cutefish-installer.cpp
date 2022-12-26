#include "../lib/CLI11.hpp"
#include "../lib/rang.hpp"
#include "./cutefish-installer.hpp"
#include "./utils.cpp"
#include <cstdlib>
#include <cstring>
#include <system_error>

using namespace std;
using namespace rang;

string dependencies[] = {
    "libqapt-dev",
    "libxcb-util0-dev",
    "xserver-xorg-input-libinput-dev",
    "libx11-xcb-dev",
    "libxcb-keysyms1-dev",
    "libxcb-dpms0-dev",
    "libxcb-dri2-0-dev",
    "libxcb-dri3-dev",
    "libxcb-glx0-dev",
    "libxcb-record0-dev",
    "xserver-xorg-dev",
    "xserver-xorg-input-synaptics-dev",
    "libkf5idletime-dev"};

string projectsName[] = {
    "libcutefish",
    "fishui",
    "kwin-plugins",
    "launcher",
    "qt-plugins",
    "wallpapers",
    "dock",
    "filemanager",
    "terminal",
    "settings",
    "statusbar",
    "core",
};

string basePath = "/var/lib/apt";
string gitUrl = "https://github.com/cutefishos/";
bool verbose = false;

int main(int argc, char **argv)
{

    cout << "Welcome in the Cutefish Desktop installer" << endl;
    CLI::App app{"Install easily Cutefish Desktop on your Ubuntu"};

    CLI::App &installCommand = *app.add_subcommand("install", "Install Cutefish Desktop");
    installCommand.callback([&app]()
                            { install(); });

    CLI::App &installDepCommand = *app.add_subcommand("install-dependencies", "Only install apt dependencies");
    installDepCommand.callback([&app]()
                               { installDependencies(); });

    CLI::App &buildCommand = *app.add_subcommand("build", "Build all Cutefish Desktop projects");
    buildCommand.callback([&app]()
                          { build(); });

    CLI::App &cloneCommand = *app.add_subcommand("clone", "Clone all Cutefish Desktop projects");
    cloneCommand.callback([&app]()
                          { clone(); });

    CLI::App &installProjectsCommand = *app.add_subcommand("install-projects", "Only install projects from .deb files");
    installProjectsCommand.callback([&app]()
                          { clone(); });

    CLI::App &cleanCommand = *app.add_subcommand("clean", "Clean temporary files and folders");
    cleanCommand.callback([&app]()
                          { clean(); });

    CLI::App &projectsCommand = *app.add_subcommand("projects", "Show infos about projects");
    projectsCommand.callback([&app]()
                             { projects(); });

    app.add_option("-d, --directory", basePath, "Directory to use to clone, build and install projects");
    app.add_option("-g, --git-url", gitUrl, "Base url to use to clone projects");
    app.add_option("-v,--verbose", verbose, "Print all in console");

    CLI11_PARSE(app, argc, argv);

    cout << endl;
    return 0;
}

void install()
{
    //isRoot();
    cout << "Ready to do a full install of Cutefish, continue ?" << endl;
    //if (!askYesNo())
    //    return;

    //clone();
    installDependencies();
    //build();
    //installProjects();
    //clean();
}

void installDependencies()
{
    isRoot();
    cout << "Installing dependencies..." << endl;
    string dependenciesList = convertToString(dependencies,
        sizeof(dependencies) / sizeof(dependencies[0]), " ");

    cout << rang::fg::cyan << "$ apt install -qq -y " << dependenciesList << style::reset << endl;
    system(("apt-get install -qq -y " + dependenciesList).c_str());
    cout << rang::fg::green << "All dependencies has been installed" << style::reset << endl;
}

void clone()
{
    isRoot();

    cout << "Cloning projects..." << endl;

    int projectsSize = sizeof(projectsName) / sizeof(projectsName[0]);

    system("rm -rf /tmp/cutefish");
    system("mkdir -p /tmp/cutefish/");

    for (int i = 0; i < projectsSize; i++)
    {
        cout << rang::fg::cyan << "Cloning " << projectsName[i] << style::reset << endl;
        system(("git -C /tmp/cutefish/ clone -q " + gitUrl + projectsName[i]).c_str());
    }

    cout << rang::fg::green << "All projects has been cloned" << endl;
}

void installProjects()
{
    isRoot();
    cout << "Installing projects..." << endl;
    cout << rang::fg::blue <<  "Intalling .deb files from " << basePath << style::reset << endl;

    string command = "apt-get -qq install " + basePath + "/*.deb -y";
    system(command.c_str());
}

void build()
{
    cout << "Building projects..." << endl;

    int projectsSize = sizeof(projectsName) / sizeof(projectsName[0]);

    for (int i = 0; i < projectsSize; i++)
    {
        cout << "\bBuilding " << projectsName[i] << endl;
        system(("cd /tmp/cutefish/" + projectsName[i]).c_str());
        system("dpkg-buildpackage -uc -us -b");
        system(("cp /tmp/" + projectsName[i] + "/*.deb " + basePath + "/" + projectsName[i] + ".deb").c_str());
    }
}

void clean()
{
    cout << "Cleaning projects..." << endl;

}

void projects()
{
    cout << "Informations about projects" << endl;
}
