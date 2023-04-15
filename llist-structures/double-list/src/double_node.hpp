
#ifndef _Double_node_h
#define _Double_node_h

template <class Tnode> class Double_node {

public:
    Double_node();
    Double_node(Tnode const data, Double_node<Tnode> *prevNode = nullptr,
                Double_node<Tnode> *nextNode = nullptr);

    Tnode get() const;
    Double_node<Tnode> *next() const;
    Double_node<Tnode> *prev() const;

    // Should the outside client have access?
    Double_node<Tnode> *m_next, *m_prev;

private:
    Tnode m_data;
};

template <class Tnode> Double_node<Tnode>::Double_node()
{
    m_prev = nullptr;
    m_next = nullptr;

    // this could be are head or tail pointer?
}

// template <class Tnode> // must go before each method
// Double_node<Tnode>::Double_node(T const data)
// {
//     this->data = data;
//     this->prev = nullptr;
//     this->next = nullptr;
// }

// more functional style as only used passed in arguments
template <class Tnode>
Double_node<Tnode>::Double_node(Tnode const data, Double_node<Tnode> *prevNode,
                                Double_node<Tnode> *nextNode)
{
    m_data = data;
    m_prev = prevNode;
    m_next = nextNode;
}

template <class Tnode> Tnode Double_node<Tnode>::get() const
{
    return m_data;
}

template <class Tnode> Double_node<Tnode> *Double_node<Tnode>::next() const
{
    return m_next;
}

template <class Tnode> Double_node<Tnode> *Double_node<Tnode>::prev() const
{
    return m_prev;
}

#endif

// struct node {
//     int value;
//     node* next;
//     node* prev;
// }
