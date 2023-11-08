#include "ImageNG.h"
#include <string.h>

//---------------------------------
//------ constructeur
//---------------------------------

	ImageNG::ImageNG(void)
	{
		#ifdef DEBUG
			cout <<">> ImageNG:constructeur par defaut<<"<< endl;
		#endif
			setId(-1);
			nom= NULL;
			setNom("???");
	}
	ImageNG::ImageNG(int i, const char*n){
		#ifdef DEBUG
			cout <<">> ImageNG:constructeur et initialisation partielle<<"<< endl;
		#endif
			setId(i);
			nom= NULL;
			setNom(n);
	}
	ImageNG::ImageNG(int i,const char*n,const Dimension& D){
		#ifdef DEBUG
			cout <<">> ImageNG:constructeur et initialisation complet<<"<< endl;
		#endif
			setId(i);
			nom= NULL;
			setNom(n);
			setDimension(D);
	}
	ImageNG::ImageNG(const ImageNG& img){
		#ifdef DEBUG
			cout <<">> ImageNG:constructeur et initialisation de copie<<"<< endl;
		#endif
		nom=NULL;
		setId(img.getId());
		setNom(img.getNom());
		setDimension(img.getDimension());
	}
//---------------------------------
//------ destructeur
//---------------------------------
	ImageNG::~ImageNG(){
		#ifdef DEBUG
			cout <<">> ImageNG:destructeur par defaut<<"<<endl;
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
	void ImageNG::setDimension(const Dimension& D){
		dimension.setHauteur(D.getHauteur());
		dimension.setLargeur(D.getLargeur());
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
		Dimension ImageNG::getDimension() const
		{
			return dimension;
		}


//---------------------------------
//------ Method
//---------------------------------

	void ImageNG::Affiche() const
	{
		cout <<"{"<<endl;
		cout<<"imageNG :nom=";
		if(nom)cout<<getNom();
		else cout<<"???" ;
		cout<<" id="<<getId();
		dimension.Affiche();
		cout<<"}"<<endl;

	}