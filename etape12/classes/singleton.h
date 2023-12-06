#ifndef SINGLETON_H
#define SINGLETON_H

#include "PhotoShop.h"
#include "Exception.h"
#include "ArrayList.h"
#include "Iterateur.h"
#include "ImageNG.h"
#include "ImageB.h"
#include "ImageRGB.h"
#include "Image.h"

#include <iostream>
using namespace std;

class Singleton
{
 	private:
 		Singleton();
 		Singleton(Singleton& a);
	 	static PhotoShop instance;
	 	Singleton& operator=(const Singleton& img);
	public:
		static PhotoShop& getInstance();
};
#endif