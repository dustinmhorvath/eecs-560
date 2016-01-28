/**
*	@file : main.cpp
*	@author :  Dustin Horvath
*	@date : 1/27/16
*	Purpose: Implementation of main
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "LinkedList.h"
#include "Box.h"


int main(){
	LinkedList list = LinkedList();

	std::ifstream file("data.txt");
	std::string line;
/*
	while(std::getline(file, line)){
		std::stringstream  lineStream(line);
		int value;
		// Read an integer at a time from the line
		while(lineStream >> value){
			list.add(value);
		}
	}
*/
	list.add(1);
	list.add(2);
	list.add(3);

	list.printList();
//	list.reverseList();
//	list.printList();
}

