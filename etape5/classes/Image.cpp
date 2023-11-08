#include <cstring>

#include "Image.h"

//---------------------------------
//------ constructeur
//---------------------------------

	Image::Image()
	{
		#ifdef DEBUG
			cout <<">> Image:constructeur par defaut<<"<< endl;
		#endif
			setId(-1);
			nom= NULL;
			setNom("???");
	}
	Image::Image(const int i,const char*n){
		#ifdef DEBUG
			cout <<">> Image:constructeur et initialisation complet<<"<< endl;
		#endif
			setId(i);
			nom= NULL;
			setNom(n);
	}
//---------------------------------
//------ destructeur
//---------------------------------
	Image::~Image(){
		#ifdef DEBUG
			cout <<">> Image:destructeur par defaut<<"<<endl;
		#endif
			if(nom)
				delete nom;
	}

//---------------------------------
//------ setter
//---------------------------------
	void Image::setId(int i){
		id=i;
	}
	void Image::setNom(const char*n){
		if (nom != nullptr) {
            delete[] nom;
        }
        if (n != nullptr) {
            nom = new char[strlen(n) + 1];
            strcpy(nom, n);
        } else {
            nom = nullptr;
        }
	}
//---------------------------------
//------ getter
//---------------------------------
		int Image::getId() const
		{
			return id;
		}
		const char* Image::getNom() const
		{
			return nom;
		}
		const Dimension& Image::getDimension() const
		{
			return dimension;
		}


//---------------------------------
//------ Method
//---------------------------------

	