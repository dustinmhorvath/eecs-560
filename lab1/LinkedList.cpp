/**
*	@file : LinkedList.cpp
*	@author :  Dustin Horvath
*	@date : 1/27/16
*	Purpose: Implementation of LinkedList Class
*/


#include <iostream>
#include <string>
#include "LinkedList.h"
#include "Box.h"

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
	std::cout << value  << std::endl;

	if(m_top == nullptr){
		m_top -> Box::setNext(new Box());
		m_top -> Box::setValue(value);
	}
	else {
		m_tempPtr = m_top -> Box::getNext();
		while(m_tempPtr){
			if(m_tempPtr -> Box::getNext()){
				m_tempPtr = m_tempPtr -> Box::getNext();
			}
		}
		m_tempPtr -> Box::setNext(new Box());
		m_tempPtr -> Box::getNext() -> Box::setValue(value);
	}
}

int LinkedList::drop(){
	if(m_top != nullptr){
		tempVal = m_top -> Box::getValue();
		m_tempPtr = m_top -> Box::getNext();
		delete m_top;
		m_top = m_tempPtr;
		m_size = m_size - 1;
		return tempVal;
	}
	else return -1111;
}

void LinkedList::printList(){
	m_tempPtr = m_top;
	while(m_tempPtr){
		std::cout << m_tempPtr -> Box::getValue() << std::endl;
		m_tempPtr =  m_tempPtr -> Box::getNext();
	}
}
