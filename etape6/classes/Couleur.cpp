#include <cstring>

#include "Couleur.h"

	const Couleur Couleur::ROUGE(255,0,0);
	const Couleur Couleur::VERT(0,255,0);
	const Couleur Couleur::BLEU(0,0,255);
	const Couleur Couleur::BLANC(255,255,255);
	const Couleur Couleur::NOIR(0,0,0);
//---------------------------------
//------ constructeur
//---------------------------------
	Couleur::Couleur(){
		setRouge(255);
		setVert(255);
		setBleu(255);
	}

	Couleur::Couleur(int r){
		setRouge(r);
		setVert(0);
		setBleu(0);
	}

	Couleur::Couleur(int r,int v){
		setRouge(r);
		setVert(v);
		setBleu(0);
	}
	Couleur::Couleur(int r,int v,int b){
		setRouge(r);
		setVert(v);
		setBleu(b);
	}
	Couleur::Couleur(const Couleur& c){
		setRouge(c.getRouge());
		setVert(c.getVert());
		setBleu(c.getBleu());
	}
//---------------------------------
//------ destructeur
//---------------------------------
	Couleur::~Couleur(){

	}
//---------------------------------
//------ setter
//---------------------------------
	void Couleur::setRouge(int r) 
	{
		if(r<0 || r>255){
			throw RGBException(r,"Composant rouge invalide");
		}
		else{
			rouge=r;
		}
	}
	void Couleur::setVert(int v) 
	{
		if(v<0 || v>255){
			throw(RGBException(v,"Composant vert invalide"));
		}
		else{
			vert=v;
		}
	}
	void Couleur::setBleu(int b) 
	{
		if(b<0 || b>255){
			throw(RGBException(b,"Composant blue invalide"));
		}
		else{
			bleu=b;
		}
	}
//---------------------------------
//------ getter
//---------------------------------
	int Couleur::getRouge()const{
		return rouge;
	}
	int Couleur::getVert()const{
		return vert;
	}
	int Couleur::getBleu()const{
		return bleu;
	}

	void Couleur::Affiche()const{
		cout<<"Couleur:"<<"Rouge:"<<getRouge()<<"Vert:"<<getVert()<<"Bleu:"<<getBleu()<<endl;
	}
//---------------------------------
//------ operateur
//---------------------------------
	Couleur& Couleur::operator=(const Couleur& c){
		setRouge(c.getRouge());
		setVert(c.getVert());
		setBleu(c.getBleu());
		return *this;
	}
	ostream& operator<<(ostream& s,const Couleur&c){
		s<<"Couleur:"<<"Rouge:"<<c.getRouge()<<"Vert:"<<c.getVert()<<"Bleu:"<<c.getBleu()<<endl;
		return s;
	}