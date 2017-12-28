#include "node.h"

template <typename T>
Node<T>::Node(const int & d, const T & c, Node *p, Node *n , int a )
:key(d), 
content(c),
left(p),
right(n),
height(a)
{/* empty*/ }

template <typename T>
int Node<T>::getKey(){
    return key;
}

template <typename T>
void Node<T>::setKey(int key){
    this->key = key;
}

template <typename T>
T Node<T>::getContent(){
    return content;
}

template <typename T>
void Node<T>::setContent(T content){
    this->content = content;
}

template <typename T>
Node<T>* Node<T>::getLeft(){
    return left;
}

template <typename T>
void Node<T>::setLeft(Node<T>* left){
    this->left = left;
}

template <typename T>
Node<T>* Node<T>::getRight(){
    return right;
}

template <typename T>
void Node<T>::setRight(Node<T>* right){
    this->right = right;
}

template <typename T>
int Node<T>::getHeight(){
    return height;
}

template <typename T>
void Node<T>::setHeight(int height){
    this->height = height;
}