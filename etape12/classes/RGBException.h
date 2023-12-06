#ifndef RGBEXCEPTION_H
#define RGBEXCEPTION_H

#include "Exception.h"
#include <iostream>
using namespace std;

class RGBException:public Exception
{
	private:
		int valeur;
	public:
		RGBException();
		RGBException(int val,const char*n);
		RGBException(const RGBException& E);
		~RGBException();

		void setvaleur(int val);
		int getvaleur() const;

		void AfficheRGBE();
};
#endif