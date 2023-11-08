#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
using namespace std;

class Exception
{
	protected:
		char*texte;
	public:
		Exception();
		Exception(const char*n);
		virtual ~Exception();

		void settexte(const char*n);
		const char* gettexte()const;
};
#endif