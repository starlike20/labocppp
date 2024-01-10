#include <string.h>
#include "Exception.h"

//---------------------------------
//------ constructeur
//---------------------------------

	Exception::Exception(){
		#ifdef DEBUG
			cout <<">> Exception:constructeur par defaut<<"<< endl;
		#endif
		texte=NULL;
		settexte("il a un probleme");
	}

	Exception::Exception(const char*n){
		#ifdef DEBUG
			cout <<">> Exception:constructeur totale<<"<< endl;
		#endif
		texte=NULL;
		settexte(n);
	}
//---------------------------------
//------ destructeur
//---------------------------------
	Exception::~Exception(){
		#ifdef DEBUG
			cout <<">> Exception:destructeur par defaut<<"<<endl;
		#endif
			if(texte)
				delete texte;
	}
//---------------------------------
//------ setter
//---------------------------------
	void Exception::settexte(const char*n){
		if (texte != nullptr) {
            delete[] texte;
        }
        if (n != nullptr) {
            texte = new char[strlen(n) + 1];
            strcpy(texte, n);
        } else {
            texte = nullptr;
        }
	}
//---------------------------------
//------ getter
//---------------------------------
	const char* Exception::gettexte()const {
		return texte;
	}
