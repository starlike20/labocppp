#ifndef IMAGEB_H
#define IMAGEB_H

#include "Dimension.h"
#include "Couleur.h"
#include "Image.h"
#include <iostream>
#include "XYException.h"
using namespace std;

class ImageB:public Image
{
	private:
		bool** matrice=NULL;
	public:
		ImageB();
		ImageB(const char*n);
		ImageB(const int i,const char*n);
		ImageB(const int i,const char*n,const Dimension& D);
		ImageB(const ImageB& img);
		~ImageB();

		virtual void setDimension(const Dimension& D) override;
		void setPixel(int x,int y,bool b) throw(XYException);
		void setBackground(bool b);

		bool getPixel(int x,int y)const throw(XYException);

		virtual void Affiche() const override;
		void intimatrice();
		virtual void Dessine() const override;
		virtual void exportToFile(const char* fichier, const char* format) override;
		ImageB& operator=(const ImageB& img);
		friend ostream& operator<<(ostream& s,const ImageB& img);

		static Couleur couleurTrue;
		static Couleur couleurFalse;

		void Save(ofstream & fichier) const override;
		void Load(ifstream & fichier) override;

};
#endif