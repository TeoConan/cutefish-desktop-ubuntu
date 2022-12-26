#include <string>
using std::string;

void install();
void installDependencies();
void clean();
void build();
void projects();
void clone();
void installProjects();
bool askYesNo();
bool caseInsensitiveStringCompare(const string& str1, const string& str2);
string convertToString(string* a, int size, char* delimiter);
bool isRoot();