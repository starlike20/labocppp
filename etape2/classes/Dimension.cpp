#include "Dimension.h"

//---------------------------------
//------ static
//---------------------------------
	const Dimension Dimension::VGA(640, 480);
	const Dimension Dimension::HD(1280, 720);
	const Dimension Dimension::FULL_HD(1920, 1080);
	

//---------------------------------
//------ constructeur
//---------------------------------
 	Dimension::Dimension(void){
 		#ifdef DEBUG
			cout <<">> ImageNG:constructeur par defaut<<"<< endl;
		#endif
			setLargeur(-1);
			setHauteur(-1);
 	}
 	Dimension::Dimension(const int l,const int h){
 		#ifdef DEBUG
			cout <<">> ImageNG:constructeur d'initialisation<<"<< endl;
		#endif
			setLargeur(l);
			setHauteur(h);
 	}
 	Dimension::Dimension(const Dimension& dim){
 		#ifdef DEBUG
			cout <<">> ImageNG:constructeur de copie<<"<< endl;
		#endif
			setLargeur(dim.getLargeur());
			setHauteur(dim.getHauteur());
 	}
//---------------------------------
//------ destructeur
//---------------------------------
 	Dimension::~Dimension(){
 		#ifdef DEBUG
			cout <<">> ImageNG:destructeur par defaut<<"<<endl;
		#endif
 	}
//---------------------------------
//------ setter
//---------------------------------
 	void Dimension::setLargeur(int i){
 		if(i<0){
 			largeur=400;
 		}
 		else{
 			largeur=i;
 		}
 	}

	void Dimension::setHauteur(int i){
		if(i<0){
 			hauteur=300;
 		}
 		else{
 			hauteur=i;
 		}
	}
	
 //---------------------------------
//------ getter
//---------------------------------
	int Dimension::getLargeur() const{
		return largeur;
	}
	int Dimension::getHauteur() const{
		return hauteur;
	}
//---------------------------------
//------ Method
//---------------------------------
	void Dimension::Affiche() const{
		cout<<"[Dimension: largeur="<<getLargeur()<<" hauteur="<<getHauteur()<<"]"<<endl;
	}