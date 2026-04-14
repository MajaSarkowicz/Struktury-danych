#pragma once
#include <cstddef>
#include <iostream>

template <typename T>
class SLinkedList;

template <typename T>
class SNode
{
private:
    T elem;         // element w węźle
    SNode<T> *next; // wskaźnik na kolejny węzeł
    friend class SLinkedList<T>;
};

template <typename T>
class SLinkedList
{
private:
    SNode<T> *head;
    SNode<T> *tail;
public:
    SLinkedList() : head(nullptr), tail(nullptr) {};
    SLinkedList(const SLinkedList& other);
    ~SLinkedList() { while(!empty()) remove_front(); };
    
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
    int search(const T &e, bool compatibility_flag);
    void print();
};

template <typename T>
SLinkedList<T>::SLinkedList(const SLinkedList& other)
    : head(nullptr), tail(nullptr)
{
    SNode<T>* current = other.head;
    while (current != nullptr) {
        add_back(current->elem);
        current = current->next;
    }
}

template <typename T>
void SLinkedList<T>::add_front(const T &e)
{
    SNode<T> *v = new SNode<T>;
    v->elem = e;
    v->next = head;
    head = v;
    if (head->next == nullptr)
    {
        tail = head;
    }
}

template <typename T>
void SLinkedList<T>::add_back(const T &e)
{
    if (head == nullptr)
    {
        SNode<T> *w = new SNode<T>;
        w->elem = e;
        tail = head = w;
        return;
    }
    SNode<T> *v = new SNode<T>;
    v->elem = e;
    v->next = nullptr;
    tail->next = v;
    tail = v;
}

template <typename T>
void SLinkedList<T>::remove_front()
{
    if (empty())
        return;
    SNode<T> *old = head;
    head = old->next;
    if (head == nullptr)
        tail = nullptr;
    delete old;
}

template <typename T>
void SLinkedList<T>::remove_back()
{
    if (head == tail)
    {
        delete head;
        head = tail = nullptr;
        return;
    }
    if (head == nullptr)
        return;

    SNode<T> *indirect = head;
    while (indirect->next != tail)
    {
        indirect = indirect->next;
    }
    delete tail;
    tail = indirect;
    tail->next = nullptr;
}

template <typename T>
int SLinkedList<T>::search(const T &e, bool compatibility_flag)
{
    int index = 0;
    SNode<T> *indirect = head;
    while (indirect != nullptr)
    {
        if (indirect->elem == e){ return index; }
        indirect = indirect->next;
        index++;
    }
    return -1;
}

template <typename T>
void SLinkedList<T>::insert(const T &e, size_t pos)
{
    if (pos == 0)
    {
        this->add_front(e);
        return;
    }
    SNode<T> *current = this->head;
    for (int i = 1; i < pos; i++)
    {
        current = current->next;
    }
    if (current->next == nullptr)
    {
        this->add_back(e);
        return;
    }
    SNode<T> *newNode = new SNode<T>;
    SNode<T> *oldNode = current->next;

    current->next = newNode;
    newNode->elem = e;
    newNode->next = oldNode;
}

template <typename T>
void SLinkedList<T>::remove(size_t pos)
{
    if (pos == 0)
    {
        this->remove_front();
        return;
    }
    SNode<T> *current = head;
    for (int i = 1; i < pos; i++)
    {
        current = current->next;
    }
    if (current->next == nullptr)
    {
        this->remove_back();
        return;
    }
    SNode<T> *trash = current->next;
    current->next = trash->next;
    delete trash;
}

template <typename T>
void SLinkedList<T>::print()
{
    std::cout << "[";
    SNode<T>* current = this->head;
    while(current != nullptr){
        std::cout << current->elem;
        current = current->next;
        if(current != nullptr){
            std::cout << ", ";
        }
    }
    std::cout << "]\n";
}