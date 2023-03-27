
#ifndef _doubleNode_h
#define _doubleNode_h

template <class Tnode> class DoubleNode {

public:
    // <Tnode> not required in constructor
    DoubleNode();
    // DoubleNode(Tnode const data); // will cause ambiguity with other constructor
    // below
    DoubleNode(Tnode const data, DoubleNode<Tnode> *prevNode = nullptr,
               DoubleNode<Tnode> *nextNode = nullptr);

    Tnode get() const;
    DoubleNode<Tnode> *next() const;
    DoubleNode<Tnode> *prev() const;

    // Should the outside client have access?
    DoubleNode<Tnode> *m_next, *m_prev;

private:
    Tnode m_data;
};

template <class Tnode> DoubleNode<Tnode>::DoubleNode()
{
    m_prev = nullptr;
    m_next = nullptr;

    // this could be are head or tail pointer?
}

// template <class Tnode> // must go before each method
// DoubleNode<Tnode>::DoubleNode(T const data)
// {
//     this->data = data;
//     this->prev = nullptr;
//     this->next = nullptr;
// }

// more functional style as only used passed in arguments
template <class Tnode>
DoubleNode<Tnode>::DoubleNode(Tnode const data, DoubleNode<Tnode> *prevNode,
                              DoubleNode<Tnode> *nextNode)
{
    m_data = data;
    m_prev = prevNode;
    m_next = nextNode;
}

template <class Tnode> Tnode DoubleNode<Tnode>::get() const
{
    return m_data;
}

template <class Tnode> DoubleNode<Tnode> *DoubleNode<Tnode>::next() const
{
    return m_next;
}

template <class Tnode> DoubleNode<Tnode> *DoubleNode<Tnode>::prev() const
{
    return m_prev;
}

#endif

// struct node {
//     int value;
//     node* next;
//     node* prev;
// }
