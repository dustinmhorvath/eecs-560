/**
*	@file : StackOfBoxes.h
*	@author :  Dustin Horvath
*	@date : 9/15/14
*	Purpose: Header file of StackOfBoxes Class
*/

#ifndef STACKOFBOXES_H_
#define STACKOFBOXES_H_

#include "Box.h"

class StackOfBoxes{
private:
	Box* m_top;
	int m_size;
public:
	/*
	 * @pre Box class required
	 * @post Creates a StackOfBoxes object with initial values
	 * @return none
	 */
	StackOfBoxes();
	/*
	 * @pre StackOfBoxes exists
	 * @post Deconstructs all boxes on the stack of boxes
	 * @return none
	 */
	~StackOfBoxes();

	/*
	 * @pre StackOfBoxes object
	 * @post none
	 * @return true if stack is empty.
	 */
	bool isEmpty() const;

	/*
	 * @pre StackOfBoxes object
	 * @post Returns the size of the stack
	 * @return Size of stack
	 */
	int size() const;

	/*
	 * @pre StackOfBoxes object
	 * @post Creates a box object. Sets m_previous to point to the next box down,
	 * then sets m_top to point to itself (the new top-of-stack)
	 * @return none
	 */
	void push(int value);

	/*
	 * @pre StackofBoxes object WITH BOX (does not have try-catch)
	 * @post Deletes the top box, sets m_top pointer, and gives the m_value from the top box.
	 * @return Returns the m_value from the top box.
	 */
	int pop();

  bool search(int value);

	int tempVal;
	Box* m_tempPtr;
};



#endif /* STACKOFBOXES_H_ */
