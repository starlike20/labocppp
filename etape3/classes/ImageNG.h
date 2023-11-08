#ifndef IMAGENG_H
#define IMAGENG_H

#include "Dimension.h"
#include <iostream>
using namespace std;

class ImageNG
{
	private:
		int id;
		char *nom;
		Dimension dimension;
		int** matrice=NULL;

		
		void alloumatrice();///modif
	public:
		ImageNG(void);
		ImageNG(int i,const char*n);
		ImageNG(int i,const char*n,const Dimension& D);
		ImageNG(const ImageNG& img);
		~ImageNG();

		void setId(int i);
		void setNom(const char*n);
		void setDimension(const Dimension& D);
		void setPixel(int x,int y,int val);
		void setBackground(int val);

		int getId()const;
		const char * getNom() const;
		Dimension getDimension()const;
		int getPixel(int x,int y)const;


		void Affiche() const;
		void Dessine();
		void importFromFile(const char* fichier);
		void exportToFile(const char* fichier, const char* format);
};

#endif