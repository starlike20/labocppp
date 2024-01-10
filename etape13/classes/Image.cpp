#include <cstring>

#include "Image.h"
#include <fstream>

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

		void Image::Save(ofstream & fichier) const{
			int n;
			n=strlen(nom);
			fichier.write((char *)&id,sizeof(int));
			fichier.write((char *)&n,sizeof(int));
			fichier.write((char *)nom,n*sizeof(char));
		}
		void Image::Load(ifstream & fichier){
			int n;
			char*nn;
			fichier.read((char *)&id,sizeof(int));
			fichier.read((char *)&n,sizeof(int));
			cout<<"load"<<n<<endl;
			nn=new char[n];
			fichier.read((char *)nn,n*sizeof(char));
			nn[n]='\0';
			setNom(nn);
		}