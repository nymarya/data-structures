#ifndef _BSTH
#define _BSTH_


#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>

namespace ls {

    template<typename T>
    class BinarySearchTree
    {

        public:
            struct Node
            {
                int key;
                T content;
                Node *left;
                Node *right;
                int height;
                /*! \brief Construtor simples para o nó. */
                Node(const int & d = int(), const T & c = T(), Node *p = nullptr, Node *n = nullptr, int a = int())
                : key(d), content(c), left(p), right(n), height(a) { /* Empty */}
            };

        private:

            Node * root;

            using nodeIterator = std::vector<int>::iterator;
            void insertFromArray(nodeIterator first, nodeIterator last);

            void altura(Node * p);

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
            *			If f=1, the key was found and 'pt' points to the node where 
            *          the key is.
            *          If f=2, the key wasn't found and 'pt' points to the node without
            *        	the left child.
            *          If f=3, the key wasn't found and 'pt' points to the node without
            *          the right child.
            */
            Node *search(int k, int &f);

            Node *successor(Node *rt);

            Node * predecessor(Node *pt );

            void level_trasversal();

            void pre_ordem_itr();

            void calculaAltura(Node *pt );

            
            Node * getRoot();

            /**
            * Get max height of the tree.
            * @return Height of the root.
            */
            int getMaxHeight( );

            void remove(Node * pt);
    };

}

#include "BST.inl"

#endif
