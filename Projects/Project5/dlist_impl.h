#ifndef PROJECT_5_RELATED_FILES_DLIST_IMPL_H
#define PROJECT_5_RELATED_FILES_DLIST_IMPL_H

#include <iostream>
#include "dlist.h"


template<class T>
Dlist<T>::Dlist() {
    node *newnode = new node;
    newnode->op = NULL;
    newnode->next = NULL;
    newnode->prev = NULL;
    first = newnode;
    last = newnode;
}

template<class T>
bool Dlist<T>::isEmpty() const {
    if (!first && !last) {
        return true;
    }
    return (first->op == NULL);
}

template<class T>
void Dlist<T>::insertFront(T *op) {
    if (op == NULL) { return; }
    if (isEmpty() && first!=NULL) {
        first->op = op;
        return;
    }
    node *tmp = new node;
    tmp->op = op;
    if(!isEmpty()){
        tmp->next = first;
        tmp->prev = NULL;
        first->prev = tmp;
        first = tmp;
    }
    else{
        first = tmp;
        last = tmp;
        tmp->next = NULL;
        tmp -> prev = NULL;
    }
}

template<class T>
void Dlist<T>::insertBack(T *op) {
    if (op == NULL) { return; }
    if (isEmpty() && first!=NULL) {
        first->op = op;
        return;
    }
    node *tmp = new node;
    tmp->op = op;
    if (!isEmpty()){
        tmp->prev = last;
        tmp->next = NULL;
        last->next = tmp;
        last = tmp;
    }
    else{
        first = tmp;
        last = tmp;
        tmp->next = NULL;
        tmp -> prev = NULL;
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
    if(first==NULL){last=NULL;}
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
    if(last==NULL){first=NULL;}
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
        node *newnode = new node;
        newnode->op = NULL;
        newnode->next = NULL;
        newnode->prev = NULL;
        first = newnode;
        last = newnode;
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
    node *newnode = new node;
    newnode->op = NULL;
    newnode->next = NULL;
    newnode->prev = NULL;
    first = newnode;
    last = newnode;
    copyAll(l);
}

template<class T>
Dlist<T> &Dlist<T>::operator=(const Dlist &l) {
    if (this == &l) { return *this; }
    copyAll(l);
    return *this;
}

template<class T>
T *Dlist<T>::remove(bool (*cmp)(const T *, const T *), T *ref) {
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

#endif //PROJECT_5_RELATED_FILES_DLIST_IMPL_H
