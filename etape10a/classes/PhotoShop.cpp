#include "PhotoShop.h"
//---------------------------------
//------ constructeur
//---------------------------------
int PhotoShop::numCourant = 0;
PhotoShop::PhotoShop(){
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
	return images.getElement(indice);
}
Image* PhotoShop::getImageParId(int id)
{
	int i;
	for(i=0;i<images.getNombreElements();i++){
		if(id==images.getElement(i)->getId()){
			return images.getElement(i);
		}
	}
	cout<<"l'indice n'existe pas"<<endl;
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