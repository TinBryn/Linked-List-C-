#ifndef LIST_HPP
#define LIST_HPP

#include <initializer_list>

template <typename T>
class List;




template <typename T>
class List
{
public:
    class iterator;

private:
    struct node
    {
        T data;
        node *next;
    };

    node *head;

public:
    List();
    List(const List &other);
    List(List &&other);
    template <typename I>
    List(const I &start, const I &stop);
    List(std::initializer_list<T> init);
    ~List();

    void push_front(const T &data);
    void pop_front();
    auto empty() const -> bool;
    auto front() -> T&;
    auto front() const -> const T&;
    void reverse();
    void clear();

    auto find(const T &key) -> iterator;
    auto begin() -> iterator;
    auto end() -> iterator;

    void erase_after(iterator pos);
    void erase(iterator before, iterator last);
    void insert_after(iterator pos, const T &data);

    operator bool();

    class iterator
    {
    private:
        node *ptr;
    public:
        iterator();
        iterator(const iterator &other);
        iterator(node *init);
        iterator& operator++();
        iterator  operator++(int);
        T& operator*();
        T* operator->();
        bool operator==(iterator rhs);
        bool operator!=(iterator rhs);
        operator bool();
        friend class List;
    };
};

//default list is empty
template<typename T>
List<T>::List() : head(nullptr)
{

}

//copy constructor delegates to iterators constructor
template<typename T>
List<T>::List(const List &other) : List(other.begin(), other.end())
{

}

//move constructor steals contents of other and leaves other empty
template<typename T>
List<T>::List(List &&other) : head(other.head)
{
    other.head = nullptr;
}

//iterators constructor copies data from range
template<typename T>
template<typename I>
List<T>::List(const I &start, const I &stop)
{
    auto curr = start;
    if(curr != stop)
    {
        head = new node;
        head->data = *curr;
        curr++;
        node *temp = head;
        while(curr != stop)
        {
            temp->next = new node;
            temp->next->data = *curr;
            temp = temp->next;
            curr++;
        }
        temp->next = nullptr;
    }
    else
    {
        head = nullptr;
    }
}

//initializer list constructor delegates to iterators constructor
template<typename T>
List<T>::List(std::initializer_list<T> init) : List(init.begin(), init.end())
{

}

//destructor clears the list
template<typename T>
List<T>::~List()
{
    clear();
}

//
template<typename T>
void List<T>::push_front(const T &data)
{
    head = new node{data, head};
}

//
template<typename T>
void List<T>::pop_front()
{
    node *temp = head;
    head = head->next;
    delete temp;
}

//
template<typename T>
auto List<T>::empty() const -> bool
{
    return head == nullptr;
}

//
template<typename T>
auto List<T>::front() -> T&
{
    return head->data;
}

//
template<typename T>
auto List<T>::front() const -> const T&
{
    return head->data;
}

//makes it so that the list is ordered in the opposite direction without
//moving data around
template<typename T>
void List<T>::reverse()
{
    //TODO
    throw 1;
}

//deletes all the data, leaves equivalent to default constructed
template<typename T>
void List<T>::clear()
{
    node *curr = head;
    while(curr != nullptr)
    {
        node *temp = curr;
        curr = curr->next;
        delete temp;
    }
}

//
template<typename T>
auto List<T>::find(const T &key) -> iterator
{
    auto curr = begin();
    auto stop = end();
    while(curr != stop && *curr != key)
    {
        curr++;
    }
    return curr;
}

//
template<typename T>
auto List<T>::begin() -> iterator
{
    return head;
}

//
template<typename T>
auto List<T>::end() -> iterator
{
    return nullptr;
}

//deletes the node after pos, undefined if last node
//UB is probably null deref or nothing happens
template<typename T>
void List<T>::erase_after(iterator pos)
{
    node *temp = pos.ptr->next;
    pos.ptr->next = temp->next;
    delete temp;
}

//erases after before until and including last
template<typename T>
void List<T>::erase(iterator before, iterator last)
{
    node *curr = before.ptr->next;
    before.ptr->next = last.ptr->next;
    while(curr != last.ptr->next)
    {
        node *temp = curr;
        curr = curr->next;
        delete temp;
    }
}

//inserts a node after pos
template<typename T>
void List<T>::insert_after(iterator pos, const T &data)
{
    pos.ptr->next = new node{data, pos.ptr->next};
}

template<typename T>
List<T>::operator bool()
{
    return !empty();
}

template<typename T>
List<T>::iterator::iterator()
{

}

template<typename T>
List<T>::iterator::iterator(const iterator &other) : ptr(other.ptr)
{

}

template<typename T>
List<T>::iterator::iterator(node *init) : ptr(init)
{

}

template<typename T>
auto List<T>::iterator::operator*() -> T&
{
    return ptr->data;
}

template<typename T>
auto List<T>::iterator::operator->() -> T*
{
    return &(ptr->data);
}

template<typename T>
auto List<T>::iterator::operator++() -> iterator&
{
    ptr = ptr->next;
    return *this;
}

template<typename T>
auto List<T>::iterator::operator++(int) -> iterator
{
    iterator res = *this;
    this->operator++();
    return res;
}

template<typename T>
auto List<T>::iterator::operator==(iterator rhs) -> bool
{
    return ptr == rhs.ptr;
}

template<typename T>
auto List<T>::iterator::operator!=(iterator rhs) -> bool
{
    return ptr != rhs.ptr;
}

template<typename T>
List<T>::iterator::operator bool()
{
    return nullptr != ptr;
}




#endif // LIST_HPP

