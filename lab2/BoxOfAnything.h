/*
 * BoxOfAnything.h
 *
 *  Created on: Sep 15, 2014
 *      Author: dhorvath
 */


#ifndef BOXOFANYTHING_H
#define BOXOFANYTHING_H

template <typename T>
class BoxOfAnything{
	private:
		BoxOfAnything<T>* m_previous;
		T m_value;

	public:
		/*
		 * @pre none.
		 * @post Creates a BoxOfAnything<T> object and sets initial values.
		 * @return none.
		 */
		BoxOfAnything(T value);

		/*
		 * @pre requires BoxOfAnything<T> object.
		 * @post none.
		 * @return returns m_value of type T.
		 */
		T getValue();

		/*
		 * @pre requires BoxOfAnything<T> object.
		 * @post sets m_value to value.
		 * @return none.
		 */
		void setValue(T value);

		/*
		 * @pre requires BoxOfAnything<T> object.
		 * @post none.
		 * @return gives back a BoxOfAnything<T>* pointer to the previous Box on the stack.
		 */
		BoxOfAnything<T>* getPrevious();

		/*
		 * @pre requires BoxOfAnything<T> object.
		 * @post Sets the m_previous pointer to the previous box on the stack.
		 * @return none.
		 */
		void setPrevious(BoxOfAnything<T>* previous);

};

#include "BoxOfAnything.hpp"

#endif
