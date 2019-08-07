#include <stdio.h>
#include <dirent.h>
#include <string>
#include <vector>
using namespace std;

int main(int argsnum, char **args) {
    DIR * dp = opendir(args[1]);
    if (dp == nullptr) {
        perror(args[0]);
        return 0;
    }
    struct dirent * fileinfo = nullptr;
    vector<struct dirent*> fileinfos;
    while ((fileinfo = readdir(dp)) != nullptr) {
        fileinfos.push_back(fileinfo);
    }
    for (int i  = 0; i < fileinfos.size(); ++i) {
        printf("%s%c", fileinfos[i]->d_name, i == fileinfos.size() - 1 ? '\n' : ' ');
    }
    return 0;
}