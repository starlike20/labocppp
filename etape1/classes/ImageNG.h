#ifndef IMAGENG_H
#define IMAGENG_H

#include <iostream>
using namespace std;

class ImageNG
{
	private:
		int id;
		char *nom;
	public:
		ImageNG(void);
		ImageNG(int i,const char*n);
		ImageNG(const ImageNG& img);
		~ImageNG();

		void setId(int i);
		void setNom(const char*n);

		int getId()const;
		const char * getNom() const;


		void Affiche() const;
};

#endif