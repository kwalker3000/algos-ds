
#ifndef _Navigation_stack_h
#define _Navigation_stack_h

#include <iostream>
#include <stdexcept>
#include <forward_list>

template <typename T>
class Navigation_stack {

public:
    Navigation_stack();
    Navigation_stack(Navigation_stack const&);
    ~Navigation_stack();

    bool can_undo() const;
    bool can_redo() const;

    void swap(Navigation_stack&);
    void event(T const&);
    void clear();

    T undo();
    T redo();

    Navigation_stack& operator=(Navigation_stack&);

private:
    std::forward_list<T> undo_stack;
    std::forward_list<T> redo_stack;

    int m_undo_size = 0;
    int m_redo_size = 0;

};

template <typename T>
Navigation_stack<T>::Navigation_stack() {}

template <typename T>
Navigation_stack<T>::Navigation_stack(Navigation_stack<T> const& list): m_undo_size(0), m_redo_size(0)
{
    undo_stack = list.undo_stack;
    redo_stack = list.redo_stack;
    m_undo_size = list.m_undo_size;
    m_redo_size = list.m_redo_size;
}

template <typename T>
Navigation_stack<T>::~Navigation_stack() {}

template <typename T>
bool Navigation_stack<T>::can_undo() const
{
    return m_undo_size != 0;
}

template <typename T>
bool Navigation_stack<T>::can_redo() const
{
    return m_redo_size != 0;
}

template <typename T>
void Navigation_stack<T>::event(T const& event)
{
    undo_stack.push_front(event);
    m_undo_size++;

    while (can_redo()) {
        redo_stack.pop_front();
        m_redo_size--;
    }
}

template <typename T>
T Navigation_stack<T>::undo()
{
    if (!can_undo()) {
        throw std::invalid_argument("Undo stack is empty");
    }
    T event = undo_stack.front();
    undo_stack.pop_front();
    redo_stack.push_front(event);
    m_undo_size--;
    m_redo_size++;

    return event;
}

template <typename T>
T Navigation_stack<T>::redo()
{
    if (!can_redo()) {
        throw std::invalid_argument("Redo stack is empty");
    }
    T event = redo_stack.front();
    redo_stack.pop_front();
    undo_stack.push_front(event);
    m_redo_size--;
    m_undo_size++;

    return event;
}

template <typename T>
void Navigation_stack<T>::clear()
{
    while (can_redo()) {
        redo_stack.pop_front();
        m_redo_size--;
    }
    while (can_undo()) {
        undo_stack.pop_front();
        m_undo_size--;
    }
}

template <typename T>
void Navigation_stack<T>::swap(Navigation_stack<T> &stack)
{
    std::swap(undo_stack, stack.undo_stack);
    std::swap(redo_stack, stack.redo_stack);
    std::swap(m_undo_size, stack.m_undo_size);
    std::swap(m_redo_size, stack.m_redo_size);
}

template <typename T>
Navigation_stack<T>& Navigation_stack<T>::operator=(Navigation_stack<T>& rhs)
{
    Navigation_stack<T> copy(rhs);
    swap(copy);
    return *this;
}



#endif
