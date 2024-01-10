#include "ImageNG.h"
#include <string.h>
#include "MyQT.h"
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
			setDimension(dimension);
			alloumatrice();
			setBackground(0);
	}

	ImageNG::ImageNG(int i, const char*n){
		#ifdef DEBUG
			cout <<">> ImageNG:constructeur et initialisation partielle<<"<< endl;
		#endif
			setId(i);
			nom= NULL;
			setNom(n);
			alloumatrice();
			setBackground(0);
	}
	ImageNG::ImageNG(int i,const char*n,const Dimension& D){
		#ifdef DEBUG
			cout <<">> ImageNG:constructeur et initialisation complet<<"<< endl;
		#endif
			setId(i);
			nom= NULL;
			setNom(n);
			setDimension(D);
			alloumatrice();
			setBackground(0);
	}
	ImageNG::ImageNG(const ImageNG& img){
		int x,y;
		#ifdef DEBUG
			cout <<">> ImageNG:constructeur et initialisation de copie<<"<< endl;
		#endif
		nom=NULL;
		setId(img.getId());
		setNom(img.getNom());
		alloumatrice();
		setBackground(0);
		setDimension(img.getDimension());
		for(x=0;x<dimension.getLargeur();x++){
			for(y=0;y<dimension.getHauteur();y++){
				setPixel(x,y,img.getPixel(x,y));
			}
		}
	}
//---------------------------------
//------ destructeur
//---------------------------------
	ImageNG::~ImageNG(){
		#ifdef DEBUG
			cout <<">> ImageNG:destructeur par defaut<<"<<endl;
		#endif
			for (int i = 0; i < getDimension().getLargeur(); i++) {
            delete[] matrice[i];
        	}
        	delete[] matrice;
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
		if((matrice!=nullptr) && (D.getLargeur() != dimension.getLargeur() || D.getHauteur() != dimension.getHauteur())){
			int** nouvelleMatrice = new int*[D.getLargeur()];
	        for (int x = 0; x < D.getLargeur(); x++) {
	            nouvelleMatrice[x] = new int[D.getHauteur()];
	        }
	        for (int x = 0; x < D.getLargeur(); x++) 
	        {
	            for (int y = 0; y < D.getHauteur(); y++) 
	            {
	                if (x < dimension.getLargeur() && y < dimension.getHauteur()) 
	                {
	                    nouvelleMatrice[x][y] = matrice[x][y];
	                } else 
	                {
	                	nouvelleMatrice[x][y] = 0; 
	                }
	            }
	        }
	        for (int i = 0; i < dimension.getLargeur(); i++) {
	            delete[] matrice[i];
	        }
	        delete[] matrice;
	        matrice = nouvelleMatrice;
	    }
	    dimension = D;
	}
	void ImageNG::setPixel(int x,int y,int val){
		int** m;
		m=matrice;
		if(x<0 || x>dimension.getLargeur() || y<0 || y>dimension.getHauteur()){
			cout<<"coordonnees invalides"<<endl;
		}
		else{
			if(val<0 || val>255){
				cout<<"entrez un niveau gris valide"<<endl;
			}
			else{
				matrice[x][y]=val;
			}
		}
	}

	void ImageNG::setBackground(int val)
	{
		int x,y;
        for(x=0;x<getDimension().getLargeur();x++){
        	for(y=0;y<getDimension().getHauteur();y++){
        		setPixel(x,y,val);
        	}
        }
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
		const Dimension& ImageNG::getDimension() const
		{
			return dimension;
		}

		int ImageNG::getPixel(int x,int y)const
		{
			if(x<0 || x>dimension.getLargeur()){
				return -1;
			}
			else{
				if(y<0 || y>dimension.getHauteur()){
					return -1;
				}
				else{
					if(matrice[x][y]<0 ||matrice[x][y]>255){
						return -1;
					}
				}
			}
			return matrice[x][y];		
		}
//---------------------------------
//------ Method
//---------------------------------

	void ImageNG::Affiche() const
	{
		cout <<"[imageNG :nom=";
		if(nom)cout<<getNom();
		else cout<<"???" ;
		cout<<" id="<<getId();
		dimension.Affiche();
	}
	void ImageNG::alloumatrice(){
		matrice = new int*[getDimension().getLargeur()];
        for (int i = 0; i < getDimension().getLargeur(); i++) {
            matrice[i] = new int[getDimension().getHauteur()];
        }
    }
	void ImageNG::Dessine(){
		MyQT::ViewImage(*this);
	}
	void ImageNG::importFromFile(const char* fichier){
		MyQT::ImportFromFile(*this,fichier);
	}
	void ImageNG::exportToFile(const char* fichier, const char* format){
		MyQT::ExportToFile(*this,fichier,format);
	}
