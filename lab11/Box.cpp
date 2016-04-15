/**
*	@file : Box.cpp
*	@author :  Dustin Horvath
*	@date : 9/15/14
*	Purpose: Implementation file of Box Class
*/

#include <iostream>
#include <string>
#include "Box.h"

Box::Box(){
	setValue(0);
	m_previous = nullptr;
}

void Box::setValue(int val){
	m_value = val;
}

int Box::getValue(){
	return m_value;
}

void Box::setPrevious(Box* prev){
	m_previous = prev;
}

Box* Box::getPrevious(){
	return m_previous;
}

