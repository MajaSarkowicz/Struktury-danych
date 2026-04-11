#pragma once
#include <cstddef>

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
    bool search(const T &e);
};

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
bool SLinkedList<T>::search(const T &e)
{
    SNode<T> *indirect = head;
    while (indirect != nullptr)
    {
        if (indirect->elem == e){ return true; }
        indirect = indirect->next;
    }
    return false;
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
