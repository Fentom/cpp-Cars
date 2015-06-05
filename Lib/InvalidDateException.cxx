#include "InvalidDateException.h"

using namespace std;

InvalidDateException::InvalidDateException()
{
	_message = NULL;
	setMessage("ERREUR: Message par defaut");
}
InvalidDateException::InvalidDateException(const char * msg)
{
	_message = NULL;

	setMessage(msg);
}
InvalidDateException::~InvalidDateException()
{
	if(_message != NULL)
		delete [] _message;
}

void InvalidDateException::setMessage(const char * msg)
{
	if(_message != NULL)
		delete [] _message;

	_message = new char[strlen(msg)+1];
	strcpy(_message, msg);
}
const char * InvalidDateException::getMessage() const
{
	return _message;
}
