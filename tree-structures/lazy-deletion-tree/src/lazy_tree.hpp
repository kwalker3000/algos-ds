
#ifndef _Lazy_tree_h
#define _Lazy_tree_h

#include <iostream>
#include <algorithm>
#include <queue>
#include <deque>
#include <set>
#include <stdexcept>


template <typename T>
class Lazy_tree {

public:
    Lazy_tree();
    ~Lazy_tree();

    bool empty() const;
    bool insert(T const&);
    bool erase(T const&);
    bool member(T const&) const;

    int size() const;
    int height() const;

    T front() const;
    T back() const;

    void breadth_first_traversal() const;
    void clear();
    void clean();

private:
    struct tree_node {
        std::pair<T, bool> value;
        tree_node *left, *right;
    };
    int m_size;
    struct tree_node* m_root;

    int max_height(tree_node*) const;
    T max_extrema(tree_node* ) const;
    T min_extrema(tree_node*) const;
    bool insert_node(tree_node*&, T const&);
    void clear_tree(tree_node*);
    void in_order(tree_node*, std::vector<tree_node*>&);
};

template <typename T>
Lazy_tree<T>::Lazy_tree(): m_root(nullptr), m_size(0) {}

template <typename T>
Lazy_tree<T>::~Lazy_tree() {}

template <typename T>
bool Lazy_tree<T>::empty() const
{
    return m_size == 0;
}

template <typename T>
int Lazy_tree<T>::size() const
{
    return m_size;
}

template <typename T>
int Lazy_tree<T>::height() const
{
    return max_height(m_root);
}

template <typename T>
int Lazy_tree<T>::max_height(tree_node* node) const
{
    if (node == nullptr) return 0;
    else {
        return std::max(max_height(node->left), max_height(node->right)) +1;
    }
}

template <typename T>
void Lazy_tree<T>::breadth_first_traversal() const
{
    if (m_root == nullptr) return;

    else {
        std::set<tree_node*> visited;
        std::queue<tree_node*> visit;
        visit.push(m_root);

        while (!visit.empty()) {
            tree_node* node = visit.front();
            visit.pop();

            if (!visited.count(node)) {
                std::cout << " " << node->value.first << " " << std::endl;
                // add left node and right node
                visited.insert(node);
                if (node->left) visit.push(node->left);
                if (node->right) visit.push(node->right);
            }
        }
    }
}

template <typename T>
bool Lazy_tree<T>::member(T const& node) const
{

}

template <typename T>
T Lazy_tree<T>::front() const
{
    if (m_root == nullptr)
        std::invalid_argument("Invalid access to empty tree");
    else {
        return min_extrema(m_root);
    }
}

template <typename T>
T Lazy_tree<T>::back() const
{
    if (m_root == nullptr)
        std::invalid_argument("Invalid access to empty tree");
    else {
        return max_extrema(m_root);
    }
}

template <typename T>
T Lazy_tree<T>::min_extrema(tree_node* node) const
{
    if (node == nullptr) return 0;
    else if (!min_extrema(node->left)) {
        if (node->value.second == true) {
            return node->value.first;
        }
        return min_extrema(node->right);
    }
    return 0;
}
template <typename T>
T Lazy_tree<T>::max_extrema(tree_node* node) const
{
    if (node == nullptr) return 0;
    else if (!max_extrema(node->right)) {
        if (node->value.second == true) {
            return node->value.first;
        }
        return min_extrema(node->left);
    }
    return 0;
}

template <typename T>
bool Lazy_tree<T>::insert(T const& key)
{
    return insert_node(m_root, key);
}

template <typename T>
bool Lazy_tree<T>::insert_node(tree_node* & node, T const& key)
{
    if (node == nullptr) {
        node = new tree_node;
        node->value.first = key;
        node->value.second = true;
        node->left = node->right = nullptr;
        m_size++;
        return true;
    }
    else {
        if (node->value.first == key) {
            if (node->value.second == false) {
                node->value.second = true;
                return true;
            }
            return false;
        }
        else {
            if (key < node->value.first) {
                insert_node(node->left, key);
            }
            else {
                insert_node(node->right, key);
            }
        }
    }
    return true;
}

template <typename T>
bool Lazy_tree<T>::erase(T const& key)
{
    if (m_root == nullptr) return false;
    else {
        tree_node* node = m_root;
        while (node->value.first != key && node != nullptr) {
            node = key > node->value.first ? node->right : node->left;
        }
        if (node) {
            if (node->value.second == true) {
                node->value.second = false;
                return true;
            }
            else return false;
        }
        else return false;
    }
}

template <typename T>
void Lazy_tree<T>::clear()
{
    clear_tree(m_root);
    m_size = 0;

}

template <typename T>
void Lazy_tree<T>::clear_tree(tree_node* node)
{
    if (node == nullptr) return;
    else {
        clear_tree(node->left);
        clear_tree(node->right);
        node = nullptr;
        delete node;
    }
}

template <typename T>
void Lazy_tree<T>::clean()
{
    std::vector<tree_node*> tree;
    in_order(m_root, tree);
    for (tree_node* node : tree) {
        std::cout << node->value.first << '\n';
        if (node->left) {
            std::cout << node->left->value.first << " ===== ";
        }
        if (node->right) {
            std::cout << node->right->value.first << std::endl;
        }
    }
}

template <typename T>
void Lazy_tree<T>::in_order(tree_node* node, std::vector<tree_node*>& tree)
{
    if (node == nullptr) return;
    else {
        in_order(node->left, tree);
        node->left = nullptr;
        tree.emplace_back(node);
        in_order(node->right, tree);
        node->right = nullptr;
    }

}

// template <typename T>
// T extrema(T* node, int i) {} // if node is a struct then the only 'Type' instance should be the value of the struct

#endif
