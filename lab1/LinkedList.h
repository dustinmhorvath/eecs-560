/**
*	@file : LinkedList.h
*	@author :  Dustin Horvath
*	@date : 1/27/16
*	Purpose: Header file of LinkedList Class
*/

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "Box.h"

class LinkedList{
private:
	Box* m_top;
	int m_size;
public:
	/*
	 * @pre Box class required
	 * @post Creates a LinkedList object with initial values
	 * @return none
	 */
	LinkedList();
	/*
	 * @pre LinkedList exists
	 * @post Deconstructs all boxes on the stack of boxes
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
	 * @post Creates a box object. Sets m_previous to point to the next box down,
	 * then sets m_top to point to itself (the new top-of-stack)
	 * @return none
	 */
	void add(int value);

	/*
	 * @pre LinkedList object WITH BOX (does not have try-catch)
	 * @post Deletes the top box, sets m_top pointer, and gives the m_value from the top box.
	 * @return Returns the m_value from the top box.
	 */
	int drop();

	/*
	 * @pre LinkedList object WITH BOX (does not have try-catch)
	 * @post Prints the values of all the boxes in the list.
	 * @return none.
	 */
	void printList();

	int tempVal;
	Box* m_tempPtr;
};



#endif /* LINKEDLIST_H_ */
