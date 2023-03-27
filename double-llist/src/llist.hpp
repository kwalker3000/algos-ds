
#ifndef _llist_h
#define _llist_h

#include <iostream>
#include <stdexcept>

// With nested node class

template <typename T> class LinkList {

private:

    class DoubleNode {

    public:
        DoubleNode();
        DoubleNode(T const data, DoubleNode *prevNode = nullptr,
                   DoubleNode *nextNode = nullptr);

        T get() const;
        DoubleNode *next() const;
        DoubleNode *prev() const;

        DoubleNode *m_next, *m_prev;

    private:
        T m_data;
    };

    DoubleNode *m_head;
    DoubleNode *m_tail;
    int m_size = 0;

public:
    LinkList();
    ~LinkList();

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
    void swap(LinkList<T> &);

    DoubleNode* begin() const;
    DoubleNode* end() const;
    DoubleNode* rbegin() const;
    DoubleNode* rend() const;

    DoubleNode* head() const;
    DoubleNode* tail() const;

    LinkList& operator=(LinkList const&);

    template <typename S>
    friend std::ostream &operator<<(std::ostream&, LinkList<S> const&);

};

template <typename T> LinkList<T>::LinkList() {}

template <typename T> LinkList<T>::~LinkList()
{
    DoubleNode *node = m_head;
    while (m_head != nullptr) {
        m_head = node->next();
        delete node;
        node = m_head;
    }
}

template <typename T> int LinkList<T>::size() const
{
    return m_size;
}

template <typename T> bool LinkList<T>::empty() const
{
    return m_size == 0;
}

template <typename T> T LinkList<T>::front() const
{
    if (empty())
        throw std::invalid_argument("Can't access an empty list!");
    return m_head->get();
}

template <typename T> T LinkList<T>::back() const
{
    if (empty())
        throw std::invalid_argument("Can't access an empty list!");
    if (m_size == 1)
        return front();
    return m_tail->get();
}

template <typename T>
typename LinkList<T>::DoubleNode* LinkList<T>::begin() const
{
    return m_head;
}

template <typename T>
typename LinkList<T>::DoubleNode* LinkList<T>::end() const
{
    return m_tail;
}

template <typename T>
typename LinkList<T>::DoubleNode* LinkList<T>::rend() const
{
    return m_head;
}

template <typename T>
typename LinkList<T>::DoubleNode* LinkList<T>::rbegin() const
{
    return m_tail;
}

template <typename T>
typename LinkList<T>::DoubleNode* LinkList<T>::head() const
{
    return m_head;
}

template <typename T>
typename LinkList<T>::DoubleNode* LinkList<T>::tail() const
{
    return m_tail;
}
// does not prevent duplicates
template <typename T>
void LinkList<T>::push_front(
    T const data)
{
    // prev and next are set to null
    DoubleNode *node = new DoubleNode(data);

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

template <typename T> void LinkList<T>::push_back(T const data)
{

    if (empty()) {
        return push_front(data);
    }
    DoubleNode *node = new DoubleNode(data);

    node->m_prev = m_tail;
    m_tail->m_next = node;
    m_tail = node;
    ++m_size;
}

template <typename T>
void LinkList<T>::swap(LinkList<T> &list)
{
    std::swap(m_head, list.m_head);
    std::swap(m_tail, list.m_tail);
    std::swap(m_size, list.m_size);
}

template <typename T>
LinkList<T>& LinkList<T>::operator=(LinkList<T> const& rhs)
{
    LinkList<T> copy(rhs);
    swap(copy);
    return *this;
}

template <typename T> bool LinkList<T>::contains(T const data) const
{

    if (empty())
        return false;

    DoubleNode *curr = m_head;
    while (curr != nullptr) {

        if (curr->get() == data) {
            return true;
        }
        curr = curr->m_next;
    }
    return false;
}

template <typename T>
T LinkList<T>::pop_front()
{
    T node = front();
    DoubleNode* temp = m_head->next();
    delete m_head;
    m_head = temp;
    --m_size;
    return node;
}

template <typename T>
T LinkList<T>::pop_back()
{
    if (size() == 1) return pop_front();

    T node = back();
    DoubleNode* temp = m_tail->prev();
    delete m_tail;
    m_tail = temp;
    m_tail->m_next = nullptr;
    --m_size;
    return node;
}

template <typename T> int LinkList<T>::erase(T const data)
{

    if (empty()) return 0;

    if (front() == data) {
        pop_front();
        return 1;
    }

    else {
        DoubleNode *curr = m_head;
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
int LinkList<T>::count(T const& value) const
{

    int count = 0;
    if (empty()) return 0;

    DoubleNode* curr = m_head;
    while (curr) {
        if (curr->get() == value) ++count;
        curr = curr->next();
    }
    return count;
}
template <typename T>
LinkList<T>::DoubleNode::DoubleNode()
{
    m_prev = nullptr;
    m_next = nullptr;
}

template <typename T>
LinkList<T>::DoubleNode::DoubleNode(T const data, DoubleNode *prevNode,
                                    DoubleNode *nextNode)
{
    m_data = data;
    m_prev = prevNode;
    m_next = nextNode;
}

template <typename T>
T LinkList<T>::DoubleNode::get() const
{
    return m_data;
}

template <typename T>
typename LinkList<T>::DoubleNode* LinkList<T>::DoubleNode::next() const
{
    return m_next;
}

template <typename T>
typename LinkList<T>::DoubleNode* LinkList<T>::DoubleNode::prev() const
{
    return m_prev;
}

template <typename S>
std::ostream &operator<<(std::ostream& os, LinkList<S> const& list)
{
    os << "head";

    for (typename LinkList<S>::DoubleNode* ptr = list.begin(); ptr != nullptr; ptr = ptr->next()) {
        os << " -> " << ptr->get();
    }
    os << " tail" << std::endl;
    return os;
}

#endif