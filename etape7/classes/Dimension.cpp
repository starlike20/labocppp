#include "Dimension.h"
#include "XYException.h"

int Dimension::comp(const Dimension& D)const{
	if(D.getLargeur() != this->getLargeur() || D.getHauteur() != this->getHauteur()){
		return 0;
	}
	return 1;
}

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
			cout <<">> Dimension:constructeur par defaut<<"<< endl;
		#endif
			setLargeur(300);
			setHauteur(400);
 	}
 	Dimension::Dimension(const int l,const int h){
 		#ifdef DEBUG
			cout <<">> Dimension:constructeur d'initialisation<<"<< endl;
		#endif
			setLargeur(l);
			setHauteur(h);
 	}
 	Dimension::Dimension(const Dimension& dim){
 		#ifdef DEBUG
			cout <<">> Dimension:constructeur de copie<<"<< endl;
		#endif
			setLargeur(dim.largeur);
			setHauteur(dim.hauteur);
 	}
//---------------------------------
//------ destructeur
//---------------------------------
 	Dimension::~Dimension(){
 		#ifdef DEBUG
			cout <<">> Dimension:destructeur<<"<<endl;
		#endif
 	}
//---------------------------------
//------ setter
//---------------------------------
 	void Dimension::setLargeur(int i) 
 	{
 		if(i<1){
 			throw XYException('x',"la largeur doit etre superieur a zeros");
 		}
 		else{
 			largeur=i;
 		}
 	}

	void Dimension::setHauteur(int i) 
	{
		if(i<1){
 			throw XYException('y',"la hauteur doit etre superieur a zeros");
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
		cout<<"[Dimension: largeur="<<getLargeur()<<" hauteur="<<getHauteur()<<endl;
	}
//---------------------------------
//------ operateur
//---------------------------------
ostream& operator<<(ostream& s, const Dimension& d) {
    s << "Largeur: " << d.getLargeur() << " Hauteur: " << d.getHauteur();
    return s;
}
istream& operator>>(istream& s, Dimension& d) 
{
    int l, h;
    cout<<"entrez la largeur: ";
    s >> l ;
    if(l<0){
    	throw XYException('x',"la largeur doit etre superieur a zeros");
    }
    cout<<"entrez la hauteur: ";
    s>>h;
    if(h<0){
    	throw XYException('y',"la hauteur doit etre superieur a zeros");
    }
    d = Dimension(l, h);
    return s;
}
int Dimension::operator==(const Dimension& d)const{
	return comp(d)==1;
}
int Dimension::operator!=(const Dimension& d)const{
	return comp(d)==0;
}