#pragma once
#include <cstddef>
#include <iostream>

template <typename T>
class DLinkedList;

template <typename T>
class DNode
{
private:
    T elem;         // element w węźle
    DNode<T> *next; // wskaźnik na kolejny węzeł
    DNode<T> *previous; // wskaźnik na poprzedni węzeł
    friend class DLinkedList<T>;
};

template <typename T>
class DLinkedList
{
private:
    DNode<T> *head;
    DNode<T> *tail;
    int length = 0;     // dlugosc struktury
public:
    DLinkedList() : head(nullptr), tail(nullptr) {};
    ~DLinkedList() { while(!empty()) remove_front(); };
    DLinkedList(const DLinkedList& other);
    bool empty() const
    {
        return head == nullptr;
    };
    const T &front() const { return head->elem; } // zwraca element poczatkowy
    const T &back() const { return tail->elem; }  // zwraca element koncowy
    
    void add_front(const T &e);
    void add_back(const T &e);
    void remove_front();
    void remove_back();
    void insert(const T &e, size_t pos);
    void remove(size_t pos);
    int fw_search(const T &e);
    int bw_search(const T &e);
    int search(const T &e, bool backwards);
    void print();
};


template <typename T>
DLinkedList<T>::DLinkedList(const DLinkedList& other) : head(nullptr), tail(nullptr), length(0)
{
    DNode<T>* current = other.head;
    while (current != nullptr) {
        add_back(current->elem);
        current = current->next;
    }
}

template <typename T>
void DLinkedList<T>::add_front(const T &e)
{
    DNode<T>* v = new DNode<T>;
    v->elem = e;
    v->previous = nullptr;
    v->next = head;

    if (head != nullptr) {
        head->previous = v;
    } else {
        tail = v;
    }

    head = v;
    length++;
}

template <typename T>
void DLinkedList<T>::add_back(const T &e)
{
    if (empty())
    {
        DNode<T> *w = new DNode<T>;
        w->elem = e;
        w->next = nullptr;
        w->previous = nullptr;
        tail = head = w;
        return;
    }
    DNode<T> *v = new DNode<T>;
    v->elem = e;
    v->next = nullptr;
    v->previous = tail;
    tail->next = v;
    tail = v;
    length++;
}

template <typename T>
void DLinkedList<T>::remove_front()
{
    if (empty())
        return;
    DNode<T> *old = head;
    head = old->next;
    if (head == nullptr)
        tail = nullptr;
    delete old;
    length--;
}

template <typename T>
void DLinkedList<T>::remove_back()
{
    if (empty())
        return;
    DNode<T> *old = tail;
    tail = old->previous;
    if (tail == nullptr)
        head = nullptr;
    delete old;
    length--;
}

template <typename T>
int DLinkedList<T>::fw_search(const T &e)
{
    int index = 0;
    DNode<T> *indirect = head;
    while (indirect != nullptr)
    {
        if (indirect->elem == e){ return index; }
        indirect = indirect->next;
        index++;
    }
    return -1;
}

template <typename T>
int DLinkedList<T>::bw_search(const T &e)
{
    int index = length;
    DNode<T> *indirect = tail;
    while (indirect != nullptr)
    {
        if (indirect->elem == e){ return index; }
        indirect = indirect->previous;
        index--;
    }
    return -1;
}

template <typename T>
int DLinkedList<T>::search(const T &e, bool backwards)
{
    if(backwards){
        return this->bw_search(e);
    }
    else{
        return this->fw_search(e);
    }
}

template <typename T>
void DLinkedList<T>::insert(const T &e, size_t pos)
{
    if (pos == 0)
    {
        add_front(e);
        return;
    }

    if (pos == length)
    {
        add_back(e);
        return;
    }

    DNode<T>* current;

    if (pos <= length / 2)
    {
        current = head;
        for (size_t i = 0; i < pos - 1; i++)
            current = current->next;
    }
    else
    {
        current = tail;
        for (size_t i = length - 1; i > pos - 1; i--)
            current = current->previous;
    }

    DNode<T>* newNode = new DNode<T>;
    newNode->elem = e;

    DNode<T>* nextNode = current->next;

    newNode->next = nextNode;
    newNode->previous = current;

    current->next = newNode;

    if (nextNode != nullptr)
        nextNode->previous = newNode;

    length++;
}

template <typename T>
void DLinkedList<T>::remove(size_t pos)
{
    if (pos == 0)
    {
        this->remove_front();
        return;
    }
    if (pos == length){
        this->remove_back();
        return;
    }
    DNode<T> *current = head;
    if(pos <= length/2){
        DNode<T> *current = this->head;
        for (int i = 1; i < pos; i++)
        {
            current = current->next;
        }
    }
    else{
        DNode<T> *current = this->tail;
        for (int i = length-1; i > pos; i--)
        {
            current = current->previous;
        }
    }
    DNode<T> *trash = current->next;
    current->next = trash->next;
    delete trash;
}

template <typename T>
void DLinkedList<T>::print()
{
    std::cout << "[";
    DNode<T>* current = this->head;
    while(current != nullptr){
        std::cout << current->elem;
        current = current->next;
        if(current != nullptr){
            std::cout << ", ";
        }
    }
    std::cout << "]\n";
}