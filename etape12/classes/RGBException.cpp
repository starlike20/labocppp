#include <string.h>
#include "RGBException.h"

//---------------------------------
//------ constructeur
//---------------------------------
	RGBException::RGBException():Exception()
	{
		#ifdef DEBUG
			cout <<">> RGBException:constructeur par defaut<<"<<endl;
		#endif
		setvaleur(-1);
	}
	RGBException::RGBException(int val,const char*n):Exception(n)
	{
		#ifdef DEBUG
			cout <<">> RGBException:constructeur totale<<"<<endl;
		#endif
		setvaleur(val);
	}
	RGBException::RGBException(const RGBException& E):Exception(E.gettexte()){
		#ifdef DEBUG
			cout <<">> RGBException:constructeur de copie<<"<<endl;
		#endif
		setvaleur(E.getvaleur());
	}
//---------------------------------
//------ destructeur
//---------------------------------
	RGBException::~RGBException(){
		#ifdef DEBUG
			cout <<">> RGBException:destructeur<<"<<endl;
		#endif

	}
//---------------------------------
//------ setter
//---------------------------------
	void RGBException::setvaleur(int val){
		valeur=val;
	}
//---------------------------------
//------ getter
//---------------------------------
	int RGBException::getvaleur()const{
		return valeur;
	}
//---------------------------------
//------ methode
//---------------------------------
	void  RGBException::AfficheRGBE(){
		cout<<gettexte()<<"causé par"<<getvaleur()<<"comme valeur"<<endl;
	}