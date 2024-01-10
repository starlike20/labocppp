#ifndef COULEUR_H
#define COULEUR_H

#include "RGBException.h"
#include <iostream>
using namespace std;
class Couleur{
	private:
		int rouge;
		int vert;
		int bleu;
	public:
		Couleur();
		Couleur(int r);
		Couleur(int r,int v);
		Couleur(int r,int v,int b);
		Couleur(const Couleur& C);
		~Couleur();

		void setRouge(int r) throw(RGBException);
		void setVert(int v) throw(RGBException);
		void setBleu(int b) throw(RGBException);

		int getRouge()const;
		int getVert()const;
		int getBleu()const;

		void Affiche()const;
		Couleur& operator=(const Couleur& c);
		friend ostream& operator<<(ostream&s,const Couleur&c);

	static const Couleur ROUGE;
	static const Couleur VERT;
	static const Couleur BLEU;
	static const Couleur BLANC;
	static const Couleur NOIR;

	void Save(ofstream & fichier) const;
	void Load(ifstream & fichier);
};
#endif