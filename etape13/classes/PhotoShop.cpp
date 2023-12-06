#include "PhotoShop.h"
//---------------------------------
//------ constructeur
//---------------------------------
int PhotoShop::numCourant = 0;
Image* PhotoShop::operande1=NULL;
Image* PhotoShop::operande2=NULL;
Image* PhotoShop::resultat=NULL;
PhotoShop::PhotoShop():i(images){
	#ifdef DEBUG
		cout <<">> PhotoShop:constructeur par defaut<<"<< endl;
		numCourant=1;
	#endif
}
PhotoShop::~PhotoShop(){
	#ifdef DEBUG
		cout <<">>photoshop:destructeur<<"<< endl;
	#endif
		reset();
}
//---------------------------------
//------ methode
//---------------------------------
void PhotoShop::reset(){
	int i;
	for(i=images.getNombreElements()-1;i>=0;i--){
		supprimeImageParIndice(i);
	}
	numCourant=1;
}
void PhotoShop::ajouteImage(Image* pImage){
	Image*p;
    ImageB* pB = dynamic_cast<ImageB*>(pImage);
    if (pB != NULL)
    {
      p =new ImageB(*pB);
    }
    ImageNG* pNG = dynamic_cast<ImageNG*>(pImage);
    if (pNG != NULL) 
    {
      p =new ImageNG(*pNG);
    }
    ImageRGB* pRGB = dynamic_cast<ImageRGB*>(pImage);
    if (pRGB != NULL) 
    {
      p =new ImageRGB(*pRGB);
    }
    cout << endl;
	p->setId(numCourant);
	numCourant++;
	images.insereElement(p);
}
void PhotoShop::afficheImages() const{
	int i;
	for(i=0;i<images.getNombreElements();i++){
		images.getElement(i)->Affiche();
		cout<<endl;
	}
}
void PhotoShop::dessineImages() const{
	int i;
	for(i=0;i<images.getNombreElements();i++){
		images.getElement(i)->Dessine();
		cout<<endl;
	}
}
Image* PhotoShop::getImageParIndice(int indice){
	if(indice<images.getNombreElements()){
		return images.getElement(indice);
	}
	return NULL;
}
Image* PhotoShop::getImageParId(int id)
{
	int i;
	for(i=0;i<images.getNombreElements();i++){
		if(id==images.getElement(i)->getId()){
			return images.getElement(i);
		}
	}
	cout<<"l'id n'existe pas"<<endl;
	return NULL;
}
void PhotoShop::supprimeImageParIndice(int ind){
	Image*img;
	img=images.retireElement(ind);
	delete img;

}
void PhotoShop::supprimeImageParId(int id){
	int i;
	for(i=0;i<images.getNombreElements();i++){
		if(id==images.getElement(i)->getId()){
			supprimeImageParIndice(i);
		}
	}
}
/**********************les instance**********************/
PhotoShop& PhotoShop::getInstance(){
	return PhotoShop::instance;
}
PhotoShop PhotoShop::instance;

int PhotoShop::importeImages(string nom){
	int n=0;
	char octet,type[6],chemin[150],no[50],ligne[200];
	ImageNG* NG;
	ImageB* B;
	ImageRGB* RGB;

	int i=0,j=0,tr=0;
	ifstream fichier(nom,ios::in);
	if (fichier) 
	{
		string lignee;
  	while (getline(fichier, lignee)) {
  		strcpy(ligne,lignee.c_str());
  		for(i=0,j=0,tr=0;i<=strlen(ligne);i++){
  			if(ligne[i]==';'){
  				if(tr==0){
  					type[j]='\0';
  					j=0;
  					tr++;
  				}
  				else{
  					if(tr==1){
  						chemin[j]='\0';
  						j=0;
  						tr++;
  					}
  					else{
  						no[j]='\0';
  						j=0;
  						tr++;
  					}
  				}
  			}
  			else{
	  			if(tr==0){
	  				type[j]=ligne[i];
	  				j++;
	  			}
	  			else{
	  				if(tr==1){
	  					chemin[j]=ligne[i];
	  					j++;
	  				}
	  				else{
	  					no[j]=ligne[i];
	  					j++;
	  				}
	  			}
	  		}
  		}
  		if(strcmp(type,"NG")==0){
  			NG=new ImageNG();
  			NG->setNom(no);
  			NG->importFromFile(chemin);
  			PhotoShop::getInstance().ajouteImage(NG);
  			n++;
  		}
  		else{
  			RGB=new ImageRGB();
  			RGB->setNom(no);
  			RGB->importFromFile(chemin);
  			PhotoShop::getInstance().ajouteImage(RGB);
  			n++;
  		}
    }
  } 
  else {
    std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
    return 0;
  }
  return n;
}
void PhotoShop::Save(){
	int n;
	Image*p;
	ImageB* pB;
	ImageNG* pN;
	ImageRGB* pR;
	if(getImageParIndice(0)!=NULL){
		ofstream fichier("sauvegarde.dat", ios::out | ios::trunc);
		if(fichier){
			fichier.write((char *)&numCourant,sizeof(int));
			ImageB::couleurTrue.Save(fichier);
			ImageB::couleurFalse.Save(fichier);
			n=images.getNombreElements();
			fichier.write((char *)&n,sizeof(int));
			i.reset();
			while(!i.end()){
				p=i;
				pB = dynamic_cast<ImageB*>(p);
		    if (pB != NULL)
		    {
		      n=3;
		      fichier.write((char *)&n,sizeof(int));
		      pB->Save(fichier);
		    }
		    pN = dynamic_cast<ImageNG*>(p);
		    if (pN != NULL)
		    {
		      n=1;
		      fichier.write((char *)&n,sizeof(int));
		      pN->Save(fichier);
		    }
		    pR = dynamic_cast<ImageRGB*>(p);
		    if (pR != NULL)
		    {
		      n=2;
		      fichier.write((char *)&n,sizeof(int));
		      pR->Save(fichier);
		    }
		    cout<<n<<endl;
		    i++;
			}
			fichier.close(); 
		}
	}

}
int PhotoShop::Load(){
	int n,i=0,j;
	Image*p;
	ImageB* pB;
	ImageNG* pN;
	ImageRGB* pR;
	ifstream fichier("sauvegarde.dat");
	if(fichier){
		fichier.read((char *)&numCourant,sizeof(int));
		ImageB::couleurTrue.Load(fichier);
		ImageB::couleurFalse.Load(fichier);
		fichier.read((char *)&n,sizeof(int));
		cout<<n<<endl;
		for(i=0;i<n;i++){
			fichier.read((char *)&j,sizeof(int));
			cout<<j<<endl;
			if(j==1){
				pN=new ImageNG();
				pN->Load(fichier);
				ajouteImage(pN);
			}
			else{
				if(j==2){
					pR=new ImageRGB();
					pR->Load(fichier);
					ajouteImage(pR);
				}
				else{
					pB=new ImageB();
					pB->Load(fichier);
					ajouteImage(pB);
				}
			}
		}
		fichier.close(); 
	}
	else{
		return 0;
	}
	return n;
}