
#ifndef _Quad_hash_h
#define _Quad_hash_h

#include <math.h>
#include <functional>
#include <stdexcept>
#include <iostream>

#define INIT_SIZE 5

enum bin_state_t { UNOCCUPIED, OCCUPIED, ERASED };

template <typename T>
class Quad_hash {

public:
    Quad_hash();
    Quad_hash(int);
    ~Quad_hash();

    int size() const;
    int capacity() const;

    double load_factor() const;

    bool empty() const;
    bool member(T const&) const;
    bool erase(T const&);

    void print() const;
    void insert(T const&);
    void clear();

    T bin(int) const;

private:
    int m_count = 0;
    int m_array_size;
    T* m_array;
    bin_state_t *occupied;
};

template <typename T>
Quad_hash<T>::Quad_hash() : m_array_size(pow(2, INIT_SIZE)), m_array(new T[pow(2, INIT_SIZE)]), occupied(new bin_state_t[pow(2, INIT_SIZE)])
{
    std::fill(occupied, occupied + INIT_SIZE, UNOCCUPIED);
}

template <typename T>
Quad_hash<T>::Quad_hash(int n)
{
    if (n < 0) {
        m_array = new T[pow(2, INIT_SIZE)];
        return;
    }
    m_array = new T[pow(2, n)];
    occupied = new bin_state_t[pow(2, n)];
    m_array_size = pow(2, n);

    std::fill(occupied, occupied + INIT_SIZE, UNOCCUPIED);
}

template <typename T>
Quad_hash<T>::~Quad_hash()
{
    delete[] m_array;
    delete[] occupied;
}

template <typename T>
int Quad_hash<T>::size() const
{
    return m_count;
}

template <typename T>
int Quad_hash<T>::capacity() const
{
    return m_array_size;
}

template <typename T>
double Quad_hash<T>::load_factor() const
{
    return static_cast<double>(m_count)/m_array_size;
}

template <typename T>
bool Quad_hash<T>::empty() const
{
    return m_count == 0;
}

template <typename T>
bool Quad_hash<T>::member(T const& key) const
{
    std::hash<T> key_hash;
    uint hash = key_hash(key);
    int bin_index = hash % m_array_size;

    int k = 1;
    for (int i = 0; i <= m_array_size/2; i++) {
        if (occupied[bin_index] == UNOCCUPIED) return false;
        else if (m_array[bin_index] == key) {
            return true;
        }
        else {
            hash += pow(k, 2);
            bin_index = hash % m_array_size;
        }
    }
    return false;
}

template <typename T>
T Quad_hash<T>::bin(int n) const
{
    if (n > m_array_size-1 || n < 0) {
        throw std::out_of_range("Out of Range error");
    }
    // What if empty?
    return m_array[n];
}

template <typename T>
void Quad_hash<T>::insert(T const& key)
{
    if (m_count == m_array_size) {
        throw std::overflow_error("Bin overflow");
    }
    std::hash<T> key_hash;
    uint hash = key_hash(key);
    int bin_index = hash % m_array_size;

    int k = 1;
    while (occupied[bin_index] == OCCUPIED) {
        if (m_array[bin_index] == key) {
            return;
        }
        hash += pow(k, 2);
        bin_index = hash % m_array_size;
    }
    m_array[bin_index] = key;
    occupied[bin_index] = OCCUPIED;
    ++m_count;
}

template <typename T>
bool Quad_hash<T>::erase(T const& key)
{
    std::hash<T> key_hash;
    uint hash = key_hash(key);
    int bin_index = hash % m_array_size;

    int k = 1;
    for (int i = 0; i <= m_array_size/2; i++) {
        if (m_array[bin_index] == key) {
            occupied[bin_index] = UNOCCUPIED;
            --m_count;
            return true;
        }
        else {
            hash += pow(k, 2);
            bin_index = hash % m_array_size;
        }
    }
    return false;
}

template <typename T>
void Quad_hash<T>::clear()
{
    for (int i = 0; i < m_array_size; i++) {
        occupied[i] = UNOCCUPIED;
    }
    m_count = 0;
}

#endif
