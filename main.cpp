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
#define SIZE 1000001//500001
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

unsigned long hashFunction(string & s){
    unsigned long index = 0;
    for(int i = 0; i < s.size();i++){
        index = index + unsigned (long(s[i] * pow(7.0,double(i))));
    }
    return index % SIZE;
}

struct listNode{
    int data;
    listNode *next;
};
listNode * hashTable[SIZE];
void insert(int x, int index, listNode* hashTable[]);
int main()
{
    string dir = "sm_doc_set";
    vector<string> files = vector<string>();
    getdir(dir,files);
    for(int i =0; i < SIZE; i++){
        hashTable[i] = NULL;
    }
    //hashTable = new list<int>[SIZE];
    string s;
    string combine;
    unsigned long hashIndex;
    int test = files.size();
    for (unsigned int i = 2; i < files.size(); i++) {
        cout << files[i] << endl;
    }
    int grid[files.size()][files.size()];
    for(int i =2; i < files.size(); i++){
        for(int j =0; j < files.size(); j++){
            grid[i][j] = 0;
        }
    }
    for(int i = 2 ; i < files.size(); i++) {
        string filedir = dir + '/' + files[i]; //change to i
        ifstream inFile;
        inFile.open(filedir.c_str());
        deque<string> buffer;
        for (int i = 0; i < 6; i++) {
            inFile >> s;
            buffer.push_back(s);
        }
        while (inFile) {
            for (deque<string>::iterator it = buffer.begin(); it != buffer.end(); it++) {
                combine += *it;
            }
            hashIndex = hashFunction(combine);
            insert(i,hashIndex,hashTable); // change to i
            //hashTable[hashIndex].push_back(2); //change to i
            buffer.pop_front();
            inFile >> s;
            buffer.push_back(s);
            combine = "";
        }
    }

    for(int i =0; i < SIZE; i++){
        if(hashTable[i] != NULL){
            listNode * p1 = hashTable[i];
            listNode * p2;
            while(p1!=NULL){
                p2 = p1->next;
                while(p2!=NULL){
                    if(p1->data != p2->data) {
                        grid[p1->data][p2->data]++;
                    }
                    p2 = p2->next;
                }
                p1 = p1->next;
            }
        }
    }
    for(int i =2; i < files.size();i++){
        for(int j = 0; j < files.size();j++){
            if(grid[i][j] > 200) {
                cout << grid[i][j] << ":" << files[i]  << "," << files[j] << endl;
            }
        }
    }
    return 0;
}

void insert(int x, int index, listNode* hashTable[]){
    if (hashTable[index] == NULL){
        listNode *newNode = new listNode;
        newNode->data = x;
        newNode->next = NULL;
        hashTable[index] = newNode;
    }
    else{
        listNode *newNode = new listNode;
        newNode->data = x;
        newNode->next = hashTable[index];
        hashTable[index] = newNode;
    }
}


