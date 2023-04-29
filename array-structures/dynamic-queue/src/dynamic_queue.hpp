
#ifndef _Dynamic_queue_h
#define _Dynamic_queue_h

#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <iterator>

template <typename T>
class Dynamic_queue {

public:
    Dynamic_queue();
    Dynamic_queue(int n);
    Dynamic_queue(Dynamic_queue const&);
    ~Dynamic_queue();

    bool empty() const;

    int size() const;
    int capacity() const;

    void swap(Dynamic_queue&);
    void enqueue(T const&);
    void clear();

    T head() const;
    T dequeue();

    Dynamic_queue& operator=(Dynamic_queue);

    template <typename S>
    friend std::ostream &operator<<(std::ostream&, Dynamic_queue<S> const&);

private:
    int mi_head = 0;
    int mi_tail = 0;
    int m_count = 0;
    int m_init_cap;
    int m_array_cap;

    T *m_array;

    enum Transform {
        GROW,
        SHRINK
    };

    void resize(Transform);

};

template <typename T>
Dynamic_queue<T>::Dynamic_queue()
{
    m_init_cap = 10;
    m_array_cap = 10;

    m_array = new T[m_init_cap];
}

template <typename T>
Dynamic_queue<T>::Dynamic_queue(int n)
{
    if (n <= 0) n = 1;

    m_init_cap = n;
    m_array_cap = n;

    m_array = new T[m_init_cap];
}

template <typename T>
Dynamic_queue<T>::Dynamic_queue(Dynamic_queue<T> const& list):
    mi_head(list.mi_head),
    mi_tail(list.mi_tail),
    m_count(list.m_count),
    m_init_cap(list.m_init_cap),
    m_array_cap(list.m_array_cap),
    m_array(new T[list.m_array_cap])
{
    for (int i = 0; i < list.m_count; i++) {
        int index = (list.mi_head + i) % list.m_array_cap;
        m_array[index] = list.m_array[index];
    }
}

template <typename T>
Dynamic_queue<T>::~Dynamic_queue()
{
    delete[] m_array;
}

template <typename T>
T Dynamic_queue<T>::head() const
{
    if (empty()) {
        throw std::invalid_argument("Can't access an empty queue");
    }
    return m_array[mi_head];
}

template <typename T>
int Dynamic_queue<T>::size() const
{
    return m_count;
}

template <typename T>
bool Dynamic_queue<T>::empty() const
{
    return m_count == 0;
}

template <typename T>
int Dynamic_queue<T>::capacity() const
{
    return m_array_cap;
}

template <typename T>
void Dynamic_queue<T>::swap(Dynamic_queue<T>& queue)
{
    std::swap(m_init_cap, queue.m_init_cap);
    std::swap(m_array_cap, queue.m_array_cap);
    std::swap(mi_head, queue.mi_head);
    std::swap(mi_tail, queue.mi_tail);
    std::swap(m_count, queue.m_count);
    std::swap(m_array, queue.m_array);
}

template <typename T>
void Dynamic_queue<T>::enqueue(T const& data)
{
    if (size() == capacity()) {
        resize(GROW);
    }

    m_array[mi_tail] = data;
    mi_tail = (mi_tail + 1) % m_array_cap;
    m_count++;
}

template <typename T>
T Dynamic_queue<T>::dequeue()
{
    if (empty()) {
        throw std::invalid_argument("Can't access an empty queue");
    }

    T data = m_array[mi_head];

    mi_head = (mi_head + 1) % m_array_cap;
    m_count--;

    if ((m_count * 4) <= m_array_cap && m_array_cap > m_init_cap) {
        resize(SHRINK);
    }
    return data;
}

template <typename T>
void Dynamic_queue<T>::resize(Transform f)
{
    int new_size;

    if (f == GROW) {
        new_size = m_array_cap * 2;
    }
    else if (f == SHRINK) {
        new_size = m_array_cap / 2;
    }
    else {
        throw std::invalid_argument("something went wrong");
    }

    T *new_array = new T[new_size];

    for (int i = 0; i < m_count; i++) {
        new_array[i] = m_array[(mi_head + i) % m_array_cap];
    }

    delete[] m_array;
    m_array = new_array;

    // set variables to new values
    m_array_cap = new_size;
    mi_head = 0;
    mi_tail = m_count;
}

template <typename T>
void Dynamic_queue<T>::clear()
{
    T *init_array = new T[m_init_cap];
    delete[] m_array;

    m_array = init_array;
    mi_head = 0;
    mi_tail = 0;
    m_count = 0;
    m_array_cap = m_init_cap;
}

template <typename T>
Dynamic_queue<T>& Dynamic_queue<T>::operator=(Dynamic_queue<T> rhs)
{
    Dynamic_queue<T> copy(rhs);
    swap(copy);
    return *this;
}

template <typename S>
std::ostream &operator<<(std::ostream &os, Dynamic_queue<S> const& queue)
{
    int index;
    for (int i = 0; i < queue.m_count-1; i++) {
        index = (queue.mi_head + i) % queue.m_array_cap;

        os << queue.m_array[index] << std::endl;
    }
    index = (queue.mi_head + queue.m_count-1) % queue.m_array_cap;

    os << queue.m_array[index];

    return os;
}


#endif
