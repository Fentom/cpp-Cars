#ifndef OPTION_H
#define OPTION_H

#include <iostream>

using namespace std;

class Option
{
	friend ostream & operator<< (ostream & flux, const Option & O);
	friend istream & operator>> (istream & flux, Option & O);

	private:
		char _code[5];
		char * _intitule;
		float _price;
	public:
		Option();
		Option(const char * code, const char * intitule, const float prix);
		Option(const Option & obj);
		~Option();

		void setCode(const char * code);
		void setIntitule(const char * intitule);
		void setPrix(const float price);

		const char * getCode() const;
		const char * getIntitule() const;
		const float getPrix() const;

		void Affiche() const;
		const char * toString() const;

		void Save(std::ofstream &f);
        void Load(std::ifstream &f);

		Option operator--(); // pré-décrémentation
		Option operator--(int); // post-décrémentation

		Option & operator=(const Option & O);
};


#endif // OPTION_H
