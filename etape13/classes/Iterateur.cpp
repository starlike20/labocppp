#include "Iterateur.h"	
#include "Couleur.h"
#include "Image.h"
//---------------------------------
//------ constructeur
//---------------------------------	
		template<class T> 
		Iterateur<T>::Iterateur(ArrayList<T> &A):liste(A){
			#ifdef DEBUG
			cout <<">> Iterateur:constructeur de liste<<"<< endl;
			#endif
			pcur=liste.tete;
		}
		template<class T> 
		Iterateur<T>::~Iterateur(){
			#ifdef DEBUG
			cout <<">> Iterateur:destructeur de liste<<"<< endl;
			#endif
			if (pcur != NULL) {
      			delete pcur;
   			}
		}

		template<class T> 
		T Iterateur<T>::reset(){
			pcur=liste.tete;
			return pcur->valeur;
		}
		template<class T> 
		bool Iterateur<T>::end(){
			if(pcur==NULL){
				return 1;
			}
			return 0;
		}
		template<class T> 
		int Iterateur<T>::operator++(){
			if(pcur){
				pcur=pcur->suivant;
				return 1;
			}
			else return 0;
		}
		template<class T>
		int Iterateur<T>::operator++(int b){
			return ++(*this)==1;
		}
		template<class T> 
		Iterateur<T>::operator T() const{
			return pcur->valeur;
		}
		template<class T> 
		T& Iterateur<T>::operator&(void){
			return pcur->valeur;
		}
	template class Iterateur<int>;
	template class Iterateur<Couleur>;
	template class Iterateur<Image*>;