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
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "string.h"
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

struct collisionset{
    int data;
    int idx1;
    int idx2;
};

listNode * hashTable[SIZE];

void insert(int x, unsigned long index, listNode* hashTable[]);


int main(int argc, char* argv[])
{
    int n=atoi(argv[2]);
    string dir= string(argv[1]);
    //string dir = "sm_doc_set";
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
        for (int j = 0; j < n; j++) {
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
            listNode *temp;
            while(p1!=NULL){
                p2 = p1->next;
                while(p2!=NULL){
                    if(p1->data != p2->data) {
                        grid[p1->data][p2->data]++;
                    }
                    p2 = p2->next;
                }
                temp=p1;
                p1 = p1->next;
                delete temp;
            }
        }
    }

    collisionset array[files.size()];
    int k=0;
    for(int i =2; i < files.size();i++){
        for(int j = 0; j < files.size();j++){
            if(grid[i][j] > 200) {
                collisionset set;
                set.data=grid[i][j];
                set.idx1=i;
                set.idx2=j;
                array[k]=set;
                k++;
            }
        }
    }

    for(int i=0; i<k; i++){
        int j=i+1;
        while(j<k) {
            if (array[i].data<array[j].data){
                collisionset temp1=array[i];
                collisionset temp2=array[j];
                array[i]=temp2;
                array[j]=temp1;
            }
            j++;
        }
    }

    for(int i=0; i<k; i++){
        cout << array[i].data << ":" << files[array[i].idx1]  << "," << files[array[i].idx2] << endl;
    }
    
    return 0;
}

void insert(int x, unsigned long index, listNode* hashTable[]){
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

