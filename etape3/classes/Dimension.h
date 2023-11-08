#ifndef Dimension_h
#define Dimension_h

#include <iostream>
using namespace std;

class Dimension{
	private:
		int largeur;
		int hauteur;
	public:
		static const Dimension VGA;
		static const Dimension HD;
		static const Dimension FULL_HD;
		Dimension(void);
		Dimension(const int l,const int h);
		Dimension(const Dimension& dim);
		~Dimension();

		void setLargeur(int i);
		void setHauteur(int i);

		int getLargeur() const;
		int getHauteur() const;

		void Affiche() const;

};

#endif