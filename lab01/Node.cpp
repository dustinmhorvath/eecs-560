/**
*	@file : Node.cpp
*	@author :  Dustin Horvath
*	@date : 1/27/16
*	Purpose: Implementation file of Node Class
*/

#include <iostream>
#include <string>
#include "Node.h"

Node::Node(){
	setValue(0);
	m_next = nullptr;
}

void Node::setValue(int val){
	m_value = val;
}

int Node::getValue(){
	return m_value;
}

void Node::setNext(Node* next){
	m_next = next;
}

Node* Node::getNext(){
	return m_next;
}

