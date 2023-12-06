#include "ArrayList.h"
#include "Image.h"	
//---------------------------------
//------ constructeur
//---------------------------------
	template<class T> 
	ArrayList<T>::ArrayList(){
		#ifdef DEBUG
			cout <<">> ArrayList:constructeur par defaut<<"<< endl;
		#endif
		tete=NULL;
	}

	template<class T> 
	ArrayList<T>::ArrayList(ArrayList<T>& A){
		int c,i=0;
		#ifdef DEBUG
			cout <<">> ArrayList:constructeur de copie<<"<< endl;
		#endif
			tete=NULL;
			c=A.getNombreElements();
			while(i<c){
				insereElement(A.getElement(i));
				i++;
			}
	}

	template<class T> 
	ArrayList<T>::~ArrayList(){
		int c,i=0;
		#ifdef DEBUG
			cout <<">> ArrayList:destructeur<<"<< endl;
		#endif
		c=getNombreElements();
		cellule<T> *t;
		while(i<c){
			t=tete;
			tete=tete->suivant;
			delete t;
			i++;
		}
	}

	template<class T> 
	int ArrayList<T>::getNombreElements()const{
		int a=0;
		cellule<T> *t;
		t=tete;
		while(t!=NULL){
			a++;
			t=t->suivant;
		}
		return a;
	}
	template<class T> 
	T& ArrayList<T>::getElement(int ind)const throw(Exception)
	{
		int c,i=0;
		c=getNombreElements();
		if(ind<=(c-1)){
			cellule<T> *t;
			t=tete;
			while(i<ind){
				t=t->suivant;
				i++;
			}
			return t->valeur;
		}
		else{
			throw Exception("indice incorrecte");
		}
	}

	template<class T> 
	bool ArrayList<T>::estVide(){
		if(tete==NULL){
			return 1;
		}
		return 0;
	}
	template<class T> 
	void ArrayList<T>::Affiche() {
		int i=0,c;
		c=getNombreElements();
		while(i<c){
			cout<<i<<":"<<getElement(i)<<endl;
			i++;
		}
	}
	template<class T> 
	void ArrayList<T>::insereElement(const T & val){
		cellule<T> *p = new cellule<T>;
	    p->valeur = val;
	    p->suivant = NULL;

	    if (estVide()) {
	        // Si la liste est vide, la tête pointe vers le nouvel élément
	        tete = p;
	    } else {
	        cellule<T> *t = tete;
	        while (t->suivant != NULL) {
	            t = t->suivant; // Parcourez la liste jusqu'à la dernière cellule
	        }
	        t->suivant = p; // Mettez à jour le dernier élément pour qu'il pointe vers le nouveau
	    }
	}
	template<class T> 
	T ArrayList<T>::retireElement(int ind) throw(Exception)
	{
	    cellule<T> *t = tete;
	    cellule<T> *p = nullptr;
	    int c=getNombreElements();
	    if(ind<=(c-1))
	    {
		    while (ind > 0 && t != nullptr) {
		        p = t;
		        t = t->suivant;
		        ind--;
		    }

		    if (t != nullptr) {
		        if (p == nullptr) {
		            // Le premier élément est retiré
		            tete = t->suivant;
		        } else {
		            p->suivant = t->suivant;
		        }
		        T valeurRetiree = t->valeur;
		        delete t;
		        return valeurRetiree;
		    }
		}
		else{
			throw Exception("indice incorrecte");
		}
	}
	template<class T> 
	ArrayList<T>& ArrayList<T>::operator=(ArrayList<T>& A){
		int i=0,c;
		c=getNombreElements();
		cellule<T> *t;
		while(i<c){
			t=tete;
			tete=tete->suivant;
			delete[] t;
			i++;
		}
		i=0;
		c=A.getNombreElements();
		while(i<c){
			insereElement(A.getElement(i));
			i++;
		}
		return *this;
	}
	template class ArrayList<int>;
	template class ArrayList<Couleur>;
	template class ArrayList<Image*>;