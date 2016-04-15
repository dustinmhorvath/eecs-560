/**
*	@file : StackOfBoxes.cpp
*	@author :  Dustin Horvath
*	@date : 9/15/14
*	Purpose: Implementation of StackOfBoxes Class
*/


#include <iostream>
#include <string>
#include "StackOfBoxes.h"
#include "Box.h"

StackOfBoxes::StackOfBoxes(){
	m_top = nullptr;
	m_size = 0;
	m_tempPtr = nullptr;
	tempVal = 0;
}

StackOfBoxes::~StackOfBoxes(){
	while(m_top != nullptr){
		pop();
	}
}

bool StackOfBoxes::isEmpty() const{
	if(m_size == 0){
		return true;
	}
	else return false;
}

int StackOfBoxes::size() const{
	return m_size;
}

void StackOfBoxes::push(int value){
	m_tempPtr = m_top;
	m_top = new Box();
	m_top -> Box::setValue(value);
	m_top -> Box::setPrevious(m_tempPtr);
	m_size = m_size + 1;
}

bool StackOfBoxes::search(int value){
  if(m_top == nullptr){
    return false;
  }
  Box* current = m_top;
  while(current != nullptr){
    if(current -> Box::getValue() == value){
      return true;
    }
    current = current -> Box::getPrevious();
  }
  return false;

}

int StackOfBoxes::pop(){
	if(m_top != nullptr){
		tempVal = m_top -> Box::getValue();
		m_tempPtr = m_top -> Box::getPrevious();
		delete m_top;
		m_top = m_tempPtr;
		m_size = m_size - 1;
		return tempVal;
	}
	else return -1111;
}
