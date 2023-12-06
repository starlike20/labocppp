#include <cstring>
#include <fstream>
#include "ImageRGB.h"
#include "MyQT.h"

//---------------------------------
//------ constructeur
//---------------------------------
	/*int ImageNG::comp(const ImageNG& img){

	}*/

	ImageRGB::ImageRGB():Image(){
		#ifdef DEBUG
			cout <<">> ImageRGB:constructeur par defaut<<"<< endl;
		#endif
		intimatrice();
		setBackground(Couleur::BLANC );
	}
	ImageRGB::ImageRGB(const char*n):Image(-1,n){
		#ifdef DEBUG
			cout <<">> ImageRGB:constructeur importation<<"<< endl;
		#endif
		intimatrice();
		setBackground(Couleur::BLANC);
		importFromFile(n);	
	}
	ImageRGB::ImageRGB(const int i,const char* n):Image(i,n){
		#ifdef DEBUG
			cout <<">> ImageRGB:constructeur et initialisation partielle<<"<< endl;
		#endif
			intimatrice();
			setBackground(Couleur::BLANC);
	}
	ImageRGB::ImageRGB(const int i,const char* n,const Dimension& D):Image(i,n){
		#ifdef DEBUG
			cout <<">> ImageRGB:constructeur et initialisation complet<<"<< endl;
		#endif
			setDimension(D);
			intimatrice();
			setBackground(Couleur::BLANC);
	}
	ImageRGB::ImageRGB(const ImageRGB& img):Image(img.getId(),img.getNom()){
		int x,y;
		#ifdef DEBUG
			cout <<">> ImageRGB:constructeur  de copie<<"<< endl;
		#endif
		setDimension(img.getDimension());
		intimatrice();
		setBackground(Couleur::BLANC);
		for(x=0;x<dimension.getLargeur();x++){
			for(y=0;y<dimension.getHauteur();y++){
				setPixel(x,y,img.getPixel(x,y));
			}
		}
	}
//---------------------------------
//------ destructeur
//---------------------------------
	ImageRGB::~ImageRGB(){
		#ifdef DEBUG
			cout <<">> ImageRGB:destructeur d'imageRGB <<"<<endl;
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
	void ImageRGB::setDimension(const Dimension& D){
		if((matrice!=nullptr) && (D.getLargeur() != dimension.getLargeur() || D.getHauteur() != dimension.getHauteur())){
			Couleur** nouvelleMatrice = new Couleur*[D.getLargeur()];
	        for (int x = 0; x < D.getLargeur(); x++) {
	            nouvelleMatrice[x] = new Couleur[D.getHauteur()];
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
	void ImageRGB::setPixel(int x,int y,const Couleur& c) throw(XYException)
	{
		if(x<0 || x>dimension.getLargeur()){
			throw XYException('x',"coordonner de pixel invalide");
		}
		else{
			if(y<0 || y>dimension.getHauteur()){
				throw XYException('y',"coordonner de pixel invalide");
			}
			matrice[x][y]=c;
		}
	}
	void ImageRGB::setBackground(const Couleur& c){
		int x,y;
        for(x=0;x<getDimension().getLargeur();x++){
        	for(y=0;y<getDimension().getHauteur();y++){
        		setPixel(x,y,c);
        	}
        }
	}
//---------------------------------
//------ getter
//---------------------------------
	const Couleur& ImageRGB::getPixel(int x,int y)const throw(XYException)
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
	void ImageRGB::Affiche() const{
		cout <<"[imageNG :nom=";
		if(nom)cout<<getNom();
		else cout<<"???" ;
		cout<<" id="<<getId();
		dimension.Affiche();
	}
	void ImageRGB::intimatrice(){
		matrice = new Couleur*[dimension.getLargeur()];
        for (int i = 0; i < dimension.getLargeur(); i++) {
            matrice[i] = new Couleur[dimension.getHauteur()];
        }
	}
	void ImageRGB::Dessine() const{
		MyQT::ViewImage(*this);
	}
	void ImageRGB::importFromFile(const char* fichier){
		MyQT::ImportFromFile(*this,fichier);
	}
	void ImageRGB::exportToFile(const char* fichier, const char* format){
		MyQT::ExportToFile(*this,fichier,format);
	}

//---------------------------------
//------ operateur
//---------------------------------
	ImageRGB& ImageRGB::operator=(const ImageRGB& img){
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
	ostream& operator<<(ostream& s,const ImageRGB& img){
		s<<img.getId()<<"/"<<img.getNom()<<"/"<<img.getDimension().getLargeur()<<"/"<<img.getDimension().getHauteur()<<endl;
		return s;
	}	

	void ImageRGB::Save(ofstream & fichier) const{
		int i,j;
		Image::Save(fichier);
		dimension.Save(fichier);
		for(i=0;i<getDimension().getLargeur();i++){
			for(j=0;j<getDimension().getHauteur();j++){
				matrice[i][j].Save(fichier);
			}
		}

	}
	void ImageRGB::Load(ifstream & fichier){
		int i,j;
		Image::Load(fichier);
		dimension.Load(fichier);
		for(i=0;i<getDimension().getLargeur();i++){
			for(j=0;j<getDimension().getHauteur();j++){
				matrice[i][j].Load(fichier);
			}
		}
	}
	ImageNG ImageRGB::getRouge() const{
		int x,y;
		ImageNG i(this->getId(),this->getNom(),this->getDimension());
		for(x=0;x<getDimension().getLargeur();x++){
			for(y=0;y<getDimension().getHauteur();y++){
				i.setPixel(x,y,this->getPixel(x,y).getRouge());
			}
		}
		return i;
	}
	ImageNG ImageRGB::getVert() const{
		int x,y;
		ImageNG i(this->getId(),this->getNom(),this->getDimension());
		for(x=0;x<getDimension().getLargeur();x++){
			for(y=0;y<getDimension().getHauteur();y++){
				i.setPixel(x,y,this->getPixel(x,y).getVert());
			}
		}
		return i;
	}
	ImageNG ImageRGB::getBleu() const{
		int x,y;
		ImageNG i(this->getId(),this->getNom(),this->getDimension());
		for(x=0;x<getDimension().getLargeur();x++){
			for(y=0;y<getDimension().getHauteur();y++){
				i.setPixel(x,y,this->getPixel(x,y).getBleu());
			}
		}
		return i;
	}

	void ImageRGB::setRGB(const ImageNG &r, const ImageNG &g, const ImageNG& b){
		int x,y;
		if(r.getDimension()==g.getDimension() && g.getDimension()==b.getDimension()){
			setDimension(r.getDimension());
			for(x=0;x<getDimension().getLargeur();x++){
				for(y=0;y<getDimension().getHauteur();y++){
					setPixel(x,y,Couleur(r.getPixel(x,y),g.getPixel(x,y),b.getPixel(x,y)));
				}
			}
		}
	}

	