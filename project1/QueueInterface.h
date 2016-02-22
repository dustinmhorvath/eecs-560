/*
/Dustin Horvath
/10/6/2014
/QueueInterface header file
/-pure virtual class used for stack implementation.
*/

#include <iostream>
#include <string>
#include "PreconditionViolationException.h"

#ifndef QUEUEINTERFACE_H
#define QUEUEINTERFACE_H

template <typename T>
class QueueInterface{
public:
	/*
	/All of the methods in this pure virtual class are not implemented,
	/and so cannot be usefully described here, other than to say that
	/their purpose is for a version of stack implementation that supports
	/changing stack elements easily from either end.
	*/
	virtual ~QueueInterface(){ };
	virtual bool isEmpty() const = 0;
	virtual void enqueue(const T newEntry) = 0;
	virtual void dequeue() throw(PreconditionViolationException) = 0;
	virtual T peekFront() const throw(PreconditionViolationException) = 0;
	virtual int size() const = 0;
	virtual bool operator < (const QueueInterface<T>& rhs) const = 0;
	virtual bool operator > (const QueueInterface<T>& rhs) const = 0;
	virtual bool operator >= (const QueueInterface<T>& rhs) const = 0;
	virtual bool operator <= (const QueueInterface<T>& rhs) const = 0;
	virtual bool operator == (const QueueInterface<T>& rhs) const = 0;
	virtual bool operator != (const QueueInterface<T>& rhs) const = 0;

	int m_length;
};

#endif
