#ifndef INVALID_RISTOURNE_EXCEPTION_H
#define INVALID_RISTOURNE_EXCEPTION_H

#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <sstream>

using namespace std;

class InvalidRistourneException
{
	private:
		char * _message;
	public:
		InvalidRistourneException();
		InvalidRistourneException(const char * msg);
		~InvalidRistourneException();

		void setMessage(const char * msg);
		const char * getMessage() const;
};

#endif // INVALID_RISTOURNE_EXCEPTION_H
