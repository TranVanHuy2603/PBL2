#pragma once
#include <string>

using namespace std;

struct HashNode {
    string key;
    int value;
    HashNode* next;
};

class HashMap {
private:
    static const int SIZE = 100;   
    HashNode* table[SIZE];

    int hash(const string& key); 

public:
    HashMap();
    ~HashMap();

    void insert(const string& key, int value);  
    int get(const string& key);              
    bool remove(const string& key);                                    
};
