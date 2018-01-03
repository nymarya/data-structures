#include "BST.h"
#include <cassert>
int main()
{
	ls::BinarySearchTree<int> bst;

	//Test insert
	bst.insert(50, 50);
	bst.insert(35, 35);
	bst.insert(70, 70);
	bst.insert(25, 25);
	bst.insert(65, 65);
	bst.insert(90, 90);
	bst.insert(40, 40);
	bst.insert(80, 80);
	bst.insert(30, 30);

	int i =0;
	bst.calculateHeight(bst.search(50, i));

	//Test traversals
	bst.level_traversal();
	std::cout << std::endl;

	bst.pre_order();

	//test successor
	auto suc = bst.successor(new Node<int>(30, 30, nullptr, nullptr, 0));
	assert(suc->getKey() == 35);

	suc = bst.successor(new Node<int>(50, 50, nullptr, nullptr, 0));
	assert(suc->getKey() == 65);

	//test predecessor
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

	// remove node with 1 child
	f=0;
	node = bst.search(30, f);
	assert(node->getKey() == 30);

	prec = bst.predecessor(node);
	assert(prec->getKey() == 25);

	bst.remove(prec);
	f=0;
	node = bst.search(30, f);
	assert(node->getKey() == 30);

	prec = bst.predecessor(node);
	assert(prec->getKey() == 30 );

	//remove node with 2 children
	f=0;
	node = bst.search(70, f);
	assert(node->getKey() == 70);

	bst.remove(node);

	f= 0;
	node = bst.search(65, f);
	suc = bst.successor(node);
	assert(suc->getKey() ==  80);

	bst.calculateHeight(bst.getRoot());
	bst.pre_order();

	// remove node chidless
	f=0;
	node = bst.search(80, f);
	assert(node->getKey() == 80);

	bst.remove(node);
	f=0;
	node = bst.search(80, f);
	assert(f != 1);

	f= 0;
	node = bst.search(90, f);
	assert(node->getKey() ==  90);
	
	prec = bst.predecessor(node);
	assert(prec->getKey() ==  65);

	bst.calculateHeight(bst.getRoot());
	bst.pre_order();

	std::vector<int> els = {50, 30, 90, 80, 70, 60, 65, 35, 40, 25, 100, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19};

	ls::BinarySearchTree<int> nBST(els);
	auto n = nBST.getMaxHeight();
	assert(n == 5);


	std::cout << "\n \nOK ;)" << std::endl;
}