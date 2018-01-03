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
            Node<T> * root; //<! Root of the tree

            using nodeIterator = std::vector<int>::iterator;

            /**
             * Insert elements from given array at the tree.
             * @param first Iterator pointing to the first element of the range.
             * @param first Iterator pointing to the last element of the range.
             */
            void insertFromArray(nodeIterator first, nodeIterator last);

            /**
             * Update height of given node.
             * @param p Node.
             */
            void height(Node<T> * p);

        public:

            
            /**
             * Default constructor.
             */
            BinarySearchTree();

            /**
             * Construct tree from vector of keys.
             * @param newEls Vector of keys.
             */
            BinarySearchTree(std::vector<int>& newEls);

            /**
             * Insert new node at the tree.
             * @param key Key of the new node.
             * @param value Content of the new node.
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

            /**
             * Return the successor of the param node.
             * @param pt Node.
             * @return Successor of 'pt'.
             */
            Node<T> *successor(Node<T> *rt);

            /**
             * Return the predecessor of the param node.
             * @param pt Node.
             * @return Predecessor of 'pt'.
             */
            Node<T> * predecessor(Node<T> *pt );

            /**
             * Level traversal the tree iteratively.
             */
            void level_traversal();

            /**
             * Pre order traversal the tree iteratively.
             */
            void pre_order_itr();

            /**
             * Calculate height of the nodes at the tree.
             * @param pt Root from the tree.
             */
            void calculateHieght(Node<T> *pt );

            /**
             * Return root of tree.
             * @return Root node.
             */
            Node<T> * getRoot();

            /**
             * Get max height of the tree.
             * @return Height of the root.
             */
            int getMaxHeight( );

            /**
             * Remove node from tree.
             * @param pt Node to be removed.
             */
            void remove(Node<T> * pt);
    };

}

#include "BST.inl"

#endif
