#include "Traitements.h"
#include <string.h>
//methode

ImageB Traitements::Seuillage(const ImageNG& imageIn, int seuil){
		ImageB img;
		char nom[40],in[10];

		strcpy(nom,imageIn.getNom());
		strcat(nom,"-seuil");
		sprintf(in, "%d", seuil);
		strcat(nom,in);

		img.setId(imageIn.getId());
		img.setNom(nom);
		img.setDimension(imageIn.getDimension());
		int i,j;
		for(i=0;i<imageIn.getDimension().getLargeur();i++){
			for(j=0;j<imageIn.getDimension().getHauteur();j++){
				if(imageIn.getPixel(i,j)>=seuil){
					img.setPixel(i,j,1);
				}
				else{
					img.setPixel(i,j,0);
				}
			}
		}
		return img;
	}

ImageNG Traitements::FiltreMoyenneur(const ImageNG& imageIn, int taille) {
	int i,j,x,y,n,m;
	ImageNG imageout(imageIn);
	if(taille%2==1){
		n=taille/2;
		int debutl,debutcol;
		for(i=0;i<imageIn.getDimension().getLargeur();i++){
			for(j=0;j<imageIn.getDimension().getHauteur();j++){
				m=0;
				debutl=i-n;
				debutcol=j-n;
				for(x=debutl;(x-debutl)<taille;x++){
					for(y=debutcol;(y-debutcol)<taille;y++)
					{
						if(x>=0 && x<imageIn.getDimension().getLargeur()){
							if(y>=0 && y<imageIn.getDimension().getHauteur()){
								m=m+imageIn.getPixel(x,y);
							}
						}
					}
				}
				m=m/(taille*taille);
				imageout.setPixel(i,j,m);
			}
		}
	}
	else{
		cout<<"taille invalide"<<endl;
	}
	return imageout;
}
ImageNG Traitements::FiltreMedian(const ImageNG& imageIn, int taille) {
	int i,j,x,y,n,m=1;
	ImageNG imageout(imageIn);
	if(taille%2==1){
		n=taille/2;
		int debutl,debutcol;
		for(i=0;i<imageIn.getDimension().getLargeur();i++){
			for(j=0;j<imageIn.getDimension().getHauteur();j++){
				SortedArrayList<int> liste;
				m=0;
				debutl=i-n;
				debutcol=j-n;
				for(x=debutl;(x-debutl)<taille ;x++){
					for(y=debutcol;(y-debutcol)<taille;y++)
					{
						if(x>=0 && x<imageIn.getDimension().getLargeur()){
							if(y>=0 && y<imageIn.getDimension().getHauteur()){
								liste.insereElement(imageIn.getPixel(x,y));
								m++;
							}
						}
					}
				}
				imageout.setPixel(i,j,liste.getElement(m/2));
			}
		}
	}
	else{
		cout<<"taille invalide"<<endl;
	}
	return imageout;
}
ImageNG Traitements::Erosion(const ImageNG& imageIn, int taille) {
	int i,j,x,y,n,m=255;
	char nom[40],in[10];
	ImageNG imageout(imageIn);
	strcpy(nom,imageIn.getNom());
	strcat(nom,"-erode");
	sprintf(in, "%d", taille);
	strcat(nom,in);

	imageout.setNom(nom);
	if(taille%2==1){
		n=taille/2;
		int debutl,debutcol;
		for(i=0;i<imageIn.getDimension().getLargeur();i++){
			for(j=0;j<imageIn.getDimension().getHauteur();j++){
				SortedArrayList<int> liste;
				m=0;
				debutl=i-n;
				debutcol=j-n;
				for(x=debutl;(x-debutl)<taille ;x++){
					for(y=debutcol;(y-debutcol)<taille;y++)
					{
						if(x>=0 && x<imageIn.getDimension().getLargeur()){
							if(y>=0 && y<imageIn.getDimension().getHauteur()){
								if(m>imageIn.getPixel(x,y)){
									m=imageIn.getPixel(x,y);
								}
							}
						}
					}
				}
				imageout.setPixel(i,j,m);
			}
		}
	}
	else{
		cout<<"taille invalide"<<endl;
	}
	return imageout;

}
ImageNG Traitements::Dilatation(const ImageNG& imageIn, int taille)
{
	int i,j,x,y,n,m=0;
	ImageNG imageout(imageIn);
	char nom[40],in[10];
	strcpy(nom,imageIn.getNom());
	strcat(nom,"-dilate");
	sprintf(in, "%d", taille);
	strcat(nom,in);

	imageout.setNom(nom);
	if(taille%2==1){
		n=taille/2;
		int debutl,debutcol;
		for(i=0;i<imageIn.getDimension().getLargeur();i++){
			for(j=0;j<imageIn.getDimension().getHauteur();j++){
				SortedArrayList<int> liste;
				m=0;
				debutl=i-n;
				debutcol=j-n;
				for(x=debutl;(x-debutl)<taille ;x++){
					for(y=debutcol;(y-debutcol)<taille;y++)
					{
						if(x>=0 && x<imageIn.getDimension().getLargeur()){
							if(y>=0 && y<imageIn.getDimension().getHauteur()){
								if(m<imageIn.getPixel(x,y)){
									m=imageIn.getPixel(x,y);
								}
							}
						}
					}
				}
				imageout.setPixel(i,j,m);
			}
		}
	}
	else{
		cout<<"taille invalide"<<endl;
	}
	return imageout;
}
ImageNG Traitements::Negatif(const ImageNG& imageIn){
	int i,j;
	ImageNG imageout(imageIn);
	char nom[40];
	strcpy(nom,imageIn.getNom());
	strcat(nom,"-negatif");
	for(i=0;i<imageIn.getDimension().getLargeur();i++){
		for(j=0;j<imageIn.getDimension().getHauteur();j++){
			imageout.setPixel(i,j,255-imageout.getPixel(i,j));
		}
	}
	return imageout;
}