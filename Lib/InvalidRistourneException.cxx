#include "InvalidRistourneException.h"

using namespace std;

InvalidRistourneException::InvalidRistourneException()
{
	_message = NULL;
	setMessage("ERREUR: Message par defaut");
}
InvalidRistourneException::InvalidRistourneException(const char * msg)
{
	_message = NULL;

	setMessage(msg);
}
InvalidRistourneException::~InvalidRistourneException()
{
	if(_message != NULL)
		delete [] _message;
}

void InvalidRistourneException::setMessage(const char * msg)
{
	if(_message != NULL)
		delete [] _message;

	_message = new char[strlen(msg)+1];
	strcpy(_message, msg);
}
const char * InvalidRistourneException::getMessage() const
{
	return _message;
}
