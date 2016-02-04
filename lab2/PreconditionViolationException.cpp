/*
/Dustin Horvath
/10/6/14
/PreconditionViolationException class implementation
/Contains methods for throwing customized exceptions
*/

#include "PreconditionViolationException.h"
#include <stdexcept>

PreconditionViolationException::PreconditionViolationException(const char* message) : std::runtime_error(message)
{

}
