#ifndef Dimension_h
#define Dimension_h
#include "XYException.h"

#include <iostream>
using namespace std;

class Dimension{
	private:
		int largeur;
		int hauteur;
		int comp(const Dimension& D)const;
	public:
		static const Dimension VGA;
		static const Dimension HD;
		static const Dimension FULL_HD;
		Dimension(void);
		Dimension(const int l,const int h);
		Dimension(const Dimension& dim);
		~Dimension();

		void setLargeur(int i);
		void setHauteur(int i) ;

		int getLargeur() const;
		int getHauteur() const;

		void Affiche() const;

		friend ostream& operator<<(ostream& s, const Dimension& d);
		friend istream& operator>>(istream& s, Dimension& d) ;
		int operator==(const Dimension& d)const;
		int operator!=(const Dimension& d)const;
		void Save(ofstream & fichier) const;
		void Load(ifstream & fichier);
};

#endif