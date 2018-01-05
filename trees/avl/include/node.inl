#include "node.h"

/// Default constructor
template <typename T>
Node<T>::Node(const int & d, const T & c, Node *p, Node *n , int a )
:key(d), 
content(c),
left(p),
right(n),
height(a)
{/* empty*/ }

/// Return key of the node.
template <typename T>
int Node<T>::getKey(){
    return key;
}

/// Update key.
template <typename T>
void Node<T>::setKey(int key){
    this->key = key;
}

/// Return content of the node.
template <typename T>
T Node<T>::getContent(){
    return content;
}

/// Update content.
template <typename T>
void Node<T>::setContent(T content){
    this->content = content;
}

/// Return left child of the node.
template <typename T>
Node<T>* Node<T>::getLeft(){
    return left;
}

/// Update left child.
template <typename T>
void Node<T>::setLeft(Node<T>* left){
    this->left = left;
}

/// Return right child of the node.
template <typename T>
Node<T>* Node<T>::getRight(){
    return right;
}

/// Update right child.
template <typename T>
void Node<T>::setRight(Node<T>* right){
    this->right = right;
}

/// Return height of the node.
template <typename T>
int Node<T>::getHeight(){
    return height;
}

/// Update height.
template <typename T>
void Node<T>::setHeight(int height){
    this->height = height;
}

/// Return balance of the node.
template <typename T>
int Node<T>::getBal(){
    return bal;
}

/// Update baçance.
template <typename T>
void Node<T>::setBal(int bal){
    this->bal = bal;
}