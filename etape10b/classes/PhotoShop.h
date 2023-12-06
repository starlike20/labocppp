#ifndef PHOTOSHOP_H
#define PHOTOSHOP_H

#include "Exception.h"
#include "ArrayList.h"
#include "Iterateur.h"
#include "ImageNG.h"
#include "ImageB.h"
#include "ImageRGB.h"
#include "Image.h"

#include <iostream>
using namespace std;

class PhotoShop
{
 	private:
		ArrayList<Image*> images;
	 	static int numCourant;


	 	static PhotoShop instance;

	 	PhotoShop();
	 	PhotoShop& operator=(const PhotoShop& img);
	public:
		~PhotoShop();
		void reset();
		void ajouteImage(Image* pImage);
		 
		void afficheImages() const;
		void dessineImages() const;
		Image* getImageParIndice(int indice);
		Image* getImageParId(int id);
		void supprimeImageParIndice(int ind);
		void supprimeImageParId(int id);

		static PhotoShop& getInstance();
};
#endif