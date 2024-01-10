#include <string.h>
#include "XYException.h"

//---------------------------------
//------ constructeur
//---------------------------------
	XYException::XYException():Exception(){
		#ifdef DEBUG
			cout <<">> XYException:constructeur par defaut<<"<<endl;
		#endif
		setcor('x');
	}
	XYException::XYException(char a,const char*n):Exception(n){
		#ifdef DEBUG
			cout <<">> XYException:constructeur par totale<<"<<endl;
		#endif
		setcor(a);
	}
	XYException::XYException(const XYException& E):Exception(E.gettexte()){
		#ifdef DEBUG
			cout <<">> XYException:constructeur de copie<<"<<endl;
		#endif
		setcor(E.getcor());
	}
//---------------------------------
//------ destructeur
//---------------------------------
	XYException::~XYException(){
		#ifdef DEBUG
			cout <<">> RGBException:destructeur par defaut<<"<<endl;
		#endif
	}
//---------------------------------
//------ setter
//---------------------------------
	void XYException::setcor(char a){
		cor=a;
	}
//---------------------------------
//------ getter
//---------------------------------
	char XYException::getcor()const{
		return cor;
	}
//---------------------------------
//------ methode
//---------------------------------
	void XYException::AfficheXY(){
		cout<<gettexte()<<"causé par de la coordonne"<<getcor()<<endl;
	}