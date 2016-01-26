/**
*	@file : Box.cpp
*	@author :  Dustin Horvath
*	@date : 1/27/16
*	Purpose: Implementation file of Box Class
*/

#include <iostream>
#include <string>
#include "Box.h"

Box::Box(){
	setValue(0);
	m_next = nullptr;
}

void Box::setValue(int val){
	m_value = val;
}

int Box::getValue(){
	return m_value;
}

void Box::setNext(Box* next){
	m_next = next;
}

Box* Box::getNext(){
	return m_next;
}

