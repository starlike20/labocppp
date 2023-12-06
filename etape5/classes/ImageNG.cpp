#include <string.h>
#include "ImageNG.h"
#include "MyQT.h"

//---------------------------------
//------ constructeur
//---------------------------------
	/*int ImageNG::comp(const ImageNG& img){

	}*/
	ImageNG::ImageNG(void):Image()
	{
		#ifdef DEBUG
			cout <<">> ImageNG:constructeur par defaut<<"<< endl;
		#endif
			intimatrice();
			setBackground(0);
	}
	ImageNG::ImageNG(const char*n):Image(-1,n){
		#ifdef DEBUG
			cout <<">> ImageNG:constructeur importation<<"<< endl;
		#endif
			intimatrice();
			setBackground(0);
			importFromFile(n);
	}
	ImageNG::ImageNG(const int i, const char*n):Image(i,n){
		#ifdef DEBUG
			cout <<">> ImageNG:constructeur et initialisation partielle<<"<< endl;
		#endif
			intimatrice();
			setBackground(0);
	}
	ImageNG::ImageNG(const int i,const char*n,const Dimension& D):Image(i,n){
		#ifdef DEBUG
			cout <<">> ImageNG:constructeur et initialisation complet<<"<< endl;
		#endif
			setDimension(D);
			intimatrice();
			setBackground(0);
	}
	ImageNG::ImageNG(const ImageNG& img):Image(img.getId(),img.getNom()){
		int x,y;
		#ifdef DEBUG
			cout <<">> ImageNG:constructeur  de copie<<"<< endl;
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
	ImageNG::~ImageNG(){
		#ifdef DEBUG
			cout <<">> ImageNG:destructeur d'imageNG <<"<<endl;
		#endif
			if (matrice) {
				for (int i = 0; i < getDimension().getLargeur(); i++) {
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
		if(x<0 || x>dimension.getLargeur() || y<0 || y>dimension.getHauteur()){
			cout<<"coordonnee invalide"<<endl;
		}
		else{
			if(val<0 || val>255){
				cout<<val<<endl;
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

		int ImageNG::getPixel(int x,int y)const
		{
			if(x<0 || x>=getDimension().getLargeur()){
				return -1;
			}
			else{
				if(y<0 || y>=getDimension().getHauteur()){
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

		int ImageNG::getLuminance()const
		{
			int i,j,s=0;
			for(i=0;i<dimension.getLargeur();i++){
				for(j=0;j<dimension.getHauteur();j++){
					s=s+getPixel(i,j);
				}
			}
			return s/(dimension.getLargeur()*dimension.getHauteur());
		}
		int ImageNG::getMinimum()const{
			int min=256,i,j;
			for(i=0;i<dimension.getLargeur();i++){
				for(j=0;j<dimension.getHauteur();j++){
					if(getPixel(i,j)<min){
						min=getPixel(i,j);
					}
				}
			}
			return min;
		}
		int ImageNG::getMaximum()const{
			int max=0,i,j;
			for(i=0;i<dimension.getLargeur();i++){
				for(j=0;j<dimension.getHauteur();j++){
					if(getPixel(i,j)>max){
						max=getPixel(i,j);
					}
				}
			}
			return max;
		}
		float ImageNG::getContraste()const{
			int min,max;
			min=getMinimum();
			max=getMaximum();
			if((max+min)==0){
				return -1.00;
			}
			else{
				return ((float)(max-min))/(max+min);
			}
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
	void ImageNG::intimatrice(){
		matrice = new int*[getDimension().getLargeur()];
        for (int i = 0; i < getDimension().getLargeur(); i++) {
            matrice[i] = new int[getDimension().getHauteur()]();
        }
    }
	void ImageNG::Dessine() const{
		MyQT::ViewImage(*this);
	}
	void ImageNG::importFromFile(const char* fichier){
		MyQT::ImportFromFile(*this,fichier);
	}
	void ImageNG::exportToFile(const char* fichier, const char* format){
		MyQT::ExportToFile(*this,fichier,format);
	}

//---------------------------------
//------ operateur
//---------------------------------

	ImageNG& ImageNG::operator=(const ImageNG& img){
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
	ostream& operator<<(ostream& s,const ImageNG& img){
		s<<img.getId()<<"/"<<img.getNom()<<"/"<<img.getDimension().getLargeur()<<"/"<<img.getDimension().getHauteur()<<"/"<<img.getLuminance()<<"/"<<img.getContraste();
		return s;
	}
	istream& operator>>(istream& s, ImageNG& img) {
	    int i;
	    Dimension d;
	    char n[50];
	    cout << "Entrez un identifiant : ";
	    s >> i;
	    while (i < 0) {
	        cout << "Entrez un identifiant valide : " << endl;
	        s >> i;
	    }
	    cout << "Entrez un nom : ";
	    s >> n;
	    s >> d;
	    img.setId(i);
	    img.setNom(n);
	    img.setDimension(d);
	    return s;
	}
	const ImageNG ImageNG::operator+(int n){
		ImageNG img(*this);
		int i,j,a;
		for(i=0;i<img.getDimension().getLargeur();i++){
			for(j=0;j<img.getDimension().getHauteur();j++){
				a=img.getPixel(i,j)+n;
				if(a>255){
					img.setPixel(i,j,255);
				}
				else{
					img.setPixel(i,j,a);
				}
			}
		}
		return img;
	}
	ImageNG operator+(int n,ImageNG& img){
		return img+n;
	}
	const ImageNG ImageNG::operator-(int n){
		ImageNG img(*this);
		int i,j,a;
		for(i=0;i<img.getDimension().getLargeur();i++){
			for(j=0;j<img.getDimension().getHauteur();j++){
				a=img.getPixel(i,j)-n;
				if(a<0 ){
					img.setPixel(i,j,0);
				}
				else{
					img.setPixel(i,j,a);
				}
			}
		}
		return img;
	}
	ImageNG operator-(int n,ImageNG& img){
		return img-n;
	}
	ImageNG ImageNG::operator-(ImageNG& im){
		int l,h,i,j,val;
		ImageNG tmp;
		if(this->getDimension().getLargeur()<im.getDimension().getLargeur()){
			l=this->getDimension().getLargeur();
		}
		else{
			l=im.getDimension().getLargeur();
		}
		if(this->getDimension().getHauteur()<im.getDimension().getHauteur()){
			h=this->getDimension().getHauteur();
		}
		else{
			h=im.getDimension().getHauteur();
		}
		tmp.setDimension(Dimension(l,h));
		for(i=0;i<l;i++){
			for(j=0;j<h;j++){
				val=this->getPixel(i,j)-im.getPixel(i,j);
				if(val<0){
					tmp.setPixel(i,j,0);
				}
				else{
					tmp.setPixel(i,j,val);
				}
			}
		}
		return tmp;
	}
	ImageNG& ImageNG::operator++(){
		(*this)=(*this)+20;
		return (*this);
	}
	ImageNG ImageNG::operator++(int){
		ImageNG tmp(*this);
		(*this)=(*this)+20;
		return tmp;
	}
	ImageNG& ImageNG::operator--(){
		(*this)=(*this)-20;
		return (*this);
	}
	ImageNG ImageNG::operator--(int){
		ImageNG tmp(*this);
		(*this)=(*this)-20;
		return tmp;
	}
	int ImageNG::operator<(ImageNG& img){
		ImageNG tmp;
		int i=0,j=0,tr=1;
		if((this->getDimension()!=img.getDimension())==1){
			return -1;
		}
		else{
			while(i<img.getDimension().getLargeur() && tr==1){
				while(j<img.getDimension().getLargeur() && tr==1)
				{
					if ((*this).getPixel(i,j)>img.getPixel(i,j))
					{
						tr=0;																																													
					}
					j++;
				}
				i++;
			}
		}
		return tr;
	}
	int ImageNG::operator>(ImageNG& img){
		ImageNG tmp;
		int i=0,j=0,tr=1;
		if((this->getDimension()!=img.getDimension())==1){
			return -1;
		}
		else{
			while(i<img.getDimension().getLargeur() && tr==1){
				while(j<img.getDimension().getLargeur() && tr==1)
				{
					if ((*this).getPixel(i,j)<img.getPixel(i,j))
					{
						tr=0;																																													
					}
					j++;
				}
				i++;
			}
		}
		return tr;
	}
	int ImageNG::operator==(ImageNG& img){
		ImageNG tmp;
		int i=0,j=0,tr=1;
		if((this->getDimension()!=img.getDimension())==1){
			return -1;
		}
		else{
			while(i<img.getDimension().getLargeur() && tr==1){
				while(j<img.getDimension().getLargeur() && tr==1)
				{
					if ((*this).getPixel(i,j)!=img.getPixel(i,j))
					{
						tr=0;																																													
					}
					j++;
				}
				i++;
			}
		}
		return tr;
	}