# Binary Search Trees

## About

The class ```BinarySearchTree``` implements the abstract data type (ATD) binary search tree. The left child of a node has a key lower than its parent and any right child of a node has a key higher than its parent. This attribute guarantees that the search operation has complexity O(logn), where `n` is the number of nodes at the tree.

#### Performance

| Main operations  | Perfomance     |
| :------------- |:-------------| 
| Search(key) | O( logn ) | 
| Remove(key) | O( height(node) ) | 
| Insert(key) | O( logn ) | 
| Sucessor(key) | O( height(node) )   | 
| Predecessor(key) | O( height(node) ) | 

Here `n` stands for the number of node at the tree.

## How to run

| #       | Description          | Command  |
| :------------- |:-------------| :-----|
| 1      | Compile | ```$ make``` |
| 2      | Run   | ```$ ../build/drive_bst``` |

## How to use

1º Copy files .h e .inl from directory ```include/```<br/>
2º Include file .h in your code.<br/>
3º Instanciate the class with the namespace ```ls``` and the type of the elements between ```<>```

### Example
```cpp
#include "BST.h"

int main() {
    
    ls::BinarySearchTree<int> bst;

    //insert
    bst.insert(50, 50);
    bst.insert(35, 35);
    bst.insert(70, 70);
    bst.insert(25, 25);
    bst.insert(65, 65);
    bst.insert(90, 90);
    bst.insert(40, 40);
    bst.insert(80, 80);
    bst.insert(30, 30);

    //traversal
    bst.level_traversal();
    std::cout << std::endl;

    // successor
    auto suc = bst.successor(new Node<int>(30, 30, nullptr, nullptr, 0));
    assert(suc->getKey() == 35);

    suc = bst.successor(new Node<int>(50, 50, nullptr, nullptr, 0));
    assert(suc->getKey() == 65);

    // predecessor
    int f = 0;
    auto node = bst.search(35, f);
    assert(node->getKey() == 35);

    auto prec = bst.predecessor(node);
    assert(prec->getKey() == 30);

    f=0;
    node = bst.search(40, f);
    assert(node->getKey() == 40);

    prec = bst.predecessor(node);
    assert(prec->getKey() == 35);

    f=0;
    node = bst.search(50, f);
    assert(node->getKey() == 50);

    prec = bst.predecessor(node);
    assert(prec->getKey() == 40);

    f=0;
    node = bst.search(30, f);
    assert(node->getKey() == 30);

    prec = bst.predecessor(node);
    assert(prec->getKey() == 25);

    bst.remove(prec);
    bst.level_traversal();
    

    return 0;
}
```

The output would be:
```
50 35 70 25 40 65 90 30 80
50 35 70 30 40 65 90 80
```


## Autorship

Developed by Mayra Dantas de Azevedo (<mayradazevedo@ufrn.edu.br >), 2017.2

&copy; IMD/UFRN 2017.
