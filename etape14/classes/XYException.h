#ifndef XYBEXCEPTION_H
#define XYBEXCEPTION_H

#include "Exception.h"
#include <iostream>
using namespace std;

class XYException:public Exception
{
	private:
		char cor;
	public:
		XYException();
		XYException(const char a,const char*n);
		XYException(const XYException& E);
		~XYException();

		void setcor(char a);
		char getcor()const;

		void AfficheXY();
};
#endif