#include "HashMap.h"
#include <iostream>

HashMap::HashMap() {
    for (int i = 0; i < SIZE; i++)
        table[i] = nullptr;
}

HashMap::~HashMap() {
    for (int i = 0; i < SIZE; i++) {
        HashNode* curr = table[i];
        while (curr) {
            HashNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }
}

int HashMap::hash(const std::string& key) {
    int sum = 0;
    for (char c : key) sum += c;
    return sum % SIZE;
}

void HashMap::insert(const std::string& key, int value) {
    int idx = hash(key);
    HashNode* curr = table[idx];
    while (curr) {
        if (curr->key == key) {
            curr->value = value; 
            return;
        }
        curr = curr->next;
    }

    HashNode* node = new HashNode{key, value, table[idx]};
    table[idx] = node;
}

int HashMap::get(const string& key) {
    int idx = hash(key);
    HashNode* curr = table[idx];
    while (curr) {
        if (curr->key == key) return curr->value;
        curr = curr->next;
    }
    return -1;
}

bool HashMap::remove(const std::string& key) {
    int idx = hash(key);
    HashNode* curr = table[idx];
    HashNode* prev = nullptr;
    while (curr) {
        if (curr->key == key) {
            if (prev) prev->next = curr->next;
            else table[idx] = curr->next;
            delete curr;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false; 
}

