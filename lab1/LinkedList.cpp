/**
*	@file : LinkedList.cpp
*	@author :  Dustin Horvath
*	@date : 1/27/16
*	Purpose: Implementation of LinkedList Class
*/


#include <iostream>
#include <string>
#include "LinkedList.h"
#include "Node.h"

LinkedList::LinkedList(){
	m_top = nullptr;
	m_size = 0;
	m_tempPtr = nullptr;
	tempVal = 0;
}

LinkedList::~LinkedList(){
	while(m_top != nullptr){
		drop();
	}
}

bool LinkedList::isEmpty() const{
	if(m_size == 0){
		return true;
	}
	else return false;
}

int LinkedList::size() const{
	return m_size;
}

void LinkedList::add(int value){
	if(m_top == nullptr){
		m_top = new Node();
		m_top -> Node::setValue(value);
		m_top -> Node::setNext(nullptr);
	}
	else {
		m_tempPtr = m_top;
		while( m_tempPtr -> Node::getNext() != nullptr){
			m_tempPtr = m_tempPtr -> Node::getNext();
		}
		m_tempPtr -> Node::setNext(new Node());
		m_tempPtr -> Node::getNext() -> Node::setValue(value);
		m_tempPtr -> Node::getNext() -> Node::setNext(nullptr);
	}
	m_size = m_size + 1;
}

int LinkedList::drop(){
	if(m_top != nullptr){
		tempVal = m_top -> Node::getValue();
		m_tempPtr = m_top -> Node::getNext();
		delete m_top;
		m_top = m_tempPtr;
		m_size = m_size - 1;
		return tempVal;
	}
	else return -1111;
}

void LinkedList::printList(){
	m_tempPtr = m_top;
	while(m_tempPtr != nullptr){
		std::cout << m_tempPtr -> Node::getValue() << " ";
		m_tempPtr =  m_tempPtr -> Node::getNext();
	}
	std::cout << std::endl;
}

void LinkedList::reverseList(){
	Node* prev = nullptr;
	Node* current = m_top;

	while (current != nullptr){
		Node* temp = current -> Node::getNext();
		current -> Node::setNext(prev);
		prev = current;
		current = temp;
	}
	m_top = prev;

}
