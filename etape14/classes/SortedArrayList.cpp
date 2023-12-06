#include "SortedArrayList.h"
template class SortedArrayList<int>;

template<class T> 
SortedArrayList<T>::SortedArrayList(): ArrayList<T>(){
	
}

template<class T> 
void SortedArrayList<T>::insereElement(T const & val) {
    cellule<T> *p = new cellule<T>;
    p->valeur = val;
    p->suivant = nullptr;

    if (this->estVide() || val < this->tete->valeur) {
        // Cas où la liste est vide ou l'élément doit être inséré au début
        p->suivant = this->tete;
        this->tete = p;
    } else {
        cellule<T> *precedent = nullptr;
        cellule<T> *courant = this->tete;

        // Trouver l'endroit approprié pour insérer l'élément
        while (courant != nullptr && courant->valeur < val) {
            precedent = courant;
            courant = courant->suivant;
        }

        // Insérer l'élément à l'endroit approprié
        p->suivant = courant;
        if (precedent != nullptr) {
            precedent->suivant = p;
        } else {
            // Cas où l'élément doit être inséré au début de la liste
            this->tete = p;
        }
    }
}