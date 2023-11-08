#ifndef IMAGE_H
#define IMAGE_H

#include "Dimension.h"
#include <iostream>
using namespace std;

class Image
{
	protected:
		int id;
		char *nom;
		Dimension dimension;
	public:
		Image(void);
		Image(const int i,const char*n);
		virtual ~Image();

		void setId(int i);
		void setNom(const char*n);
		virtual void setDimension(const Dimension& D)=0;

		int getId()const;
		const char * getNom() const;
		const Dimension& getDimension() const;

		virtual void Affiche()const =0;
		virtual void Dessine()const=0;
		virtual void exportToFile(const char* fichier, const char* format)=0;
};
#endif