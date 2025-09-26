#pragma once
#include <iostream>
#include <algorithm>
#include "String.h"        
using llu = unsigned long long;

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

    // ===== Operators overload ======
    T &operator[](int);
    const T& operator[](int) const;
    Vector& operator=(const Vector &other);
    bool operator==(const Vector<T>& other) const;

    // ===== Truy suat, set phan tu dau va cuoi Vector =====
    T *begin();
    T *end();
    const T *begin() const;
    const T *end() const;
};

template <typename T>
Vector<T>::Vector()
{
    array = new T[1];
    this->capacity = 1;
    this->size = 0;
}

template <typename T>
Vector<T>::Vector(int n, const T& val) {
    capacity = size = n;
    array = new T[capacity];
    for (int i = 0; i < size; i++) {
        array[i] = val;
    }
}

// ====== Destructors ========
template <typename T>
Vector<T>::~Vector()
{
    delete[] array;
}

// ===== Cac ham chuc nang ======
template <typename T>
void Vector<T>::resize(int newcap)
{
    T *newarr = new T[newcap];
    for (int i = 0; i < size; i++)
    {
        newarr[i] = array[i];
    }
    delete[] array;
    this->array = newarr;
    this->capacity = newcap;
}

template <typename T>
void Vector<T>::resize(int new_size, const T& value) {
    if (new_size <= size) {
        size = new_size; // cắt ngắn lại
        return;
    }

    if (new_size > capacity) {
        int newcap = capacity;
        while (newcap < new_size) newcap *= 2;
        T* newarr = new T[newcap];
        for (int i = 0; i < size; i++) {
            newarr[i] = array[i];
        }
        delete[] array;
        array = newarr;
        capacity = newcap;
    }

    // khởi tạo phần tử mới với giá trị `value`
    for (int i = size; i < new_size; i++) {
        array[i] = value;
    }
    size = new_size;
}

template <typename T>
void Vector<T>::push_back(const T &value)
{
    if (size == capacity)
    {
        resize(capacity * 2);
    }
    array[size++] = value;
}

template <typename T>
void Vector<T>::pop_back()
{
    if (size > 0)
    {
        --size;
    }
}

template <typename T>
int Vector<T>::get_size() const { return size; }

template <typename T>
int Vector<T>::get_capacity() const { return capacity; }

template <typename T>
void Vector<T>::erase(int index)
{
    if (index < 0 || index >= size)
        return;
    for (int i = index; i < size - 1; i++)
    {
        array[i] = array[i + 1];
    }
    --size;
}

template <typename T>
T *Vector<T>::erase(T *pos)
{
    if (pos < array || pos >= array + size)
        return end();

    int index = static_cast<int>(pos - array);
    for (int i = index; i < size - 1; ++i)
    {
        array[i] = array[i + 1];
    }
    --size;
    return array + index;
}

template <typename T>
T *Vector<T>::insert(T *pos, const T &val)
{
    if (pos < array || pos > array + size)
        return end();

    int index = static_cast<int>(pos - array);

    if (size == capacity)
        resize(capacity * 2);

    for (int i = size; i > index; --i)
    {
        array[i] = array[i - 1];
    }
    array[index] = val;
    ++size;

    return array + index;
}

template <typename T>
void Vector<T>::clear()
{
    size = 0;
}

template <typename T>
void Vector<T>::reverse()
{
    for (int i = 0; i < size / 2; i++)
    {
        T temp = array[i];
        array[i] = array[size - i - 1];
        array[size - i - 1] = temp;
    }
}

template <typename T>
bool Vector<T>::remove(const T &value)
{
    for (int i = 0; i < size; i++)
    {
        if (array[i] == value)
        {
            erase(i);
            return true;
        }
    }
    return false;
}

template <typename T>
bool Vector<T>::empty() const
{
    return size == 0;
}

// ===== Operators overload ======
template <typename T>
T &Vector<T>::operator[](int index)
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Index out of range");
    }
    else
        return array[index];
}

template <typename T>
const T& Vector<T>::operator[](int index) const
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Index out of range");
    }
    return array[index];
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &other)
{
    if (this == &other)
        return *this;
    delete[] array;
    capacity = other.capacity;
    size = other.size;
    array = new T[capacity];
    for (int i = 0; i < size; i++)
    {
        array[i] = other.array[i];
    }
    return *this;
}

template <typename T>
bool Vector<T>::operator==(const Vector<T>& other) const {
    if (size != other.size) return false;
    for (int i = 0; i < size; i++)
        if (!(array[i] == other.array[i])) return false;
    return true;
}



// ===== Truy suat, set phan tu dau va cuoi Vector =====
template <typename T>
T* Vector<T>::begin() { return array; }

template <typename T>
T* Vector<T>::end() { return array + size; }

template <typename T>
const T *Vector<T>::begin() const { return array; }

template <typename T>
const T *Vector<T>::end() const { return array + size; }

template class Vector<int>;
template class Vector<String>;
template class Vector<Vector<int>>;