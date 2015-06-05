#ifndef INVALID_PASSWORD_EXCEPTION_H
#define INVALID_PASSWORD_EXCEPTION_H

#include <iostream>

using namespace std;

class InvalidPasswordException
{
	private:
		int _nbr;
	public:
		InvalidPasswordException();
		InvalidPasswordException(const int nbr);
		~InvalidPasswordException();

		void setNombre(const int nbr);
		const int getNombre() const;
};

#endif // INVALID_PASSWORD_EXCEPTION_H
