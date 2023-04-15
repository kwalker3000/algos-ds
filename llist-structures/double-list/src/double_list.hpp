
#ifndef _Double_list_h
#define _Double_list_h

#include <iostream>
#include <stdexcept>

// With nested node class

template <typename T> class Double_list {

private:

    class Double_node {

    public:
        Double_node();
        Double_node(T const&, Double_node *prevNode = nullptr,
                    Double_node *nextNode = nullptr);

        T get() const;
        Double_node *next() const;
        Double_node *prev() const;

        Double_node *m_next, *m_prev;

    private:
        T m_data;
    };

    Double_node *m_head;
    Double_node *m_tail;
    int m_size = 0;

public:
    Double_list();
    Double_list(Double_list<T> const&);
    ~Double_list();

    int size() const;
    int count(T const&) const;
    int erase(T const data);

    bool contains(T const data) const;
    bool empty() const;
    T front() const;
    T back() const;
    T pop_front();
    T pop_back();

    void push_front(T const data);
    void push_back(T const data);
    void swap(Double_list<T> &);

    Double_node* begin() const;
    Double_node* end() const;
    Double_node* rbegin() const;
    Double_node* rend() const;

    Double_node* head() const;
    Double_node* tail() const;

    Double_list& operator=(Double_list const&);

    template <typename S>
    friend std::ostream &operator<<(std::ostream&, Double_list<S> const&);

};

template <typename T> Double_list<T>::Double_list() {}

template <typename Type>
Double_list<Type>::Double_list( Double_list<Type> const &list ):
    m_head( nullptr ),
    m_tail( nullptr ),
    m_size( 0 )
{
    Double_node* node = list.head();
    while (node != nullptr) {
        push_back(node->get());
        node = node->next();
    }
}

template <typename T> Double_list<T>::~Double_list()
{
    Double_node *node = m_head;
    while (m_head != nullptr) {
        m_head = node->next();
        delete node;
        node = m_head;
    }
}

template <typename T> int Double_list<T>::size() const
{
    return m_size;
}

template <typename T> bool Double_list<T>::empty() const
{
    return m_size == 0;
}

template <typename T> T Double_list<T>::front() const
{
    if (empty())
        throw std::invalid_argument("Can't access an empty list!");
    return head()->get();
}

template <typename T> T Double_list<T>::back() const
{
    if (empty())
        throw std::invalid_argument("Can't access an empty list!");
    if (m_size == 1)
        return front();
    return tail()->get();
}

template <typename T>
typename Double_list<T>::Double_node* Double_list<T>::begin() const
{
    return m_head;
}

template <typename T>
typename Double_list<T>::Double_node* Double_list<T>::end() const
{
    return m_tail;
}

template <typename T>
typename Double_list<T>::Double_node* Double_list<T>::rend() const
{
    return m_head;
}

template <typename T>
typename Double_list<T>::Double_node* Double_list<T>::rbegin() const
{
    return m_tail;
}

template <typename T>
typename Double_list<T>::Double_node* Double_list<T>::head() const
{
    return m_head;
}

template <typename T>
typename Double_list<T>::Double_node* Double_list<T>::tail() const
{
    return m_tail;
}
// does not prevent duplicates
template <typename T>
void Double_list<T>::push_front(
    T const data)
{
    // prev and next are set to null
    Double_node *node = new Double_node(data);

    if (empty()) {
        m_head = node;
        m_tail = node;
    }

    else {
        m_head->m_prev = node;
        node->m_next = m_head;
        m_head = node;
    }
    ++m_size;
}

template <typename T> void Double_list<T>::push_back(T const data)
{

    if (empty()) {
        return push_front(data);
    }
    Double_node *node = new Double_node(data);

    node->m_prev = m_tail;
    m_tail->m_next = node;
    m_tail = node;
    ++m_size;
}

template <typename T>
void Double_list<T>::swap(Double_list<T> &list)
{
    std::swap(m_head, list.m_head);
    std::swap(m_tail, list.m_tail);
    std::swap(m_size, list.m_size);
}

template <typename T>
Double_list<T>& Double_list<T>::operator=(Double_list<T> const& rhs)
{
    Double_list<T> copy(rhs);
    swap(copy);
    return *this;
}

template <typename T> bool Double_list<T>::contains(T const data) const
{

    if (empty())
        return false;

    Double_node *curr = m_head;
    while (curr != nullptr) {

        if (curr->get() == data) {
            return true;
        }
        curr = curr->m_next;
    }
    return false;
}

template <typename T>
T Double_list<T>::pop_front()
{
    T node = front();
    Double_node* temp = m_head->next();
    delete m_head;
    m_head = temp;
    --m_size;
    return node;
}

template <typename T>
T Double_list<T>::pop_back()
{
    if (size() == 1) return pop_front();

    T node = back();
    Double_node* temp = m_tail->prev();
    delete m_tail;
    m_tail = temp;
    m_tail->m_next = nullptr;
    --m_size;
    return node;
}

template <typename T> int Double_list<T>::erase(T const data)
{

    if (empty()) return 0;

    if (front() == data) {
        pop_front();
        return 1;
    }

    else {
        Double_node *curr = m_head;
        while (curr) {
            if (curr->get() == data) {
                if (curr->next() == nullptr) {
                    curr = curr->prev();
                    delete m_tail;
                    m_tail = curr;
                    m_tail->m_next = nullptr;

                }
                else {
                    curr->next()->m_prev = curr->prev();
                    curr->prev()->m_next = curr->next();
                    delete curr;
                }
                --m_size;
                return 1;
            }
            curr = curr->next();
        }
    }
    return 0;
}

template <typename T>
int Double_list<T>::count(T const& value) const
{

    int count = 0;
    if (empty()) return 0;

    Double_node* curr = m_head;
    while (curr) {
        if (curr->get() == value) ++count;
        curr = curr->next();
    }
    return count;
}
template <typename T>
Double_list<T>::Double_node::Double_node()
{
    m_prev = nullptr;
    m_next = nullptr;
}

template <typename T>
Double_list<T>::Double_node::Double_node(T const& data, Double_node *prevNode,
        Double_node *nextNode)
{
    m_data = data;
    m_prev = prevNode;
    m_next = nextNode;
}

template <typename T>
T Double_list<T>::Double_node::get() const
{
    return m_data;
}

template <typename T>
typename Double_list<T>::Double_node* Double_list<T>::Double_node::next() const
{
    return m_next;
}

template <typename T>
typename Double_list<T>::Double_node* Double_list<T>::Double_node::prev() const
{
    return m_prev;
}

template <typename S>
std::ostream &operator<<(std::ostream& os, Double_list<S> const& list)
{
    os << "head";

    for (typename Double_list<S>::Double_node* ptr = list.begin(); ptr != nullptr; ptr = ptr->next()) {
        os << " -> " << ptr->get();
    }
    os << " tail" << std::endl;
    return os;
}

#endif
