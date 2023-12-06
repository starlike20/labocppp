#ifndef IMAGENG_H
#define IMAGENG_H

#include "Dimension.h"
#include "Image.h"
#include "XYException.h"
#include "RGBException.h"
#include <iostream>
using namespace std;

class ImageNG:public Image
{
	private:
		int** matrice=NULL;
	public:
		ImageNG(void);
		ImageNG(const char*n);
		ImageNG(const int i,const char*n);
		ImageNG(const int i,const char*n,const Dimension& D);
		ImageNG(const ImageNG& img);
		~ImageNG();

		virtual void setDimension(const Dimension& D) override;
		void setPixel(int x,int y,int val) throw(XYException,RGBException);
		void setBackground(int val);

		int getPixel(int x,int y)const throw(XYException,RGBException);
		int getLuminance()const;
		int getMinimum()const;
		int getMaximum()const;
		float getContraste()const;

		virtual void Affiche() const override;
		void intimatrice();
		virtual void Dessine() const override;
		void importFromFile(const char* fichier);
		virtual void exportToFile(const char* fichier, const char* format) override;

		ImageNG& operator=(const ImageNG& img);
		friend ostream& operator<<(ostream& s,const ImageNG& img);
		friend istream& operator>>(istream& s,ImageNG& img);
		const ImageNG operator+(int n);
		friend ImageNG operator+(int n,ImageNG& img);
		const ImageNG operator-(int n);
		friend ImageNG operator-(int n,ImageNG& img);
		ImageNG operator-(const ImageNG& im);
		ImageNG& operator++();
		ImageNG operator++(int);
		ImageNG& operator--();
		ImageNG operator--(int);
		int operator<(ImageNG& img) throw(XYException);
		int operator>(ImageNG& img) throw(XYException);
		int operator==(ImageNG& img) throw(XYException);

		void Save(ofstream & fichier) const override;
		void Load(ifstream & fichier)override;

};

#endif