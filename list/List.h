#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include <memory>
#include <iterator>

namespace List_NS {
template<typename T>
class List
{
    class List_Iterator;
public:
    List();
    List(List<T> const &);
    List(List<T> &&) noexcept;
    List(std::initializer_list<T>);
    ~List();

    List & operator=(List<T> const &)&;
    List & operator=(List<T> &&)& noexcept;

    void push_front(T);
    void push_back(T);

    T back() const noexcept;
    T & back() noexcept;

    T front() const noexcept;
    T & front() noexcept;

    T & at(int idx);
    T const & at(int idx) const;

    int size() const noexcept;
    bool empty() const noexcept;

    void swap(List<T> & other) noexcept;

    List_Iterator begin();

    List_Iterator end();


private:
    struct Node;
    std::unique_ptr<Node> head;
    Node * tail {};
    int sz {};

    class List_Iterator
    {
    public:
        friend class List;
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = T;
        using pointer = T*;
        using reference = T&;
 
        List_Iterator();
        List_Iterator(Node* ptr);

        reference operator*() const;
        pointer operator->() const;

        List_Iterator& operator++();

        List_Iterator operator++(int);

        List_Iterator& operator--();

        List_Iterator operator--(int);

        bool operator==(List_Iterator const& rhs) const;
        bool operator!=(List_Iterator const& rhs) const;

    private:
        Node* ptr;
    };
};

template<typename T>
std::ostream& operator<<(std::ostream &os, List<T> const &list);

}
#include "List.tcc"

#endif //LIST_H
