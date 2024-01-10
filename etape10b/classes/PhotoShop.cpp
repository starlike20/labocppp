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
	
	pImage->setId(numCourant);
	numCourant++;
	images.insereElement(pImage);
}
void PhotoShop::afficheImages() const{
	ArrayList<Image*> m(images);
	Iterateur<Image*> i(m);
	while(!i.end()){
		(&i)->Affiche();
		//images.getElement(i)->Dessine();
		cout<<endl;
		i++;
	}
}
void PhotoShop::dessineImages() const{
	ArrayList<Image*> m(images);
	Iterateur<Image*> i(m);
	while(!i.end()){
		(&i)->Dessine();
		//images.getElement(i)->Dessine();
		cout<<endl;
		i++;
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
			return  images.getElement(i);
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
	int j=0;
	ArrayList<Image*> m(images);
	Iterateur<Image*> i(m);
	while(!i.end()){
		if(id==(&i)->getId()){
			supprimeImageParIndice(j);
		}
		j++;
		i++;
	}
	
}
/**********************les instance**********************/
PhotoShop& PhotoShop::getInstance(){
	return PhotoShop::instance;
}
PhotoShop PhotoShop::instance;