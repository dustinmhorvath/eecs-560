/*
/Dustin Horvath
/10/6/14
/Queue header file
/Used for implementating a stack, inherits from Queueinterface
*/


#include <iostream>
#include <string>
#include "BoxOfAnything.h"
#include "QueueInterface.h"

#ifndef QUEUE_H
#define QUEUE_H

template <typename T>
class Queue : public QueueInterface<T>{
public:
	/*
	/@pre none
	/@post makes a queue object
	/@return none
	*/
	Queue();

	/*
	/@pre Requires a queue
	/@post Empties the queue, then deletes the queue
	/@return none
	*/
	~Queue();

	/*
	/@pre requires queue object
	/@post none
	/@returns a bool whether the queue has objects in it or not
	*/
	bool isEmpty() const;

	/*
	/@pre requires queue object
	/@post creates a new boxofanything object in the queue with newentry value in it. Takes care of pointers throughout.
	/@return none
	*/
	void enqueue(const T newEntry);

	/*
	/@pre Requires queue object with object in it
	/@post deletes the front object, and returns the value stored in it
	/@returns none
	*/
	void dequeue() throw(PreconditionViolationException);

	/*
	/@pre requires queue object with something in it
	/@post none
	/@return gives back the value stored in the front object of the queue
	*/
	T peekFront() const throw(PreconditionViolationException);

	/*
	/@pre requires queue object
	/@post none
	/@return gives back the length of the queue
	*/
	int size() const;

	/*
	/@pre requires queue object
	/@post none
	/@returns bool if instance object length element is less than argument object length
	*/
	bool operator < (const QueueInterface<T>& rhs) const;

	/*
	/@pre requires queue object
	/@post none
	/@returns bool if instance object length element is greater than argument object length
	*/
	bool operator > (const QueueInterface<T>& rhs) const;

	/*
	/@pre requires queue object
	/@post none
	/@returns bool if instance object length element is greater than or equal to argument object length
	*/
	bool operator >= (const QueueInterface<T>& rhs) const;

	/*
	/@pre requires queue object
	/@post none
	/@returns bool if instance object length element is less than or equal to argument object length
	*/
	bool operator <= (const QueueInterface<T>& rhs) const;

	/*
	/@pre requires queue object
	/@post none
	/@returns bool if instance object length element is equal to argument object length
	*/
	bool operator == (const QueueInterface<T>& rhs) const;

	/*
	/@pre requires queue object
	/@post none
	/@returns bool if instance object length element is not equal to argument object length
	*/
	bool operator != (const QueueInterface<T>& rhs) const;

	BoxOfAnything<T>* m_front;
	BoxOfAnything<T>* m_back;

	int m_length;
};

#include "Queue.hpp"

#endif
