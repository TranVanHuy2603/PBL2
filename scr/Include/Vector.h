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
    Vector();
    ~Vector();
    void push_back(const T &);
    void pop_back();
    void erase(int);
    T* erase(T* pos);                 
    T* insert(T* pos, const T &val);
    void clear();
    void reverse();
    bool remove(const T&);
    int get_size() const;
    int get_capacity() const;
    T &operator[](int);
    Vector& operator=(const Vector& other);
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
Vector<T>::~Vector()
{
    delete[] array;
}

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
T* Vector<T>::erase(T* pos)
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
T* Vector<T>::insert(T* pos, const T &val)
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
T &Vector<T>::operator[](int index)
{
    if (index < 0 || index >= size)
    {
        static T error{};
        return error;
    }
    else
        return array[index];
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    if (this == &other) return *this; 
    delete[] array; 
    capacity = other.capacity;
    size = other.size;
    array = new T[capacity];
    for (int i = 0; i < size; i++) {
        array[i] = other.array[i];
    }
    return *this;
}

template <typename T>
T *Vector<T>::begin() { return array; }

template <typename T>
T *Vector<T>::end() { return array + size; }

template <typename T>
const T *Vector<T>::begin() const { return array; }

template <typename T>
const T *Vector<T>::end() const { return array + size; }
