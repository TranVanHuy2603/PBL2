#include <vector>
#include <functional>
#include <algorithm>
#pragma once

using namespace std;

/*template giup viet ham mot lan nhung co the dung cho nhieu kieu du lieu khac nhau*/

template <typename T, typename Compare = less<T> /*Ham so sanh mat dinh*/ >
class Priorityqueue 
{
private:
    vector<T> heap;
    Compare comp;
    void heapify_up(int);//day phan thu moi len dnung vi tri
    void minheapify(int);//tao lai heap

public:
    void push(const T& value);
    void pop();
    T& top();
    bool isEmpty() const;
    vector<T>& getHeap(); //tra ve heap
};


template <typename T, typename Compare>
void Priorityqueue<T, Compare>::heapify_up(int index) 
{
    if (index == 0) return;
    int parent = (index - 1) / 2;
    if (comp(heap[index], heap[parent])) 
    {
        swap(heap[index], heap[parent]);
        heapify_up(parent);
    }
}

template <typename T, typename Compare>
void Priorityqueue<T, Compare>::minheapify(int index) 
{
    int l = 2 * index + 1;
    int r = 2 * index + 2;
    int smallest = index;
    if (l < heap.size() && comp(heap[l], heap[smallest])) smallest = l;
    if (r < heap.size() && comp(heap[r], heap[smallest])) smallest = r;
    if (smallest != index) 
    {
        swap(heap[index], heap[smallest]);
        minheapify(smallest);
    }
}

template <typename T, typename Compare>
void Priorityqueue<T, Compare>::push(const T& value) 
{
    heap.push_back(value);
    heapify_up(heap.size() - 1);
}

template <typename T, typename Compare>
void Priorityqueue<T, Compare>::pop() 
{
    if (heap.empty()) return;
    swap(heap.front(), heap.back());
    heap.pop_back();
    if (!heap.empty()) minheapify(0);
}

template <typename T, typename Compare>
T& Priorityqueue<T, Compare>::top() 
{
    return heap.front();
}

template <typename T, typename Compare>
bool Priorityqueue<T, Compare>::isEmpty() const 
{
    return heap.empty();
}

template <typename T, typename Compare>
vector<T>& Priorityqueue<T, Compare>::getHeap() 
{
    return heap;
}
