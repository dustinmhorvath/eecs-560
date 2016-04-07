/**
*	@file : Node.h
*	@author :  Dustin Horvath
*	@date : 1/27/16
*	Purpose: Header file of Node Class
*/

#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>

class Node{
public:
	/*
	 * @pre None
	 * @post Builds a Node object with initial values
	 * @return none
	 */
	Node();

	/*
	 * @pre Node object
	 * @post Sets m_value to integer argument
	 * @return none
	 */
	void setValue(int val);

	/*
	 * @pre Node object
	 * @post Returns the m_value stored inside the Node
	 * @return m_value from inside Node
	 */
	int getValue();

	/*
	 * @pre Node object
	 * @post Makes m_next point to the argument pointer
	 * @return none
	 */
	void setNext(Node* next);

	/*
	 * @pre Node object
	 * @post Returns Node* pointer m_previous
	 * @return Node* pointer to next Node down the list
	 */
	Node* getNext();
private:
	int m_value;
	Node* m_next;
};



#endif /* NODE_H_ */
