#ifndef _NODE_H_
#define _NODE_H_

template <typename T>
class Node
{
    private:
        int key; //<! Key of the node
        T content; //<! Value of the node
        Node<T> *left; //<! Left child
        Node<T> *right; //<! Right child
        int height; //<! Height of the node

    public: 

        /**
         * Default constructor.
         * @param d Key
         * @param c Content
         * @param p Left child
         * @param n Right child
         * @param a Height
         */
        Node(const int & d = int(), const T & c = T(), Node *p = nullptr, Node *n = nullptr, int a = int());

        ////////////////////////////////
        //  [I] GETTERS  AND SETTERS  //
        ///////////////////////////////

        /**
         * Return key of the node.
         * @return Key
         */
        int getKey();

        /**
         * Update key.
         * @param key New key
         */
        void setKey(int key);
        
        /**
         * Return content of the node.
         * @return Content.
         */
        T getContent();
        
        /**
         * Update content.
         * @param content New content
         */
        void setContent(T content);
        
        /**
         * Return left child of the node.
         * @return Left subtree.
         */
        Node<T>* getLeft();

        /**
         * Update left child.
         * @param left New left subtree
         */
        void setLeft(Node<T>* left);

        /**
         * Return right child of the node.
         * @return Right subtree.
         */
        Node<T>* getRight();

        /**
         * Update right child.
         * @param right New right subtree
         */
        void setRight(Node<T>* right);

        /**
         * Return height of the node.
         * @return Height.
         */
        int getHeight();

        /**
         * Update height.
         * @param height New height
         */
        void setHeight(int height);

};

#include "node.inl"

#endif 