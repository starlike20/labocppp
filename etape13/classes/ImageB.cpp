#include "ImageB.h"
#include "MyQT.h"
#include <fstream>
#include <string.h>

Couleur ImageB::couleurTrue=Couleur::VERT;
Couleur ImageB::couleurFalse=Couleur::ROUGE;
//---------------------------------
//------ constructeur
//---------------------------------
	ImageB::ImageB():Image(){
		#ifdef DEBUG
			cout <<">> ImageB:constructeur par defaut<<"<< endl;
		#endif
		intimatrice();
		setBackground(0);
	}
	ImageB::ImageB(const char*n):Image(-1,n){
		#ifdef DEBUG
			cout <<">> ImageB:constructeur importation<<"<< endl;
		#endif
		intimatrice();
		setBackground(0);
	}
	ImageB::ImageB(const int i,const char*n):Image(i,n){
		#ifdef DEBUG
			cout <<">> ImageB:constructeur et initialisation partielle<<"<< endl;
		#endif
			intimatrice();
			setBackground(0);
	}
	ImageB::ImageB(const int i,const char*n,const Dimension& D):Image(i,n){
		#ifdef DEBUG
			cout <<">> ImageB:constructeur et initialisation complet<<"<< endl;
		#endif
			setDimension(D);
			intimatrice();
			setBackground(0);
	}
	ImageB::ImageB(const ImageB& img):Image(img.getId(),img.getNom()){
		int x,y;
		#ifdef DEBUG
			cout <<">> ImageB:constructeur  de copie<<"<< endl;
		#endif
		setDimension(img.getDimension());
		intimatrice();
		setBackground(0);
		for(x=0;x<dimension.getLargeur();x++){
			for(y=0;y<dimension.getHauteur();y++){
				setPixel(x,y,img.getPixel(x,y));
			}
		}
	}
//---------------------------------
//------ destructeur
//---------------------------------
	ImageB::~ImageB(){
		#ifdef DEBUG
			cout <<">> ImageB:destructeur d'imageB <<"<<endl;
		#endif
			if (matrice) {
				for (int i = 0; i < dimension.getLargeur(); i++) {
	            delete[] matrice[i];
	        	}
	        	delete[] matrice;
	        }
	        else{
	        	printf("vide");
	        }

	}
//---------------------------------
//------ setter
//---------------------------------
	void ImageB::setDimension(const Dimension& D){
		if((matrice!=nullptr) && (D.getLargeur() != dimension.getLargeur() || D.getHauteur() != dimension.getHauteur())){
			bool** nouvelleMatrice = new bool*[D.getLargeur()];
	        for (int x = 0; x < D.getLargeur(); x++) {
	            nouvelleMatrice[x] = new bool[D.getHauteur()];
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
	void ImageB::setPixel(int x,int y,bool b) throw(XYException)
	{
		if(x<0 || x>dimension.getLargeur()){
			throw XYException('x',"coordonner de pixel invalide");
		}
		else{
			if(y<0 || y>dimension.getHauteur()){
				throw XYException('y',"coordonner de pixel invalide");
			}
			matrice[x][y]=b;
		}
	}
	void ImageB::setBackground(bool b){
		int x,y;
        for(x=0;x<getDimension().getLargeur();x++){
        	for(y=0;y<getDimension().getHauteur();y++){
        		setPixel(x,y,b);
        	}
        }
	}
//---------------------------------
//------ getter
//---------------------------------
	bool ImageB::getPixel(int x,int y)const throw(XYException)
	{
		if(x<0 || x>=getDimension().getLargeur()){
				throw XYException('x',"coordonner de pixel invalide");
			}
		else{
			if(y<0 || y>=getDimension().getHauteur()){
				throw XYException('y',"coordonner de pixel invalide");
			}
		}
		return matrice[x][y];
	}
//---------------------------------
//------ Method
//---------------------------------

	void ImageB::Affiche() const {
		cout <<"[imageNG :nom=";
		if(nom)cout<<getNom();
		else cout<<"???" ;
		cout<<" id="<<getId();
		dimension.Affiche();
	}
	void ImageB::intimatrice(){
		matrice = new bool*[dimension.getLargeur()];
        for (int i = 0; i < dimension.getLargeur(); i++) {
            matrice[i] = new bool[dimension.getHauteur()];
        }
	}
	void ImageB::Dessine() const {
		MyQT::ViewImage(*this);
	}
	void ImageB::exportToFile(const char* fichier, const char* format){
		MyQT::ExportToFile(*this,fichier,format);
	}

//---------------------------------
//------ operateur
//---------------------------------

	ImageB& ImageB::operator=(const ImageB& img){
		if (this == &img) {
        return *this;  
    	}
		int x,y;
		setId(img.getId());
		setNom(img.getNom());
		setDimension(img.getDimension());
		for(x=0;x<this->getDimension().getLargeur();x++){
			for(y=0;y<this->getDimension().getHauteur();y++){
				this->setPixel(x,y,img.getPixel(x,y));
			}	
		}
		return (*this);
	}
	ostream& operator<<(ostream& s,const ImageB& img){
		s<<img.getId()<<"/"<<img.getNom()<<"/"<<img.getDimension().getLargeur()<<"/"<<img.getDimension().getHauteur()<<endl;
		return s;	
	}
	
	void ImageB::Save(ofstream & fichier) const{
		int i,j;
		Image::Save(fichier);
		dimension.Save(fichier);
		for(i=0;i<getDimension().getLargeur();i++){
			for(j=0;j<getDimension().getHauteur();j++){
				fichier.write((char *)&matrice[i][j],sizeof(bool));
			}
		}
	}
	void ImageB::Load(ifstream & fichier){
		int i,j;
		Image::Load(fichier);
		dimension.Load(fichier);
		for(i=0;i<getDimension().getLargeur();i++){
			for(j=0;j<getDimension().getHauteur();j++){
				fichier.read((char *)&matrice[i][j],sizeof(bool));
			}
		}
	}