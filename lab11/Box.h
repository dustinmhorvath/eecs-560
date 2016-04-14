/**
*	@file : Box.h
*	@author :  Dustin Horvath
*	@date : 9/15/14
*	Purpose: Header file of Box Class
*/

#ifndef BOX_H
#define BOX_H

#include <iostream>
#include <string>

class Box{
public:
	/*
	 * @pre None
	 * @post Builds a box object with initial values
	 * @return none
	 */
	Box();

	/*
	 * @pre Box object
	 * @post Sets m_value to integer argument
	 * @return none
	 */
	void setValue(int val);

	/*
	 * @pre Box object
	 * @post Returns the m_value stored inside the box
	 * @return m_value from inside Box
	 */
	int getValue();

	/*
	 * @pre Box object
	 * @post Makes m_previous point to the argument pointer
	 * @return none
	 */
	void setPrevious(Box* prev);

	/*
	 * @pre Box object
	 * @post Returns Box* pointer m_previous
	 * @return Box* pointer to next Box down the stack
	 */
	Box* getPrevious();
private:
	int m_value;
	Box* m_previous;
};



#endif /* BOX_H_ */
