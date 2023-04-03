#include "List.h"
#include <iterator>
#include <utility>
#include <stdexcept>

using namespace std;
#include <iostream>

template<typename T>
struct List<T>::Node
{
    Node() = default;
    Node(T v, Node* p, unique_ptr<Node> n)
        : value{v}, prev{p}, next{move(n)} {}
    T value {};
    unique_ptr<Node> next {};
    Node * prev {};
};

template<typename T>
List<T>::~List() {}

template<typename T>
List<T>::List()
    : head{ new Node{} }, tail{}, sz{}
{
    T tmp{};
    head->next = make_unique<Node>(tmp, head.get(), nullptr);
    tail = head->next.get();
}

template<typename T>
List<T>::List(List<T> const & other)
    : List{}
{
    for (Node * tmp {other.head->next.get()}; tmp != other.tail ; )
    {
        push_back(tmp->value);
        tmp = tmp->next.get();
    }
}

template<typename T>
List<T>::List(List<T> && tmp) noexcept
    :List{}
{
    swap(tmp);
}

template<typename T>
List<T>::List(std::initializer_list<T> lst)
    : List{}
{
    for ( auto val : lst )
    {
        push_back(val);
    }
}

template<typename T>
void List<T>::push_front(T value)
{
    Node * old_first { head->next.get() };
    head->next = make_unique<Node>(value, head.get(), move(head->next));
    old_first->prev = head->next.get();
    ++sz;
}

template<typename T>
void List<T>::push_back(T value)
{
    Node * old_last { this->tail->prev };
    old_last->next = make_unique<Node>(value, old_last, move(old_last->next));
    tail->prev = old_last->next.get();
    ++sz;
}


template<typename T>
bool List<T>::empty() const noexcept
{
    return head->next.get() == tail;
}

template<typename T>
T List<T>::back() const noexcept
{
    return tail->prev->value;
}


template<typename T>
T & List<T>::back() noexcept
{
    return tail->prev->value;
}

template<typename T>
T List<T>::front() const noexcept
{
    return head->next->value;
}

template<typename T>
T & List<T>::front() noexcept
{
    return head->next->value;
}

template<typename T>
T & List<T>::at(int idx)
{
    return const_cast<T &>(static_cast<List<T> const *>(this)->at(idx));
}

template<typename T>
T const & List<T>::at(int idx) const
{
    if (idx >= sz)
        throw std::out_of_range{"Index not found"};
    Node * tmp {head->next.get()};
    while ( idx > 0 )
    {
        tmp = tmp->next.get();
        --idx;
    }
    return tmp->value;
}

template<typename T>
int List<T>::size() const noexcept
{
    return sz;
}

template<typename T>
void List<T>::swap(List & other) noexcept
{
    using std::swap;
    swap(head, other.head);
    swap(tail, other.tail);
    swap(sz, other.sz);
}

template<typename T>
List<T> & List<T>::operator=(List<T> const & rhs) &
{
    List{rhs}.swap(*this);
    return *this;
}

template<typename T>
List<T> & List<T>::operator=(List<T> && rhs)& noexcept
{
    swap(rhs);
    return *this;
}

template<typename T>
List<T>::List_Iterator::List_Iterator() : ptr{nullptr} {}

template<typename T>
List<T>::List_Iterator::List_Iterator(Node* ptr) 
    : ptr{ptr} {}

template<typename T>
ostream& operator<<(ostream &os, List<T> const &list) {
    for(int i = 0; i < list.size(); i++) {
        os << list.at(i);
        if (i+1 != list.size()) {
            os << " ";
        }
    }
    return os;
}


template<typename T>
typename List<T>::List_Iterator List<T>::begin() {
    return List_Iterator(this->head->next.get());
}

template<typename T>
typename List<T>::List_Iterator List<T>::end() {
    return List_Iterator(this->tail);
}


template<typename T>
typename List<T>::List_Iterator& List<T>::List_Iterator::operator++() {
    ptr = ptr->next.get();
    return *this;
}

template<typename T>
typename List<T>::List_Iterator List<T>::List_Iterator::operator++(int) {
    List_Iterator temp = *this;
    operator++();
    return temp;
}

template<typename T>
typename List<T>::List_Iterator& List<T>::List_Iterator::operator--() {
    ptr = ptr->prev;
    return *this;
}

template<typename T>
typename List<T>::List_Iterator List<T>::List_Iterator::operator--(int) {
    List_Iterator temp = *this;
    operator--();
    return temp;
}

template<typename T>
typename List<T>::List_Iterator::reference List<T>::List_Iterator::operator*() const {
    return this->ptr->value;
}

template<typename T>
typename List<T>::List_Iterator::pointer List<T>::List_Iterator::operator->() const {
    return &this->ptr->value;
}

template<typename T>
bool List<T>::List_Iterator::operator==(List<T>::List_Iterator const& rhs) const {
    return this->ptr == rhs.ptr;
}

template<typename T>
bool List<T>::List_Iterator::operator!=(List<T>::List_Iterator const& rhs) const {
    return !(this->ptr == rhs.ptr);
}


