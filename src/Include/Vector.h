#pragma once
#include <iostream>
#include <algorithm>
#include <stdexcept>

template <typename T>
class Vector {
private:
    T* array;
    int capacity;
    int size;

    void ensureCapacity(int minCap) {
        if (minCap <= capacity) return;
        int newCap = capacity ? capacity * 2 : 1;
        while (newCap < minCap) newCap *= 2;
        T* newArr = new T[newCap];
        for (int i = 0; i < size; ++i) newArr[i] = array[i];
        delete[] array;
        array = newArr;
        capacity = newCap;
    }

public:
    Vector() : array(nullptr), capacity(0), size(0) {}
    Vector(int n) : array(new T[n]), capacity(n), size(n) {
        for (int i = 0; i < n; ++i) array[i] = T();
    }
    Vector(int n, const T& val) : array(new T[n]), capacity(n), size(n) {
        for (int i = 0; i < n; ++i) array[i] = val;
    }

    // Copy constructor
    Vector(const Vector& other) : array(new T[other.capacity]), capacity(other.capacity), size(other.size) {
        for (int i = 0; i < size; ++i) array[i] = other.array[i];
    }

    // Move constructor
    Vector(Vector&& other) noexcept : array(other.array), capacity(other.capacity), size(other.size) {
        other.array = nullptr;
        other.capacity = 0;
        other.size = 0;
    }

    // Destructor
    ~Vector() { delete[] array; }

    // Assignment operators
    Vector& operator=(const Vector& other) {
        if (this == &other) return *this;
        delete[] array;
        capacity = other.capacity;
        size = other.size;
        array = new T[capacity];
        for (int i = 0; i < size; ++i) array[i] = other.array[i];
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this == &other) return *this;
        delete[] array;
        array = other.array;
        size = other.size;
        capacity = other.capacity;
        other.array = nullptr;
        other.size = 0;
        other.capacity = 0;
        return *this;
    }

    // Accessors
    int get_size() const { return size; }
    int get_capacity() const { return capacity; }
    bool empty() const { return size == 0; }

    T& operator[](int index) {
        if (index < 0 || index >= size) throw std::out_of_range("Index out of range");
        return array[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= size) throw std::out_of_range("Index out of range");
        return array[index];
    }

    // Add / remove
    void push_back(const T& value) {
        ensureCapacity(size + 1);
        array[size++] = value;
    }

    void pop_back() { if (size > 0) --size; }

    void clear() { size = 0; }

    T* begin() { return array; }
    T* end() { return array + size; }
    const T* begin() const { return array; }
    const T* end() const { return array + size; }

    T& front() { if (empty()) throw std::out_of_range("Vector empty"); return array[0]; }
    T& back() { if (empty()) throw std::out_of_range("Vector empty"); return array[size - 1]; }
    const T& front() const { if (empty()) throw std::out_of_range("Vector empty"); return array[0]; }
    const T& back() const { if (empty()) throw std::out_of_range("Vector empty"); return array[size - 1]; }

    // Remove / erase
    void erase(int index) {
        if (index < 0 || index >= size) return;
        for (int i = index; i < size - 1; ++i) array[i] = array[i + 1];
        --size;
    }

    T* erase(T* pos) {
        if (pos < array || pos >= array + size) return end();
        int idx = static_cast<int>(pos - array);
        erase(idx);
        return array + idx;
    }

    T* insert(T* pos, const T& val) {
        if (pos < array || pos > array + size) return end();
        int idx = static_cast<int>(pos - array);
        ensureCapacity(size + 1);
        for (int i = size; i > idx; --i) array[i] = array[i - 1];
        array[idx] = val;
        ++size;
        return array + idx;
    }

    bool remove(const T& val) {
        for (int i = 0; i < size; ++i) {
            if (array[i] == val) { erase(i); return true; }
        }
        return false;
    }

    bool operator==(const Vector& other) const {
        if (size != other.size) return false;
        for (int i = 0; i < size; ++i)
            if (!(array[i] == other.array[i])) return false;
        return true;
    }
};
