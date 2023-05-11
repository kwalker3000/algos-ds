
#ifndef _Lazy_tree_h
#define _Lazy_tree_h

#include <climits>
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
    void find_max(tree_node*, T&) const;
    void find_min(tree_node*, T&) const;
    bool insert_node(tree_node*&, T const&);
    void clear_tree(tree_node*);
    void collect_nodes(tree_node*, std::vector<tree_node*>&);
    tree_node* resize(std::vector<tree_node*>& tree, int left, int right);
};

template <typename T>
Lazy_tree<T>::Lazy_tree(): m_root(nullptr), m_size(0) {}

template <typename T>
Lazy_tree<T>::~Lazy_tree()
{
    clear_tree(m_root);
}

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
                std::cout << node->value.first;
                if (node->value.second == false) std::cout << "x ";
                else std::cout << " ";
                // add left node and right node
                visited.insert(node);
                if (node->left) visit.push(node->left);
                if (node->right) visit.push(node->right);
            }
        }
        std::cout << '\n';
    }
}

template <typename T>
bool Lazy_tree<T>::member(T const& node) const
{

}

template <typename T>
T Lazy_tree<T>::front() const
{
    if (m_root == nullptr || m_size == 0) {
        std::invalid_argument("Invalid access to empty tree");
    }
    else {
        T min = m_root->value.first;
        find_min(m_root, min);
        return min;
    }
}

template <typename T>
T Lazy_tree<T>::back() const
{
    if (m_root == nullptr || m_size == 0) {
        std::invalid_argument("Invalid access to empty tree");
    }
    else {
        T max = m_root->value.first;
        find_max(m_root, max);
        return max;
    }
}

template <typename T>
void Lazy_tree<T>::find_min(tree_node* node, T& min) const
{
    if (node == nullptr) return;
    else {
        find_min(node->left, min);
        bool is_active = node->value.second;

        if (is_active) {
            bool active_root = m_root->value.second;

            min = !active_root && min == m_root->value.first
                  ? node->value.first
                  : std::min(node->value.first, min);
        }
        find_min(node->right, min);
    }
}
template <typename T>
void Lazy_tree<T>::find_max(tree_node* node, T& max) const
{
    if (node == nullptr) return;
    else {
        find_max(node->right, max);
        bool is_active = node->value.second;
        if (is_active) {
            bool active_root = m_root->value.second;

            max = !active_root && max == m_root->value.first
                  ? node->value.first
                  : std::max(node->value.first, max);
        }
        find_max(node->left, max);
    }
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
                --m_size;
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
        delete node;
    }
}

template <typename T>
void Lazy_tree<T>::clean()
{
    std::vector<tree_node*> old_tree;
    std::vector<tree_node*> new_tree;

    collect_nodes(m_root, old_tree);

    for (tree_node* node : old_tree) {
        if (!node->value.second) {
            delete node;
        }
        else new_tree.emplace_back(node);
    }
    m_size = new_tree.size();
    m_root = resize(new_tree, 0, new_tree.size()-1);
}

template <typename T>
struct Lazy_tree<T>::tree_node* Lazy_tree<T>::resize(std::vector<tree_node*>& tree, int left, int right)
{
    if (left > right) return nullptr;

    int mid = left + (right-left) / 2;
    tree[mid]->left = resize(tree, left, mid-1);
    tree[mid]->right = resize(tree, mid+1, right);

    return tree[mid];
}

template <typename T>
void Lazy_tree<T>::collect_nodes(tree_node* node, std::vector<tree_node*>& tree)
{
    if (node == nullptr) return;
    else {
        collect_nodes(node->left, tree);
        node->left = nullptr;

        tree.emplace_back(node);

        collect_nodes(node->right, tree);
        node->right = nullptr;
    }
}


#endif
