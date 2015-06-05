#include "InvalidFonctionException.h"

#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <sstream>

using namespace std;


InvalidFonctionException::InvalidFonctionException()
{
	_message = NULL;
	setMessage("ERREUR: Message par defaut");
}
InvalidFonctionException::InvalidFonctionException(const char * msg)
{
	_message = NULL;

	setMessage(msg);
}
InvalidFonctionException::~InvalidFonctionException()
{
	if(_message != NULL)
		delete [] _message;
}

void InvalidFonctionException::setMessage(const char * msg)
{
	if(_message != NULL)
		delete [] _message;

	_message = new char[strlen(msg)+1];
	strcpy(_message, msg);
}
const char * InvalidFonctionException::getMessage() const
{
	return _message;
}
