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
	public:
		ImageNG(void);
		ImageNG(int i,const char*n);
		ImageNG(int i,const char*n,const Dimension& D);
		ImageNG(const ImageNG& img);
		~ImageNG();

		void setId(int i);
		void setNom(const char*n);
		void setDimension(const Dimension& D);

		int getId()const;
		const char * getNom() const;
		const Dimension& getDimension() const;


		void Affiche() const;
};

#endif