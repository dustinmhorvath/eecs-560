/**
*	@file : LinkedList.h
*	@author :  Dustin Horvath
*	@date : 1/27/16
*	Purpose: Header file of LinkedList Class
*/

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "Node.h"

class LinkedList{
private:
	Node* m_top;
	int m_size;
public:
	/*
	 * @pre Node class required
	 * @post Creates a LinkedList object with initial values
	 * @return none
	 */
	LinkedList();
	/*
	 * @pre LinkedList exists
	 * @post Deconstructs all nodes on the stack of nodes
	 * @return none
	 */
	~LinkedList();

	/*
	 * @pre LinkedList object
	 * @post none
	 * @return true if stack is empty.
	 */
	bool isEmpty() const;

	/*
	 * @pre LinkedList object
	 * @post Returns the size of the stack
	 * @return Size of stack
	 */
	int size() const;

	/*
	 * @pre LinkedList object
	 * @post Creates a Node object. Sets m_previous to point to the next Node down,
	 * then sets m_top to point to itself (the new top-of-stack)
	 * @return none
	 */
	void add(int value);

	/*
	 * @pre LinkedList object
	 * @post Deletes the top Node, sets m_top pointer, and gives the m_value from the top Node.
	 * @return Returns the m_value from the top Node.
	 */
	int drop();

	/*
	 * @pre LinkedList object
	 * @post Prints the values of all the nodes in the list.
	 * @return none.
	 */
	void printList();

	/*
	 * @pre LinkedList object
	 * @post Reverses the order of the list in place.
	 * @return none.
	 */
	void reverseList();

	int tempVal;
	Node* m_tempPtr;
};



#endif /* LINKEDLIST_H_ */
