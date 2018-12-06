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

struct listNode{
    int data;
    listNode *next;
};

listNode *hashTable[SIZE];

void insert(int x, int index, listNode* hashTable[]){
    if(hashTable[index]==NULL){
        listNode *newNode = new listNode;
        newNode->data=x;
        newNode->next= NULL;
        hashTable[index]=newNode;
    }
    else{
        listNode *newNode=new listNode;
        newNode->data=x;
        newNode->next= hashTable[index];
        hashTable[index]=newNode;
    }
}

void findCollision(listNode* hashTable[], int origFile, int i, int *grid[]){
    int col1=hashTable[i]->data;
    listNode *temp=hashTable[i]->next;
    int col2=temp->data;
    grid[col1][col2]+=1;
    if(hashTable[i]->next==NULL){
        return;
    }
    findCollision(hashTable, col1, i, grid );
}

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

unsigned long hashFunction(string & s) {
    unsigned long index = 0;
    for (int i = 0; i < s.size(); i++) {
        index = index + unsigned(long(s[i] * pow(7, double(i))));
    }
    return index % SIZE;
}

int main()
{
    string dir = "sm_doc_set";
    vector<string> files = vector<string>();
    getdir(dir,files);
 //   list<int> *hashTable;
 // hashTable = new list<int>[SIZE];
    deque<string> buffer;
    string s;
    string combine;
    long hashIndex;
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
            insert(i, hashIndex, hashTable );
            buffer.pop_front();
            inFile >> s;
            buffer.push_back(s);
            combine = "";
        }
    }

    for(int i =0; i < SIZE; i++){
        if (hashTable[i]->data==i){
            int col1=hashTable[i]->data;
            while(hashTable[i]->next!=NULL){
                findCollision(hashTable, col1, i, &grid);

            }

        }
    }
    return 0;
}

//are we allocating space every time we place a node in the linked list
//array of pointers to structs


/*int main()
{
    //string dir= string(argv[1]);
    string dir = "sm_doc_set";
    vector<string> files = vector<string>();
    int n=6;

    getdir(dir,files);

    for (unsigned int i = 0;i < files.size();i++) {
        cout << i << " " << files[i] << endl;
    }

    ifstream inFile;
    deque <string> readNWords;
    string nWords;
    //int idx=0;
    for(int i=2; i<files.size(); i++){
        string curfile=dir;
        curfile += '/' + files[i];
        cout << curfile << endl;
        inFile.open(curfile.c_str());
        for(int j=0; j<n; j++){
            inFile >> nWords;
            readNWords.push_back(nWords);
        }
     }
    return 0;
}*/

