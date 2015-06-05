#include "InvalidPasswordException.h"

#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <sstream>

using namespace std;

InvalidPasswordException::InvalidPasswordException()
{
	setNombre(0);
}
InvalidPasswordException::InvalidPasswordException(const int nbr)
{
	setNombre(nbr);
}
InvalidPasswordException::~InvalidPasswordException()
{

}

void InvalidPasswordException::setNombre(const int nbr)
{
	_nbr = nbr;
}
const int InvalidPasswordException::getNombre() const
{
	return _nbr;
}
