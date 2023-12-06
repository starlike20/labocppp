#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "Exception.h"
#include "Couleur.h"
#include <iostream>
using namespace std;

template <class T> struct cellule
{
	T valeur;
	cellule<T> *suivant;

};
template<class T> class Iterateur;

template<class T> 
class ArrayList
{
	private:
		cellule<T> *tete;
	public:
		friend class Iterateur<T>;
		ArrayList();
		ArrayList(ArrayList<T>& A);
		~ArrayList();

		int getNombreElements();
		T& getElement(int ind) throw(Exception);

		bool estVide();
		void Affiche();
		void insereElement(T const & val);
		T retireElement(int ind) throw(Exception);
		ArrayList<T>& operator=(ArrayList<T>& A);

};
#endif