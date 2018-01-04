#ifndef _NODE_H_
#define _NODE_H_

template <typename T>
class Node
{
    private:
        int key;
        T content;
        Node<T> *left;
        Node<T> *right;
        int height;

    public: 
        Node(const int & d = int(), const T & c = T(), Node *p = nullptr, Node *n = nullptr, int a = int());

        ////////////////////////////////
        //  [I] GETTERS  AND SETTERS  //
        ///////////////////////////////

        int getKey();
        void setKey(int key);
        T getContent();
        void setContent(T content);
        Node<T>* getLeft();
        void setLeft(Node<T>* left);
        Node<T>* getRight();
        void setRight(Node<T>* right);
        int getHeight();
        void setHeight(int height);

};

#include "node.inl"

#endif 