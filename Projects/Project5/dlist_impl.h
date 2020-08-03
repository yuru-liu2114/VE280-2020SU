#ifndef P5_DLIST_IMPL_H
#define P5_DLIST_IMPL_H

#include <iostream>
#include "dlist.h"

template<class T>
Dlist<T>::Dlist() {
    first = NULL;
    last = NULL;
}

template<class T>
bool Dlist<T>::isEmpty() const {
    return first == NULL && last == NULL;
}

template<class T>
void Dlist<T>::insertFront(T *op) {
    if (op == NULL) { return; }
    node *tmp = new node;
    tmp->op = op;
    if (isEmpty()) {
        last = tmp;
        first = tmp;
        tmp->next = NULL;
        tmp->prev = NULL;
    } else {
        tmp->next = first;
        tmp->prev = NULL;
        first->prev = tmp;
        first = tmp;
    }
}

template<class T>
void Dlist<T>::insertBack(T *op) {
    if (op == NULL) { return; }
    node *tmp = new node;
    tmp->op = op;
    if (isEmpty()) {
        last = tmp;
        first = tmp;
        tmp->next = NULL;
        tmp->prev = NULL;
    } else {
        last->next = tmp;
        tmp->prev = last;
        tmp->next = NULL;
        last = tmp;
    }
}

template<class T>
T *Dlist<T>::removeFront() {
    if (isEmpty()) {
        emptyList empty;
        throw empty;
    }
    node *tmp = first;
    T *tmp_op = tmp->op;
    first = tmp->next;
    if (first == NULL) {
        last = NULL;
    }
    else{
        first->prev=NULL;
    }
    delete tmp;
    return tmp_op;
}

template<class T>
T *Dlist<T>::removeBack() {
    if (isEmpty()) {
        emptyList empty;
        throw empty;
    }
    node *tmp = last;
    T *tmp_op = tmp->op;
    last = tmp->prev;
    if (last == nullptr) { // no node left
        first = nullptr;
    }
    else{
        last->next=nullptr;
    }
    delete tmp;
    return tmp_op;
}
template<class T>
void Dlist<T>::removeAll() {
    node *iter = first;
    while (iter) {
        node *tmp = iter;
        iter = tmp->next;
        delete tmp;
    }
}
template<class T>
Dlist<T>::~Dlist() {
    removeAll();
}

template<class T>
void Dlist<T>::copyAll(const Dlist &l) {
    if (this == &l) { return; }
    if (!isEmpty()) {
        removeAll();
        first=NULL;
        last=NULL;
    }
    node *iter = l.first;
    while (iter) {
        T *tmp_op = iter->op;
        this->insertBack(tmp_op);
        iter=iter->next;
    }
}

template<class T>
Dlist<T>::Dlist(const Dlist &l) {
    first=NULL;
    last=NULL;
    copyAll(l);
}
template<class T>
Dlist<T> &Dlist<T>::operator=(const Dlist &l) {
    if (this != &l) {
        removeAll();
        copyAll(l);
    }
    return *this;
}
template<class T>
T *Dlist<T>::remove(bool (*cmp)(const T *, const T *), T *ref) {
    if(isEmpty()){
        return NULL;
    }
    node* iter=first;
    bool flag=false;
    int size=0;
    while(iter){
        if(cmp(iter->op,ref)){
            flag=true;
        }
        size++;
        iter=iter->next;
    }
    if(!flag){
        return NULL;
    }
    T* result;
    for(int i=0;i<size;++i){
        iter=first;
        if(cmp(iter->op,ref)){
            result=removeFront();
        }
        else{
            T* tmp=removeFront();
            insertBack(tmp);
        }
    }
    return result;

}
#endif //P5_DLIST_IMPL_H
