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
		ImageNG comp(const ImageNG& img);
	public:
		ImageNG(void);
		ImageNG(const char*n);
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
		const Dimension& getDimension() const;
		int getPixel(int x,int y)const;
		int getLuminance()const;
		int getMinimum()const;
		int getMaximum()const;
		float getContraste()const;

		void Affiche() const;
		void intimatrice();
		void Dessine();
		void importFromFile(const char* fichier);
		void exportToFile(const char* fichier, const char* format);

		ImageNG& operator=(const ImageNG& img);
		friend ostream& operator<<(ostream& s,const ImageNG& img);
		friend istream& operator>>(istream& s,ImageNG& img);
		const ImageNG operator+(int n);
		friend ImageNG operator+(int n,ImageNG& img);
		const ImageNG operator-(int n);
		friend ImageNG operator-(int n,ImageNG& img);
		ImageNG operator-(ImageNG& im);
		ImageNG& operator++();
		ImageNG operator++(int);
		ImageNG& operator--();
		ImageNG operator--(int);
		int operator<(ImageNG& img);
		int operator>(ImageNG& img);
		int operator==(ImageNG& img);

};

#endif