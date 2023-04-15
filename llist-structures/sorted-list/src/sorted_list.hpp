
#ifndef _Sorted_list_h
#define _Sorted_list_h

#include <iostream>
#include <stdexcept>

template <typename T> class Sorted_list {

private:

    class Single_node {

    public:
        Single_node();
        Single_node(T const&, Single_node*);

        T get() const;
        Single_node *next() const;

        Single_node *m_next;

    private:
        T m_data;
    };

    Single_node *m_head;
    int m_size = 0;

public:
    Sorted_list();
    Sorted_list(Sorted_list const&);
    ~Sorted_list();

    int size() const;
    int count(T const&) const;
    int erase(T const&);

    bool empty() const;
    T front() const;
    T pop_front();

    Single_node *head() const;

    void swap(Sorted_list&);
    void insert(T const&);

    Sorted_list& operator=(Sorted_list const&);

    template <typename S>
    friend std::ostream &operator<<(std::ostream&, Sorted_list<S> const&);

};

template <typename T>
Sorted_list<T>::Sorted_list() {}

template <typename Type>
Sorted_list<Type>::Sorted_list( Sorted_list<Type> const &list ):
    m_head( nullptr ),
    m_size( 0 )
{
    Single_node* node = list.head();
    while (node != nullptr) {
        insert(node->get());
        node = node->next();
    }
}

template <typename T>
Sorted_list<T>::~Sorted_list()
{

    Single_node *temp = m_head;

    while (temp != nullptr) {
        temp = temp->next();
        delete m_head;
        m_head = temp;
    }
}

template <typename T>
int Sorted_list<T>::size() const
{
    return m_size;
}

template <typename T>
int Sorted_list<T>::count(T const& value) const
{
    int count = 0;

    Single_node *node = m_head;
    while (node != nullptr) {
        if (node->get() == value) count++;
        node = node->next();
    }
    return count;
}

template <typename T>
int Sorted_list<T>::erase(T const& value)
{

    if (size() == 0) return 0;

    if (front() == value) {
        Single_node *node = m_head->next();
        delete m_head;
        m_head = node;
        m_size--;
        return 1;
    }
    else {
        Single_node *prev = m_head;
        Single_node *curr = m_head;
        while (curr != nullptr) {
            if (curr->get() == value) {
                prev->m_next = curr->next();
                delete curr;
                m_size--;
                return 1;
            }
            else {
                prev = curr;
                curr = curr->next();
            }
        }
    }
    return 0;
}

template <typename T>
bool Sorted_list<T>::empty() const
{
    return size() == 0;
}

template <typename T>
T Sorted_list<T>::front() const
{
    if (empty())
        throw std::invalid_argument("Can't access an empty list!");
    return head()->get();
}

template <typename T>
T Sorted_list<T>::pop_front()
{

    if (empty()) throw std::invalid_argument("Can't access an empty list!");

    T node = front();
    Single_node *next = m_head->next();
    delete m_head;
    m_head = next;
    --m_size;
    return node;
}

template <typename T>
typename Sorted_list<T>::Single_node* Sorted_list<T>::head() const
{
    return m_head;
}

template <typename T>
void Sorted_list<T>::insert(T const& value)
{

    Single_node *new_node = new Single_node(value, nullptr);

    if (empty()) {
        m_head = new_node;
        ++m_size;
        return;
    }

    if (value <= head()->get()) {
        new_node->m_next = head();
        m_head = new_node;
        ++m_size;
        return;
    }

    Single_node *curr = m_head;
    while (curr->next() != nullptr && value > curr->next()->get()) {
        curr = curr->next();
    }
    new_node->m_next = curr->next();
    curr->m_next = new_node;
    ++m_size;
    return;
}

template <typename T>
void Sorted_list<T>::swap(Sorted_list<T> &list)
{
    std::swap(m_head, list.m_head);
    std::swap(m_size, list.m_size);
}

template <typename T>
Sorted_list<T>& Sorted_list<T>::operator=(Sorted_list<T> const& rhs)
{
    Sorted_list<T> copy(rhs);
    swap(copy);
    return *this;
}

template <typename T>
Sorted_list<T>::Single_node::Single_node()
{
    m_next = nullptr;
}

template <typename T>
Sorted_list<T>::Single_node::Single_node(T const& value, Single_node *next)
{
    m_data = value;
    m_next = next;
}

template <typename T>
T Sorted_list<T>::Single_node::get() const
{
    return m_data;
}

template <typename T>
typename Sorted_list<T>::Single_node* Sorted_list<T>::Single_node::next() const
{
    return m_next;
}

template <typename S>
std::ostream &operator<<( std::ostream &out, Sorted_list<S> const &list )
{
    for (typename Sorted_list<S>::Single_node *ptr = list.head(); ptr != nullptr; ptr = ptr->next() ) {
        out << "->" << ptr->get();
    }

    out << "->0";

    return out;
}

#endif
