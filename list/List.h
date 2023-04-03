#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include <memory>
#include <iterator>

class List
{
    class List_Iterator;
public:
    List();
    List(List const &);
    List(List &&) noexcept;
    List(std::initializer_list<int>);
    ~List();

    List & operator=(List const &)&;
    List & operator=(List &&)& noexcept;

    void push_front(int);
    void push_back(int);

    int back() const noexcept;
    int & back() noexcept;

    int front() const noexcept;
    int & front() noexcept;

    int & at(int idx);
    int const & at(int idx) const;

    int size() const noexcept;
    bool empty() const noexcept;

    void swap(List & other) noexcept;

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
        using value_type = int;
        using difference_type = int;
        using pointer = int*;
        using reference = int&;
 
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

std::ostream& operator<<(std::ostream &os, List const &list);

#endif //LIST_H
