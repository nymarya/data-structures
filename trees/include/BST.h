#ifndef _BSTH_
#define _BSTH_


#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include "node.h"

namespace ls {

    template<typename T>
    class BinarySearchTree
    {

        private:
            Node<T> * root;

            using nodeIterator = std::vector<int>::iterator;
            void insertFromArray(nodeIterator first, nodeIterator last);

            void altura(Node<T> * p);

        public:

            

            BinarySearchTree();

            BinarySearchTree(std::vector<int>& newEls);

            /**
            * 
            */
            void insert(int key, int value);

            /**
            * 
            * @param rt Root of the tre.
            * @param k Key to be searched.
            * @param f Variable that keeps information about the search result.
            * 			If f=0, the tree is empty.
            *			If f=1, the key was found and 'pt' points to the Node<T> where 
            *          the key is.
            *          If f=2, the key wasn't found and 'pt' points to the Node<T> without
            *        	the left child.
            *          If f=3, the key wasn't found and 'pt' points to the Node<T> without
            *          the right child.
            */
            Node<T> *search(int k, int &f);

            Node<T> *successor(Node<T> *rt);

            Node<T> * predecessor(Node<T> *pt );

            void level_trasversal();

            void pre_ordem_itr();

            void calculaAltura(Node<T> *pt );

            
            Node<T> * getRoot();

            /**
            * Get max height of the tree.
            * @return Height of the root.
            */
            int getMaxHeight( );

            void remove(Node<T> * pt);
    };

}

#include "BST.inl"

#endif
