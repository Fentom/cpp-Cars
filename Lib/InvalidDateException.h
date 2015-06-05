#ifndef INVALID_DATE_EXCEPTION_H
#define INVALID_DATE_EXCEPTION_H

#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <sstream>

using namespace std;

class InvalidDateException
{
	private:
		char * _message;
	public:
		InvalidDateException();
		InvalidDateException(const char * msg);
		~InvalidDateException();

		void setMessage(const char * msg);
		const char * getMessage() const;
};

#endif // INVALID_DATE_EXCEPTION_H
