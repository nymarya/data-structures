#include "BST.h"

//Insert elements from given array at the tree.
template <typename T>
void ls::BinarySearchTree<T>::insertFromArray(nodeIterator first, nodeIterator last){
    if(first != last ){
        auto n = std::distance(first, last)/2;
        insert(*(first+n), 0);
        insertFromArray(first, first+n);
        insertFromArray(first+n+1, last);
    }
}

// Update height of given node.
template <typename T>
void ls::BinarySearchTree<T>::height(Node<T> * p){
    auto aut1 = 1;
    auto aut2 = 1;

    if(p->getLeft() != nullptr ){
        aut1 += p->getLeft()->getHeight();
    }
    if(p->getRight() != nullptr ){
        aut2 += p->getRight()->getHeight();
    }

    auto height = (aut1 > aut2)? aut1 : aut2;
    p->setHeight(height);
}

// Default constructor.
template <typename T>
ls::BinarySearchTree<T>::BinarySearchTree()
:root(nullptr)
{/*empty*/}

// Construct tree from vector of keys.
template <typename T>
ls::BinarySearchTree<T>::BinarySearchTree(std::vector<int>& newEls)
:root(nullptr)
{
    std::sort(newEls.begin(), newEls.end());
    insertFromArray(newEls.begin(), newEls.end());
}

// Insert new node at the tree.
template <typename T>
void ls::BinarySearchTree<T>::insert(int key, int value)
{
    Node<T> *pt = root;
    int f = 0;
    pt = search(key, f);

    //if key was found, insert failed
    if (f == 1)
    {
        return;
    }
    else
    {
        Node<T> * nNode = new Node<T>(key, value, nullptr, nullptr, 0);
        if (f == 0)
            root = nNode;

        // f == 2 =>left child of 'pt' is empty
        // f== 3 => right child of 'pt' is empty
        if (f == 2)
            pt->setLeft(nNode);
        else if (f == 3)
            pt->setRight(nNode);
    }
}

// Search node at the tree
template <typename T>
Node<T> * ls::BinarySearchTree<T>::search(int k, int &f)
{
    auto rt(root);
    if (rt != nullptr)
    {
        // f starts with 0
        while (f == 0)
        {
            if (rt->getKey() == k)
                f = 1;
            else
            {
                //Key not found, look at the subtrees

                if (k < rt->getKey())
                {
                    //Search at left subtree
                    if (rt->getLeft() == nullptr)
                        f = 2;
                    else
                    {
                        rt = rt->getLeft();
                    }
                }
                else
                {
                    //Search at right subtree
                    if (rt->getRight() == nullptr)
                    {
                        f = 3;
                    }
                    else
                        rt = rt->getRight();
                }
            }
        }
    }
    return rt;
}

// Return the successor of the given node.
template <typename T>
Node<T> * ls::BinarySearchTree<T>::successor(Node<T> *rt)
{
    auto pt(root);

    std::stack<Node<T> *> ancestrals;

    while (pt != nullptr)
    {
        ancestrals.push(pt);
        if (pt->getKey() == rt->getKey())
            break;
        else if (rt->getKey() < pt->getKey())
            pt = pt->getLeft();
        else
            pt = pt->getRight();
    }

    //if right subtree is not empty, get min value
    if (pt->getRight() != nullptr)
    {
        auto current = pt->getRight();
        while (current->getLeft() != nullptr)
        {
            current = current->getLeft();
        }

        return current;
    }
    //if right subtree is empty, search at parents
    while (!ancestrals.empty())
    {
        auto parent = ancestrals.top();
        ancestrals.pop();

        if (parent->getKey() > rt->getKey())
            return parent;
    }

    return pt;
}

// Return the predecessor of the given node.
template <typename T>
Node<T> * ls::BinarySearchTree<T>::predecessor(Node<T> *pt ){

    // left subtree is not null, so the predecessor is the max value
    // of this subtree
    if( pt->getLeft() != nullptr){
        auto current = pt->getLeft();
        while(current->getRight() != nullptr){
            current = current->getRight();
        }

        return current;
    }

    //left subtree is empty, so predecessor is the immediate 
    // value smaller than the key at the 'parents path'
    auto aux = root;
    auto min = pt;
    while( aux != nullptr and aux->getKey() != pt->getKey() ){
        if(aux->getKey() <= pt->getKey())
            min = aux;
        if( aux->getKey() > pt->getKey())
            aux = aux->getLeft();
        else if( aux->getKey() < pt->getKey())
            aux = aux->getRight();
    }

    return min;
}

// Level traversal the tree iteratively.
template <typename T>
void ls::BinarySearchTree<T>::level_traversal(){
    std::queue<Node<T> *> q;
    q.push(root);
    while (!q.empty())
    {
        auto temp = q.front();
        q.pop();

        std::cout << temp->getContent() << " ";

        if (temp->getLeft() != nullptr)
            q.push(temp->getLeft());

        if (temp->getRight() != nullptr)
            q.push(temp->getRight());
    }
}

// Pre order traversal the tree iteratively.
template <typename T>
void ls::BinarySearchTree<T>::pre_order()
{
    std::stack<Node<T> *> s;
    s.push(root);

    while (not s.empty())
    {
        Node<T> *temp = s.top();
        s.pop();
        std::cout << temp->getKey() << "("<< temp->getHeight()<<") ";
        if (temp->getRight() != nullptr)
        {
            s.push(temp->getRight());
        }
        if (temp->getLeft() != nullptr)
        {
            s.push(temp->getLeft());
        }
    }

    std::cout << std::endl;
}

// Calculate height of the nodes at the tree.
template <typename T>
void ls::BinarySearchTree<T>::calculateHeight(Node<T> *pt )
{
    if(pt->getLeft() != nullptr)
        calculateHeight(pt->getLeft());
    if( pt->getRight() != nullptr)
        calculateHeight(pt->getRight());
    height(pt);
}

// Return root of the tree.
template <typename T>
 Node<T> * ls::BinarySearchTree<T>::getRoot()
{
    return root;
}

// Get max height of the tree.
template <typename T>
int ls::BinarySearchTree<T>::getMaxHeight()
{
    if(root->getHeight() == 0)
        calculateHeight(root);
    return root->getHeight();
}

// Remove node from tree.
template <typename T>
void ls::BinarySearchTree<T>::remove(Node<T> * pt)
{
    int f = 0;
    Node<T>* current = root;
    auto parent = predecessor(pt);

    while(current->getKey() != pt->getKey()){
        parent = current;
        if(current->getKey() > pt->getKey()){
            current = current->getLeft();
            f = 1;
        } else {
            current = current->getRight();
            f = 2;
        }
    }

    auto target = current;
    // node has no child
    if(pt->getLeft() == nullptr and pt->getRight() == nullptr){
        current = nullptr;

    } else if(not(pt->getLeft() != nullptr and pt->getRight() != nullptr)){
        // node has one child
        if(pt->getLeft() != nullptr){
            current = pt->getLeft();
        }	
        else {
            current = pt->getRight();
        }  
    } else {
        // node has 2 children
        auto fast = pt->getLeft();

        //get predecessor
        while( fast != nullptr){
            current = fast;
            fast = fast->getRight();
        }
        current->setRight( target->getRight() );
    }

    //free node
    delete target;

    // update parent
    if( f == 1){
        parent->setLeft(current);
    } else {
        parent->setRight(current);
    }
}
