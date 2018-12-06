#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <fstream>
#include <deque>
#include <list>
#include <math.h>
#define SIZE 1000001
using namespace std;

/*function... might want it in some class?*/
int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

int hashFunction(string & s){
    int index = 0;
    for(int i = 1; i <= s.size();i++){
        index = int(index + s[i] * pow(17,i));
    }
    return index;
}

int main()
{
    string dir = "sm_doc_set";
    vector<string> files = vector<string>();
    getdir(dir,files);
    list<int> *hashTable;
    hashTable = new list<int>[SIZE];
    deque<string> buffer;
    string s;
    string combine;
    int hashIndex;
    int grid[files.size()][files.size()];
    for(int i =2; i < files.size(); i++){
        for(int j =0; i < files.size(); j++){
            grid[i][j] = 0;
        }
    }
    for(int i = 2 ; i < files.size(); i++) {
        string filedir = dir + '/' + files[i];
        ifstream inFile;
        inFile.open(filedir.c_str());
        for (unsigned int i = 2; i < files.size(); i++) {
            cout << files[i] << endl;
        }
        for (int i = 0; i < 6; i++) {
            inFile >> s;
            buffer.push_back(s);
        }
        while (inFile) {
            for (deque<string>::iterator it = buffer.begin(); it != buffer.end(); it++) {
                combine += *it;
            }
            hashIndex = hashFunction(combine);
            hashTable[hashIndex].push_back(i);
            buffer.pop_front();
            inFile >> s;
            buffer.push_back(s);
            combine = "";
        }
    }

    for(int i =0; i < files.size(); i++){

    }
    return 0;
}
