#include "BST.h"

template <typename T>
void ls::BinarySearchTree<T>::insertFromArray(nodeIterator first, nodeIterator last){
    if(first != last ){
        auto n = std::distance(first, last)/2;
        insert(*(first+n), 0);
        insertFromArray(first, first+n);
        insertFromArray(first+n+1, last);
    }
}

template <typename T>
void ls::BinarySearchTree<T>::altura(Node * p){
    auto aut1 = 1;
    auto aut2 = 1;

    if(p->left != nullptr ){
        aut1 += p->left->height;
    }
    if(p->right != nullptr ){
        aut2 += p->right->height;
    }

    p->height = (aut1 > aut2)? aut1 : aut2;
}

template <typename T>
ls::BinarySearchTree<T>::BinarySearchTree()
{
    root = nullptr;
}

template <typename T>
ls::BinarySearchTree<T>BinarySearchTree(std::vector<int>& newEls){
    root = nullptr;
    std::sort(newEls.begin(), newEls.end());
    insertFromArray(newEls.begin(), newEls.end());
}

/**
* 
*/
template <typename T>
void ls::BinarySearchTree<T>::insert(int key, int value)
{
    Node *pt = root;
    int f = 0;
    pt = search(key, f);

    //if key was found, insert failed
    if (f == 1)
    {
        return;
    }
    else
    {
        Node * nNode = new Node(key, value, nullptr, nullptr, 0);
        if (f == 0)
            root = nNode;

        // f == 2 =>left child of 'pt' is empty
        // f== 3 => right child of 'pt' is empty
        if (f == 2)
            pt->left = nNode;
        else if (f == 3)
            pt->right = nNode;
    }
}

/**
* 
* @param rt Root of the tre.
* @param k Key to be searched.
* @param f Variable that keeps information about the search result.
* 			If f=0, the tree is empty.
*			If f=1, the key was found and 'pt' points to the Node where 
*          the key is.
*          If f=2, the key wasn't found and 'pt' points to the Node without
*        	the left child.
*          If f=3, the key wasn't found and 'pt' points to the Node without
*          the right child.
*/
template <typename T>
typename ls::BinarySearchTree<T>::Node * ls::BinarySearchTree<T>::search(int k, int &f)
{
    auto rt(root);
    if (rt != nullptr)
    {
        // f starts with 0
        while (f == 0)
        {
            if (rt->key == k)
                f = 1;
            else
            {
                //Key not found, look at the subtrees

                if (k < rt->key)
                {
                    //Search at left subtree
                    if (rt->left == nullptr)
                        f = 2;
                    else
                    {
                        rt = rt->left;
                    }
                }
                else
                {
                    //Search at right subtree
                    if (rt->right == nullptr)
                    {
                        f = 3;
                    }
                    else
                        rt = rt->right;
                }
            }
        }
    }
    return rt;
}

template <typename T>
typename ls::BinarySearchTree<T>::Node * ls::BinarySearchTree<T>::successor(Node *rt)
{
    auto pt(root);

    std::stack<Node *> ancestrals;

    while (pt != nullptr)
    {
        ancestrals.push(pt);
        if (pt->key == rt->key)
            break;
        else if (rt->key < pt->key)
            pt = pt->left;
        else
            pt = pt->right;
    }

    //if right subtree is not empty, get min value
    if (pt->right != nullptr)
    {
        auto current = pt->right;
        while (current->left != nullptr)
        {
            current = current->left;
        }

        return current;
    }
    //if right subtree is empty, search at parents
    while (!ancestrals.empty())
    {
        auto parent = ancestrals.top();
        ancestrals.pop();

        if (parent->key > rt->key)
            return parent;
    }

    return pt;
}

template <typename T>
typename ls::BinarySearchTree<T>::Node * ls::BinarySearchTree<T>::predecessor(Node *pt ){

    // left subtree is not null, so the predecessor is the max value
    // of this subtree
    if( pt->left != nullptr){
        auto current = pt->left;
        while(current->right != nullptr){
            current = current->right;
        }

        return current;
    }

    //left subtree is empty, so predecessor is the immediate 
    // value smaller than the key at the 'parents path'
    auto aux = root;
    auto min = pt;
    while( aux != nullptr and aux->key != pt->key ){
        if(aux->key < min->key )
            min = aux;
        if( aux->key > pt->key)
            aux = aux->left;
        else if( aux->key < pt->key)
            aux = aux->right;
    }

    return min;
}

template <typename T>
void ls::BinarySearchTree<T>::level_trasversal()
{
    std::queue<Node *> q;
    q.push(root);
    while (!q.empty())
    {
        auto temp = q.front();
        q.pop();

        std::cout << temp->content << " ";

        if (temp->left != nullptr)
            q.push(temp->left);

        if (temp->right != nullptr)
            q.push(temp->right);
    }
}

template <typename T>
void ls::BinarySearchTree<T>::pre_ordem_itr()
{
    std::stack<Node *> s;
    s.push(root);

    while (not s.empty())
    {
        Node *temp = s.top();
        s.pop();
        std::cout << temp->key << "("<< temp->height<<") ";
        if (temp->right != nullptr)
        {
            s.push(temp->right);
        }
        if (temp->left != nullptr)
        {
            s.push(temp->left);
        }
    }

    std::cout << std::endl;
}

/**
 * 
 */
template <typename T>
void ls::BinarySearchTree<T>::calculaAltura(Node *pt )
{
    if(pt->left != nullptr)
        calculaAltura(pt->left);
    if( pt->right != nullptr)
        calculaAltura(pt->right);
    altura(pt);
}

/**
 * Return root of the tree.
 * @return root
 */
template <typename T>
typename ls::BinarySearchTree<T>::Node * ls::BinarySearchTree<T>::getRoot()
{
    return root;
}

/**
* Get max height of the tree.
* @return Height of the root.
*/
template <typename T>
int ls::BinarySearchTree<T>::getMaxHeight()
{
    if(root->height == 0)
        calculaAltura(root);
    return root->height;
}

/**
 *
 */
template <typename T>
void ls::BinarySearchTree<T>::remove(Node * pt)
{
    int f = 0;
    auto current = root;
    auto parent = predecessor(pt);

    while(current->key != pt->key){
        parent = current;
        if(current->key > pt->key){
            current = current->left;
            f = 1;
        } else {
            current = current->right;
            f = 2;
        }
    }

    if(pt->left == nullptr and pt->right == nullptr)
        current = nullptr;

    else if(not(pt->left != nullptr and pt->right != nullptr)){
        if(pt->left != nullptr){
            current = pt->left;
            f = 1;
        }	
        else {
            current = pt->right;
            f=2;
        }
            
    }

    else {
        auto fast = pt->left;
        while( fast != nullptr){
            current = fast;
            fast = fast->right;
        }

    }


    if( f == 1){
        parent->left = current;
    } else {
        parent->right = current;
    }
}
