#include "Node.h"


#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

class BinarySearchTree{
public:
	BinarySearchTree();
	~BinarySearchTree();
	void add(int value);
	void printTree();
	void printTree(Node* subTree);
	Node* search(int value);

private:
	Node* add(int value, Node* subtree);
	void deleteTree(Node* subTree);
	Node* search(int value, Node* subtree);


	Node* m_root;

};



#endif
