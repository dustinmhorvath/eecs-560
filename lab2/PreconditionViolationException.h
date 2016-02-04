/*
/Dustin Horvath
/10/6/14
/PreconditionViolationException header file
/Custom exception handler that throws error messages
*/


#include <iostream>
#include <string>
#include <stdexcept>

#ifndef PRECONDITIONVIOLATIONEXCEPTION_H
#define PRECONDITIONVIOLATIONEXCEPTION_H

class PreconditionViolationException : public std::runtime_error{
public:
	/*
	/@pre none
	/@post makes a Preconditionviolationexception
	/@return none
	*/
	PreconditionViolationException(const char* message);
};

#endif
