#pragma once
#include "Vector.h"

template <typename T>
class Set {
private:
    Vector<T> data;

public:
    Set();

    bool count(const T &value) const;
    void insert(const T &value);
    void clear();
    int size() const;
};

template <typename T>
Set<T>::Set() {}

template <typename T>
bool Set<T>::count(const T &value) const {
    for (int i = 0; i < data.get_size(); i++) {
        if (data[i] == value)
            return true;
    }
    return false;
}

template <typename T>
void Set<T>::insert(const T &value) {
    if (!count(value))
        data.push_back(value);
}

template <typename T>
void Set<T>::clear() {
    data.clear();
}

template <typename T>
int Set<T>::size() const {
    return data.get_size();
}
