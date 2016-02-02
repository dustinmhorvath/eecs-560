#include <iostream>
#include "Node.h"
#include "BinarySearchTree.h"

BinarySearchTree::BinarySearchTree(){
	m_root = nullptr;
}

BinarySearchTree::~BinarySearchTree(){
	deleteTree(m_root);
}

void BinarySearchTree::add(int value){
	Node* temp = add(value, m_root);
	temp = new Node();
	temp -> setValue(value);
}

Node* BinarySearchTree::add(int value, Node* subtree){
	if(subtree == nullptr){
		return subtree;
	}
	else if(value < subtree -> getValue()){
		return(add(value, subtree -> getLeft()));
	}
	else if(value > subtree -> getValue()){
		return(add(value, subtree -> getRight()));
	}
	else{
		std::cout << "Error. There is no room to add the value." << std::endl;

	}
}

void BinarySearchTree::printTree(){
	printTree(m_root);
}

void BinarySearchTree::printTree(Node* subTree){
	if(subTree != nullptr){
		std::cout << subTree -> getValue();
		printTree(subTree -> getLeft());
		printTree(subTree -> getRight());
	}
}

void BinarySearchTree::deleteTree(Node* subTree){
	if(subTree != nullptr){
		if(subTree -> getLeft() != nullptr){
			deleteTree(subTree -> getLeft());
		}
		if(subTree -> getRight() != nullptr){
			deleteTree(subTree -> getRight());
		}
		delete m_root;
	}
}

Node* BinarySearchTree::search(int value){
	return search(value, m_root);
}

Node* BinarySearchTree::search(int value, Node* subtree){
	if(subtree == nullptr){
		std::cout << "The value is not in the tree." << std::endl;
		return subtree;
	}
	if(subtree -> getValue() == value){
		std::cout << "Found value " << value << std::endl;
		return subtree;
	}
	if(value < subtree -> getValue()){
		search(value, subtree -> getLeft());
	}
	if(value > subtree -> getValue()){
		search(value, subtree -> getRight());
	}
}
