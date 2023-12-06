#ifndef SORTEDARRAYLIST_H
#define SORTEDARRAYLIST_H
#include <stdio.h>
#include "Exception.h"
#include "Couleur.h"
#include "ArrayList.h"	

template<class T> 
class SortedArrayList:public ArrayList <T>
{
	public:
		SortedArrayList();
		void insereElement(T const & val) override;
};
#endif;