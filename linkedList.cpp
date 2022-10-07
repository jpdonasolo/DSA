#include <iostream>
#include "linkedList.h"


template <typename T> 
void LinkedList<T>::print(){
    Node * cur = m_head;
    // TODO create iterator
    while (!isNil(cur)){
        std::cout << cur->data << " -> ";
        cur = cur->next;
    }
    std::cout << "NIL\n";
}

template <typename T>
void LinkedList<T>::insertFirst(T data){
    Node * n = new Node(data);

    // List is empty
    if (isNil(m_head)){
        m_head = n;
        m_tail = n;

        n->next = m_nil;
        n->prev = m_nil;
    }
    else{
        n->next = m_head;
        n->prev = m_nil;

        m_head->prev = n;
        m_head = n;
    }
}

// template <typename T>
// void LinkedList<T>::insertLast(T data){
//     Node * n = new Node(data);

//     // List is empty
//     if (isNil(m_tail)){
//         m_head = n;
//         m_tail = n;
//         n->next = m_nil;  
//     }
//     else {
//         m_tail->next = n;

//     }
// }

template <typename T>
void LinkedList<T>::insertAfter(T prevData, T data){
    Node * n = new Node(data);
    Node ** prevNode;
    
    find(prevNode, prevData);
    if (isNil(*prevNode)) return;

    // Is tail
    if (*(prevNode) == m_tail){
        n->prev = m_tail;
        n->next = m_nil;

        m_tail->next = n;
        m_tail = n;
    }
    else {
        n->next = (*prevNode)->next;
        n->prev = (*prevNode);

        (*prevNode)->next->prev = n;
        (*prevNode)->next = n;
    }
}

template <typename T>
void LinkedList<T>::find(Node **& prevNode, T prevData){
    prevNode = &m_head;
    while ((*prevNode)->data != prevData && !isNil(*prevNode)){
        prevNode = &(*prevNode)->next;
    }
}

template <typename T>
void LinkedList<T>::pop(T data){
    Node ** node;
    find(node, data);

    // Not in list
    if (isNil((*node))){
        throw "Not in list\n";
    }

    Node * oldNode = (*node);
    
    // Head
    if ((*node) == m_head){
        m_head = (*node)->next;
        m_head->prev = m_nil;
    }
    // Trail
    else if ((*node) == m_tail){
        m_tail = (*node)->prev;
        m_tail->next = m_nil;
    }
    // In between
    else{
        (*node)->prev->next = (*node)->next;
        (*node)->next->prev = (*node)->prev;
    }
    delete oldNode;

    // Deleted node was head, now list is empty. Must update tail
    if (isNil(m_head)){
        m_tail = m_nil;
    }

}

int main(int argc, char const *argv[])
{
    
    LinkedList<int> list;

    list.insertAfter(0, 20); //

    list.insertFirst(4); // 4
    list.insertFirst(6); // 6 4
    list.insertFirst(24); // 24 6 4

    list.insertAfter(6, 7); // 24 6 7 4
    list.insertAfter(0, 3); // 24 6 7 4
    list.insertAfter(4, 300); // 24 6 7 4 300
    list.insertAfter(24, 33); // 24 33 6 7 4 300

    list.pop(24); // 33 6 7 4 300
    list.pop(300); // 33 6 7 4
    list.pop(6); // 33 7 4
     
    list.print();

    list.pop(33);
    list.pop(7);
    list.pop(4);

    list.print();

    list.pop(0);

    return 0;
}
