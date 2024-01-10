#ifndef IMAGERGB_H
#define IMAGERGB_H

#include "Dimension.h"
#include "Couleur.h"
#include "Image.h"
#include "ImageNG.h"
#include <iostream>
#include "XYException.h"
#include "RGBException.h"
using namespace std;

class ImageRGB:public Image
{
	private:
		Couleur** matrice=NULL;
	public:
		ImageRGB();
		ImageRGB(const char*n);
		ImageRGB(const int i,const char* n);
		ImageRGB(const int i,const char* n,const Dimension& D);
		ImageRGB(const ImageRGB& img);
		~ImageRGB();

		virtual void setDimension(const Dimension& D) override;
		void setPixel(int x,int y,const Couleur& c) ;
		void setBackground(const Couleur& c);

		const Couleur& getPixel(int x,int y)const ;

		virtual void Affiche() const override;
		void intimatrice();
		virtual void Dessine() const override;
		void importFromFile(const char* fichier);
		virtual void exportToFile(const char* fichier, const char* format) override;
		ImageRGB& operator=(const ImageRGB& img);
		friend ostream& operator<<(ostream& s,const ImageRGB& img);

		void Save(ofstream & fichier) const;
		void Load(ifstream & fichier);

		ImageNG getRouge() const;
		ImageNG getVert() const;
		ImageNG getBleu() const;
		void setRGB(const ImageNG &r, const ImageNG &g, const ImageNG& b);
};
#endif