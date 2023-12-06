#ifndef ITERATEUR_H
#define ITERATEUR_H

#include "Exception.h"
#include "ArrayList.h"
#include <iostream>
using namespace std;

template<class T> 
class Iterateur{
	private:
		ArrayList<T>& liste;
		cellule<T> *pcur;
	public:
		Iterateur(ArrayList<T> &A);
		~Iterateur();

		T reset();
		bool end();
		int operator++();
		int operator++(int);
		operator T() const;
		T& operator&(void);
};
#endif
