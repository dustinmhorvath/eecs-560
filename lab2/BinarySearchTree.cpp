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
	add(value, m_root);
}

void BinarySearchTree::printTree(){
	printTree(m_root);
}

void BinarySearchTree::printTree(Node* subTree){
	while(subTree != nullptr){
		std::cout << subTree -> getValue();
		printTree(subTree -> getLeft());
		printTree(subTree -> getRight());
	}
}

Node* BinarySearchTree::search(int value){
	return search(value, m_root);
}

void BinarySearchTree::add(int value, Node* subtree){
	if(subtree == nullptr){
		subtree = new Node();
		subtree -> setValue(value);
	}
	else if(value < subtree -> getValue()){
		add(value, subtree -> getLeft());
	}
	else if(value > subtree -> getValue()){
		add(value, subtree -> getRight());
	}
	else{
		std::cout << "Error. There is no room to add the value." << std::endl;
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

Node* BinarySearchTree::search(int value, Node* subtree){
	if(subtree == nullptr){
		std:: cout << "The value is not in the tree." << std::endl;
		return subtree;
	}
	if(subtree -> getValue() == value){
		return subtree;
	}
	else if(value < subtree -> getValue()){
		search(value, subtree -> getLeft());
	}
	else if(value > subtree -> getValue()){
		search(value, subtree -> getRight());
	}
}
