#include "ImageNG.h"
#include <string.h>

//---------------------------------
//------ constructeur
//---------------------------------

	ImageNG::ImageNG(void)
	{
		#ifdef DEBUG
			cout <<">> ImageNG:constructeur par defaut<<">> endl;
		#endif
			setId(-1);
			nom= NULL;
			setNom("???");
	}
	ImageNG::ImageNG(int i, const char*n){
		#ifdef DEBUG
			cout <<">> ImageNG:constructeur et initialisation<<">> endl;
		#endif
			setId(i);
			nom= NULL;
			setNom(n);
	}
	ImageNG::ImageNG(const ImageNG& img){
		nom=NULL;
		setId(img.getId());
		setNom(img.getNom());
	}
//---------------------------------
//------ destructeur
//---------------------------------
	ImageNG::~ImageNG(){
		#ifdef DEBUG
			cout <<">> ImageNG:destructeur par defaut<<">> endl;
		#endif
			if(nom)
				delete nom;
	}

//---------------------------------
//------ setter
//---------------------------------
	void ImageNG::setId(int i){
		id=i;
	}
	void ImageNG::setNom(const char*n){
		if(nom) delete nom;
		if(n==NULL){
			nom=NULL;
		}
		nom=new char[strlen(n)+1];
		strcpy(nom,n);
	}
//---------------------------------
//------ getter
//---------------------------------
		int ImageNG::getId() const
		{
			return id;
		}
		const char *ImageNG::getNom() const
		{
			return nom;
		}

//---------------------------------
//------ Method
//---------------------------------

	void ImageNG::Affiche() const
	{
		cout <<"[imageNG :nom=";
		if(nom)cout<<getNom();
		else cout<<"???" ;
		cout<<" id="<<getId()<<"]"<<endl;

	}