#pragma once
#include <iostream>
#include <algorithm>

template <typename T>
class Vector
{
private:
    T *array;
    int capacity;
    int size;
    void resize(int);

public:
    // ====== Constructors ========
    Vector();
    Vector(int , const T&);

    // ====== Destructors ========
    ~Vector();

    // ===== Cac ham chuc nang ======
    void resize(int , const T&);
    void push_back(const T&);
    void pop_back();
    void erase(int);
    T *erase(T *pos);
    T *insert(T *pos, const T &val);
    void clear();
    void reverse();
    bool remove(const T &);
    int get_size() const;
    int get_capacity() const;
    bool empty() const;
    int size() const;

    // ===== Operators overload ======
    T &operator[](int);
    Vector& operator=(const Vector &other);

    // ===== Truy suat, set phan tu dau va cuoi Vector =====
    T *begin();
    T *end();
    const T *begin() const;
    const T *end() const;
};


