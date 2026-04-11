#pragma once
#include <algorithm>

template <typename T>
class DynamicArray
{
public:
    DynamicArray();
    DynamicArray(size_t cap);
    ~DynamicArray();

    T *getCollection() { return collection; }
    size_t &getSize() { return size; }
    size_t &getCapacity() { return capacity; }

    void upsize_();
    bool needsToUpsize() { return this->size + 1 >= this->capacity; }

    void insert(size_t position, T val);
    void push_back(T val);
    void push_forward(T val);

    void remove(size_t position);
    void pop_back();
    void pop_front();

    bool search(T e);

private:
    T *collection;   // tablica
    size_t capacity; // rozmiar tablicy
    size_t size;     // ilość elementów w tablicy
};

template <typename T>
DynamicArray<T>::DynamicArray() : capacity(4), size(0)
{
    collection = new T[capacity];
}

template <typename T>
DynamicArray<T>::DynamicArray(size_t cap) : capacity(cap), size(0)
{
    collection = new T[capacity];
}

template <typename T>
DynamicArray<T>::~DynamicArray()
{
    delete[] collection;
}

template <typename T>
void DynamicArray<T>::upsize_()
{
    size_t new_capacity = capacity * 2;
    T *new_collection = new T[new_capacity];
    std::move(collection, collection + size, new_collection);
    delete[] collection;
    collection = new_collection;
    capacity = new_capacity;
}

template <typename T>
void DynamicArray<T>::insert(size_t position, T val)
{
    if (needsToUpsize())
    {
        upsize_();
    }
    std::move(collection + position, collection + size, collection + position + 1);
    collection[position] = val;
    size++;
}

template <typename T>
void DynamicArray<T>::push_forward(T val)
{
    if (needsToUpsize())
    {
        upsize_();
    }
    std::move(collection, collection + size, collection + 1);
    collection[0] = val;
    size++;
}

template <typename T>
void DynamicArray<T>::push_back(T val)
{
    if (needsToUpsize())
    {
        upsize_();
    }
    collection[size] = val;
    size++;
}

template <typename T>
void DynamicArray<T>::remove(size_t position)
{
    std::move(collection + position + 1, collection + size, collection + position);
    size--;
}

template <typename T>
void DynamicArray<T>::pop_back()
{
    size--;
}

template <typename T>
void DynamicArray<T>::pop_front()
{
    std::move(collection + 1, collection + size, collection);
    size--;
}

template <typename T>
bool DynamicArray<T>::search(T e)
{
    for (size_t i = 0; i < size; i++)
    {
        if (collection[i] == e)
            return true;
    }
    return false;
}