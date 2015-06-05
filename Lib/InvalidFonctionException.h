#ifndef INVALID_FONCTION_EXCEPTION_H
#define INVALID_FONCTION_EXCEPTION_H

#include <iostream>

using namespace std;

class InvalidFonctionException
{
	private:
		char * _message;
	public:
		InvalidFonctionException();
		InvalidFonctionException(const char * msg);
		~InvalidFonctionException();

		void setMessage(const char * msg);
		const char * getMessage() const;
};

#endif // INVALID_FONCTION_EXCEPTION_H
