#include "mainwindowphotoshop.h"
#include "ui_mainwindowphotoshop.h"

#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QScreen>
#include <QRect>
#include <QPixmap>
#include <QColorDialog>
#include <filesystem>


#include "ImageNG.h"
#include "ImageRGB.h"
#include "ImageB.h"
#include "PhotoShop.h"
#include "Iterateur.h"
#include "Traitements.h"
#include "XYException.h"


MainWindowPhotoShop::MainWindowPhotoShop(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindowPhotoShop)
{
    int n;
    ui->setupUi(this);
    setTitre("Mini-PhotoShop  en C++");

    // Centrage de la fenetre
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->availableGeometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);
    setFixedSize(1021,845);

    // Configuration de la table des images
    ui->tableWidgetImages->setColumnCount(4);
    ui->tableWidgetImages->setRowCount(0);
    QStringList labelsTableOptions;
    labelsTableOptions << "Id" << "Type" << "Dimension" << "Nom";
    ui->tableWidgetImages->setHorizontalHeaderLabels(labelsTableOptions);
    ui->tableWidgetImages->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetImages->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetImages->horizontalHeader()->setVisible(true);
    ui->tableWidgetImages->horizontalHeader()->setDefaultSectionSize(100);
    ui->tableWidgetImages->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetImages->verticalHeader()->setVisible(false);
    ui->tableWidgetImages->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Intialisation des scrollArea
    
    setImageNG("selection");
    setImageNG("operande1");
    setImageNG("operande2");
    setImageNG("resultat");
    

    // ComboBox des traitements disponibles
    ajouteTraitementDisponible("Eclaircir (+ val)");
    ajouteTraitementDisponible("Eclaircir (++)");
    ajouteTraitementDisponible("Assombrir (- val)");
    ajouteTraitementDisponible("Assombrir (--)");
    ajouteTraitementDisponible("Différence");
    ajouteTraitementDisponible("Comparaison (==)");
    ajouteTraitementDisponible("Comparaison (<)");
    ajouteTraitementDisponible("Comparaison (>)");
    ajouteTraitementDisponible("Seuillage");
    ajouteTraitementDisponible("Filtre moyenneur");
    ajouteTraitementDisponible("Filtre médian");
    ajouteTraitementDisponible("Erosion");
    ajouteTraitementDisponible("Dilatation");
    ajouteTraitementDisponible("Négatif");

    // Etape 14 (TO DO)
    // Restauration bibliothèque via fichier de sauvegarde
    n=PhotoShop::getInstance().Load();
    if(n>0){
      affichetable();
    }

    // TESTS DEMOS A SUPPRIMER
    /*ajouteTupleTableImages(3,"NG","256x256","lena.bmp");
    setResultatBoolean(1);*/
}

MainWindowPhotoShop::~MainWindowPhotoShop()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Méthodes de la fenêtre (ne pas modifier) ///////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::setTitre(string titre)
{
  this->setWindowTitle(titre.c_str());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::setNomImage(string nom)
{
  ui->lineEditNom->setText(QString::fromStdString(nom));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string MainWindowPhotoShop::getNomImage() const
{
  return ui->lineEditNom->text().toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::setParametresImageNG(int max,int min,int luminance,float contraste)
{
  if (max == -1)
  {
    ui->lineEditMax->setText("");
    ui->lineEditMin->setText("");
    ui->lineEditLuminance->setText("");
    ui->lineEditContraste->setText("");
    return;
  }
  char tmp[20];
  sprintf(tmp,"%d",max);
  ui->lineEditMax->setText(tmp);
  sprintf(tmp,"%d",min);
  ui->lineEditMin->setText(tmp);
  sprintf(tmp,"%d",luminance);
  ui->lineEditLuminance->setText(tmp);
  sprintf(tmp,"%f",contraste);
  ui->lineEditContraste->setText(tmp);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindowPhotoShop::setImageNG(string destination,const ImageNG* imageng)
{
    QPixmap * pixmap = NULL;
    if (imageng != NULL)
    {
      // Creation du QPixmap
      int largeur = imageng->getDimension().getLargeur();
      int hauteur = imageng->getDimension().getHauteur();
      QImage im1(largeur,hauteur,QImage::Format_RGB32);
      for(int x=0 ; x<largeur ; x++)
        for(int y=0 ; y<hauteur ; y++)
        {
          int valeur = imageng->getPixel(x,y);
          im1.setPixel(x,y,qRgb(valeur,valeur,valeur));
        }
     pixmap = new QPixmap(QPixmap::fromImage(im1));
    }

    // Mise en place du QPixmap
    QLabel* label = new QLabel();
    label->setAlignment(Qt::AlignCenter);
    if (pixmap) label->setPixmap(*pixmap);
    else label->setText("vide");
    if (destination == "selection") ui->scrollAreaSelection->setWidget(label);
    if (destination == "operande1") ui->scrollAreaOperande1->setWidget(label);
    if (destination == "operande2") ui->scrollAreaOperande2->setWidget(label);
    if (destination == "resultat") ui->scrollAreaResultat->setWidget(label);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::setImageRGB(string destination,const ImageRGB* imagergb)
{
    QPixmap * pixmap = NULL;
    if (imagergb != NULL)
    {
      // Creation du QPixmap
      int largeur = imagergb->getDimension().getLargeur();
      int hauteur = imagergb->getDimension().getHauteur();
      QImage im1(largeur,hauteur,QImage::Format_RGB32);
      for(int x=0 ; x<largeur ; x++)
        for(int y=0 ; y<hauteur ; y++)
        {
          Couleur valeur = imagergb->getPixel(x,y);
          im1.setPixel(x,y,qRgb(valeur.getRouge(),valeur.getVert(),valeur.getBleu()));
        }
     pixmap = new QPixmap(QPixmap::fromImage(im1));
    }

    // Mise en place du QPixmap
    QLabel* label = new QLabel();
    label->setAlignment(Qt::AlignCenter);
    if (pixmap) label->setPixmap(*pixmap);
    else label->setText("vide");
    if (destination == "selection") ui->scrollAreaSelection->setWidget(label);
    if (destination == "operande1") ui->scrollAreaOperande1->setWidget(label);
    if (destination == "operande2") ui->scrollAreaOperande2->setWidget(label);
    if (destination == "resultat") ui->scrollAreaResultat->setWidget(label);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::setImageB(string destination,const ImageB* imageb)
{
    QPixmap * pixmap = NULL;
    if (imageb != NULL)
    {
      // Creation du QPixmap
      int largeur = imageb->getDimension().getLargeur();
      int hauteur = imageb->getDimension().getHauteur();
      QImage im1(largeur,hauteur,QImage::Format_RGB32);
      for(int x=0 ; x<largeur ; x++)
        for(int y=0 ; y<hauteur ; y++)
        {
          bool valeur = imageb->getPixel(x,y);
          if (valeur) im1.setPixel(x,y,qRgb(ImageB::couleurTrue.getRouge(),ImageB::couleurTrue.getVert(),ImageB::couleurTrue.getBleu()));
          else im1.setPixel(x,y,qRgb(ImageB::couleurFalse.getRouge(),ImageB::couleurFalse.getVert(),ImageB::couleurFalse.getBleu()));
        }
     pixmap = new QPixmap(QPixmap::fromImage(im1));
    }

    // Mise en place du QPixmap
    QLabel* label = new QLabel();
    label->setAlignment(Qt::AlignCenter);
    if (pixmap) label->setPixmap(*pixmap);
    else label->setText("vide");
    if (destination == "selection") ui->scrollAreaSelection->setWidget(label);
    if (destination == "operande1") ui->scrollAreaOperande1->setWidget(label);
    if (destination == "operande2") ui->scrollAreaOperande2->setWidget(label);
    if (destination == "resultat") ui->scrollAreaResultat->setWidget(label);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::setResultatBoolean(int val)
{
  if (val == 1) // vrai
  {
    ui->checkBoxResultat->setChecked(true);
    ui->checkBoxResultat->setText("VRAI");
    ui->checkBoxResultat->setStyleSheet("background-color: lightgreen;border: 1px solid black;");
    return;
  }
  if (val == 0) // faux
  {
    ui->checkBoxResultat->setChecked(false);
    ui->checkBoxResultat->setText("FAUX");
    ui->checkBoxResultat->setStyleSheet("background-color: red;border: 1px solid black;");
    return;
  }
  // ni vrai, ni faux
  ui->checkBoxResultat->setChecked(false);
  ui->checkBoxResultat->setText("Résultat");
  ui->checkBoxResultat->setStyleSheet("background-color: lightyellow;border: 1px solid black;");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles Table des Images (ne pas modifier) ////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::ajouteTupleTableImages(int id,string type,string dimension,string nom)
{
    char Id[20];
    sprintf(Id,"%d",id);

    char Type[20];
    strcpy(Type,type.c_str());

    char Dimension[20];
    strcpy(Dimension,dimension.c_str());

    char Nom[80];
    strcpy(Nom,nom.c_str());

    // Ajout possible
    int nbLignes = ui->tableWidgetImages->rowCount();
    nbLignes++;
    ui->tableWidgetImages->setRowCount(nbLignes);
    ui->tableWidgetImages->setRowHeight(nbLignes-1,20);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(Id);
    ui->tableWidgetImages->setItem(nbLignes-1,0,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(Type);
    ui->tableWidgetImages->setItem(nbLignes-1,1,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(Dimension);
    ui->tableWidgetImages->setItem(nbLignes-1,2,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(Nom);
    ui->tableWidgetImages->setItem(nbLignes-1,3,item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::videTableImages()
{
    ui->tableWidgetImages->setRowCount(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MainWindowPhotoShop::getIndiceImageSelectionnee()
{
    QModelIndexList liste = ui->tableWidgetImages->selectionModel()->selectedRows();
    if (liste.size() == 0) return -1;
    QModelIndex index = liste.at(0);
    int indice = index.row();
    return indice;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Combox des traitements disponibles (ne pas modifier) ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::ajouteTraitementDisponible(string operation)
{
    ui->comboBoxTraitements->addItem(operation.c_str());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::videTraitementsDisponibles()
{
    ui->comboBoxTraitements->clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string MainWindowPhotoShop::getTraitementSelectionne() const
{
    return ui->comboBoxTraitements->currentText().toStdString();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions permettant d'afficher des boites de dialogue (ne pas modifier) ///////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::dialogueMessage(const char* titre,const char* message)
{
   QMessageBox::information(this,titre,message);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::dialogueErreur(const char* titre,const char* message)
{
   QMessageBox::critical(this,titre,message);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string MainWindowPhotoShop::dialogueDemandeTexte(const char* titre,const char* question)
{
    QString chaine = QInputDialog::getText(this,titre,question);
    return chaine.toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MainWindowPhotoShop::dialogueDemandeInt(const char* titre,const char* question)
{
    return QInputDialog::getInt(this,titre,question);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
float MainWindowPhotoShop::dialogueDemandeFloat(const char* titre,const char* question)
{
    return QInputDialog::getDouble(this,titre,question);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string MainWindowPhotoShop::dialogueDemandeFichierOuvrir(const char* question)
{
  QString fileName = QFileDialog::getOpenFileName(this,question, "", "Tous les fichiers (*.*)");
  return fileName.toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string MainWindowPhotoShop::dialogueDemandeFichierEnregistrer(const char* question)
{
  QString fileName = QFileDialog::getSaveFileName(this,question, "", "Tous les fichiers (*.*)");
  return fileName.toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::dialogueDemandeCouleur(const char* message,int* pRouge,int* pVert,int* pBleu)
{
  QColor color = QColorDialog::getColor(Qt::red,this,message);
  *pRouge = color.red();
  *pVert = color.green();
  *pBleu = color.blue();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Clic sur la croix de la fenêtre ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::closeEvent(QCloseEvent *event)
{
  if (event == NULL) {} // pour éviter le warning à la compilation
  // Etape 14 (TO DO)
  PhotoShop::getInstance().Save();
  on_actionReset_triggered();
  QApplication::exit();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les items de menu //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionQuitter_triggered()
{
  // Etape 14 (TO DO)
  PhotoShop::getInstance().Save();
  on_actionReset_triggered();
  QApplication::exit();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionCharger_ImageNB_triggered()
{
  // Etape 11 (TO DO)
  int j=0,i;
  string nom,m,type,dimension;
  char mn[150],n[150];
  nom=dialogueDemandeFichierOuvrir("ouvrire l'image");
  if (nom.length() > 4) {
    m = nom.substr(nom.length() - 4);

    m=nom.substr(nom.length() - 4);
    if (tolower(m[0]) != tolower(".bmp"[0]) || tolower(m[1]) !=tolower(".bmp"[1]) || tolower(m[2]) != tolower(".bmp"[2]) || tolower(m[3]) != tolower(".bmp"[3])){
      if (tolower(m[0]) != tolower(".jpg"[0]) || tolower(m[1]) !=tolower(".jpg"[1]) || tolower(m[2]) != tolower(".jpg"[2]) || tolower(m[3]) != tolower(".jpg"[3])){
        if (tolower(m[0]) != tolower(".png"[0]) || tolower(m[1]) !=tolower(".png"[1]) || tolower(m[2]) != tolower(".png"[2]) || tolower(m[3]) != tolower(".png"[3])){
          j=-1;
        }
      }
    }
    if(j==-1){
      dialogueErreur("erreur de chargement","les type autoriser son :bmp ,jpg et png");
    }
    else{
      strcpy(mn,nom.c_str());
      i=nom.find_last_of("/\\");
      m=nom.substr(i + 1);
      strcpy(n,m.c_str());
      ImageNG*img;
      img=new ImageNG(1,mn);
      img->importFromFile(mn);
      PhotoShop::getInstance().ajouteImage(img);
      affichetable();
    }

  }
  else{

    dialogueErreur("erreur de chargement","l'image n'existe pas dans le repertoire");
  }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionCharger_ImageRGB_triggered()
{
  // Etape 11 (TO DO)
  int j=0,i;
  string nom,m,type,dimension;
  char mn[150],n[150];
  nom=dialogueDemandeFichierOuvrir("ouvrire l'image");
  if (nom.length() > 4) {
    m = nom.substr(nom.length() - 4);

    m=nom.substr(nom.length() - 4);
    if (tolower(m[0]) != tolower(".bmp"[0]) || tolower(m[1]) !=tolower(".bmp"[1]) || tolower(m[2]) != tolower(".bmp"[2]) || tolower(m[3]) != tolower(".bmp"[3])){
      if (tolower(m[0]) != tolower(".jpg"[0]) || tolower(m[1]) !=tolower(".jpg"[1]) || tolower(m[2]) != tolower(".jpg"[2]) || tolower(m[3]) != tolower(".jpg"[3])){
        if (tolower(m[0]) != tolower(".png"[0]) || tolower(m[1]) !=tolower(".png"[1]) || tolower(m[2]) != tolower(".png"[2]) || tolower(m[3]) != tolower(".png"[3])){
          j=-1;
        }
      }
    }
    if(j==-1){
      dialogueErreur("erreur de chargement","les type autoriser son :bmp ,jpg et png");
    }
    else{
      strcpy(mn,nom.c_str());
      i=nom.find_last_of("/\\");
      m=nom.substr(i + 1);
      strcpy(n,m.c_str());
      ImageRGB*img;
      img=new ImageRGB(1,mn);
      img->importFromFile(mn);
      PhotoShop::getInstance().ajouteImage(img);
      affichetable();
    }

  }
  else{

    dialogueErreur("erreur de chargement","l'image n'existe pas dans le repertoire");
  }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionEnregistrer_ImageNB_triggered()
{
  // Etape 11 (TO DO)
int i,j,n;
  string nom,m;
  n=getIndiceImageSelectionnee();
  char mn[150],format[4];
  if(n!=-1)
  {
    nom=dialogueDemandeFichierEnregistrer("sauvegarder sous");
    if(nom.length() > 4) {
      
      m=nom.substr(nom.length() - 4);
      if (tolower(m[0]) != tolower(".bmp"[0]) || tolower(m[1]) !=tolower(".bmp"[1]) || tolower(m[2]) != tolower(".bmp"[2]) || tolower(m[3]) != tolower(".bmp"[3])){
        j=1;
        if (tolower(m[0]) != tolower(".jpg"[0]) || tolower(m[1]) !=tolower(".jpg"[1]) || tolower(m[2]) != tolower(".jpg"[2]) || tolower(m[3]) != tolower(".jpg"[3])){
          j=2;
          if (tolower(m[0]) != tolower(".png"[0]) || tolower(m[1]) !=tolower(".png"[1]) || tolower(m[2]) != tolower(".png"[2]) || tolower(m[3]) != tolower(".png"[3])){
            j=-1;
          }
        }
      }
      if(j==-1){
        dialogueErreur("erreur de sauvegarde","les type autoriser son :bmp ,jpg et png");
      }
      else{
        if(j==0){
          strcpy(format,"BMP");
        }
        else{
          if(j==1){
            strcpy(format,"JPG");
          }
          else{
            strcpy(format,"PNG");
          }
        }
        strcpy(mn,nom.c_str());
        //n=getNombreElements();
        Image* p=PhotoShop::getInstance().getImageParIndice(n);
        ImageNG* pB = dynamic_cast<ImageNG*>(p);
        if (pB != NULL)
        {
          pB->exportToFile(mn,format);
        }
        else{
          dialogueErreur("erreur de sauvegarde","selectionner le bon type");
        }
      }

    }
    else{

      dialogueErreur("erreur de sauvegarde","erreur de formatage");
    }
  }
  else{
    dialogueErreur("erreur de sauvegarde","selectionner une ligne");
  }

}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionEnregistrer_ImageRGB_triggered()
{
  // Etape 11 (TO DO)
  int i,j,n;
  string nom,m;
  n=getIndiceImageSelectionnee();
  char mn[150],format[4];
  if(n!=-1)
  {
    nom=dialogueDemandeFichierEnregistrer("sauvegarder sous");
    if(nom.length() > 4) {
      
      m=nom.substr(nom.length() - 4);
      if (tolower(m[0]) != tolower(".bmp"[0]) || tolower(m[1]) !=tolower(".bmp"[1]) || tolower(m[2]) != tolower(".bmp"[2]) || tolower(m[3]) != tolower(".bmp"[3])){
        j=1;
        if (tolower(m[0]) != tolower(".jpg"[0]) || tolower(m[1]) !=tolower(".jpg"[1]) || tolower(m[2]) != tolower(".jpg"[2]) || tolower(m[3]) != tolower(".jpg"[3])){
          j=2;
          if (tolower(m[0]) != tolower(".png"[0]) || tolower(m[1]) !=tolower(".png"[1]) || tolower(m[2]) != tolower(".png"[2]) || tolower(m[3]) != tolower(".png"[3])){
            j=-1;
          }
        }
      }
      if(j==-1){
        dialogueErreur("erreur de sauvegarde","les type autoriser son :bmp ,jpg et png");
      }
      else{
        if(j==0){
          strcpy(format,"BMP");
        }
        else{
          if(j==1){
            strcpy(format,"JPG");
          }
          else{
            strcpy(format,"PNG");
          }
        }
        strcpy(mn,nom.c_str());
        //n=getNombreElements();
        Image* p=PhotoShop::getInstance().getImageParIndice(n);
        ImageRGB* pB = dynamic_cast<ImageRGB*>(p);
        if (pB != NULL)
        {
          pB->exportToFile(mn,format);
        }
        else{
          dialogueErreur("erreur de sauvegarde","selectionner le bon type");
        }
      }

    }
    else{

      dialogueErreur("erreur de sauvegarde","erreur de formatage");
    }
  }
  else{
    dialogueErreur("erreur de sauvegarde","selectionner une ligne");
  }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionEnregistrer_ImageB_triggered()
{
  // Etape 11 (TO DO)
  int j,n;
  string nom,m;
  n=getIndiceImageSelectionnee();
  char mn[150],format[4];
  if(n!=-1)
  {
    nom=dialogueDemandeFichierEnregistrer("sauvegarder sous");
    if(nom.length() > 4) {
      
      m=nom.substr(nom.length() - 4);
      if (tolower(m[0]) != tolower(".bmp"[0]) || tolower(m[1]) !=tolower(".bmp"[1]) || tolower(m[2]) != tolower(".bmp"[2]) || tolower(m[3]) != tolower(".bmp"[3])){
        j=1;
        if (tolower(m[0]) != tolower(".jpg"[0]) || tolower(m[1]) !=tolower(".jpg"[1]) || tolower(m[2]) != tolower(".jpg"[2]) || tolower(m[3]) != tolower(".jpg"[3])){
          j=2;
          if (tolower(m[0]) != tolower(".png"[0]) || tolower(m[1]) !=tolower(".png"[1]) || tolower(m[2]) != tolower(".png"[2]) || tolower(m[3]) != tolower(".png"[3])){
            j=-1;
          }
        }
      }
      if(j==-1){
        dialogueErreur("erreur de sauvegarde","les type autoriser son :bmp ,jpg et png");
      }
      else{
        if(j==0){
          strcpy(format,"BMP");
        }
        else{
          if(j==1){
            strcpy(format,"JPG");
          }
          else{
            strcpy(format,"PNG");
          }
        }
        strcpy(mn,nom.c_str());
        //n=getNombreElements();
        Image* p=PhotoShop::getInstance().getImageParIndice(n);
        ImageB* pB = dynamic_cast<ImageB*>(p);
        if (pB != NULL)
        {
          pB->exportToFile(mn,format);
        }
        else{
          dialogueErreur("erreur de sauvegarde","selectionner le bon type");
        }
      }

    }
    else{

      dialogueErreur("erreur de sauvegarde","erreur de formatage");
    }
  }
  else{
    dialogueErreur("erreur de sauvegarde","selectionner une ligne");
  }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionImage_selectionn_e_triggered()
{
  // Etape 11 (TO DO)
  int n;
  string m,type,dimension;
  n=getIndiceImageSelectionnee();
  if(n!=-1){
    if(PhotoShop::getInstance().getImageParIndice(n)!=NULL){
      PhotoShop::getInstance().supprimeImageParIndice(n);
      videTableImages();
      PhotoShop::getInstance().i.reset();
      Image*im;
      ImageB* pB;
      ImageNG* pNG;
      ImageRGB* pRGB;
      while(!PhotoShop::getInstance().i.end()){
        im=PhotoShop::getInstance().i;
        pB = dynamic_cast<ImageB*>(im);
        if (pB != NULL)
        {
          type="B";
        }
        pNG = dynamic_cast<ImageNG*>(im);
        if (pNG != NULL) 
        {
          type="NG";
        }
        pRGB = dynamic_cast<ImageRGB*>(im);
        if (pRGB != NULL) 
        {
          type="RGB";
        }
        m=im->getNom();
        dimension=to_string(im->getDimension().getLargeur())+"X"+to_string(im->getDimension().getHauteur());
        ajouteTupleTableImages(im->getId(),type,dimension,m);
        PhotoShop::getInstance().i++;
      }
    }
    else{
      dialogueErreur("suppression","l'id n'existe pas");
    }
  }
  else{
    dialogueErreur("erreur","aucun element selectionner");
  }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionImage_par_id_triggered()
{
  // Etape 11 (TO DO)
  int n;
  string m,type,dimension;
  n=dialogueDemandeInt("suppression","entrez l'indice de l'element a supprimer");
  if(PhotoShop::getInstance().getImageParId(n)!=NULL){
    PhotoShop::getInstance().supprimeImageParId(n);
    videTableImages();
    PhotoShop::getInstance().i.reset();
    Image*im;
    ImageB* pB;
    ImageNG* pNG;
    ImageRGB* pRGB;
    while(!PhotoShop::getInstance().i.end()){
      im=PhotoShop::getInstance().i;
      pB = dynamic_cast<ImageB*>(im);
      if (pB != NULL)
      {
        type="B";
      }
      pNG = dynamic_cast<ImageNG*>(im);
      if (pNG != NULL) 
      {
        type="NG";
      }
      pRGB = dynamic_cast<ImageRGB*>(im);
      if (pRGB != NULL) 
      {
        type="RGB";
      }
      m=im->getNom();
      dimension=to_string(im->getDimension().getLargeur())+"X"+to_string(im->getDimension().getHauteur());
      ajouteTupleTableImages(im->getId(),type,dimension,m);
      PhotoShop::getInstance().i++;
    }
  }
  else{
    dialogueErreur("suppression","l'id n'existe pas");
  }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionCouleur_TRUE_pour_ImageB_triggered()
{
  // Etape 12 (TO DO)
  int r,v,b;
  dialogueDemandeCouleur("entrez la couleur true",&r,&v,&b);
  ImageB::couleurTrue=Couleur(r,v,b);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionCouleur_FALSE_pour_imageB_triggered()
{
  // Etape 12 (TO DO)
   int r,v,b;
  dialogueDemandeCouleur("entrez la couleur false",&r,&v,&b);
  ImageB::couleurFalse=Couleur(r,v,b);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionImporterCSV_triggered()
{
  // Etape 13 (TO DO)
  int n;
  string nn;
  char nnn[30];
  n=PhotoShop::getInstance().importeImages("n.csv");
  nn=to_string(n);
  strcpy(nnn,nn.c_str());
  strcat(nnn," on été importé");
  affichetable();
  dialogueMessage("les nombre d'image importe",nnn);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionReset_triggered()
{
  // Etape 14 (TO DO)
  Image*p;
  if(PhotoShop::getInstance().getImageParIndice(0)!=NULL){
    PhotoShop::getInstance().reset();
    videTableImages();
    setImageNG("selection");
    setImageNG("operande1");
    setImageNG("operande2");
    setImageNG("resultat");
    PhotoShop::operande1=NULL;
    PhotoShop::operande2=NULL;
    if (PhotoShop::resultat!=NULL)
    {
      delete PhotoShop::resultat;
    }
    setNomImage(" ");
    ImageB::couleurTrue=Couleur::BLANC;
    ImageB::couleurFalse=Couleur::NOIR;
  }

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions selection sur la table des images ////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_tableWidgetImages_itemSelectionChanged()
{
  // Etape 11 (TO DO)
  string nom;
  int n;
  Image*i;
  n=getIndiceImageSelectionnee();
  if(n!=-1){
    if(PhotoShop::getInstance().getImageParIndice(n)!=NULL){
      i=PhotoShop::getInstance().getImageParIndice(n);
      nom=i->getNom();
      setNomImage(nom);
      ImageB* pB = dynamic_cast<ImageB*>(i);
      if (pB != NULL)
      {
        setImageB("selection",pB);
        setParametresImageNG(-1,-1,-1,0.0);
      }
      ImageNG* pN = dynamic_cast<ImageNG*>(i);
      if (pN != NULL)
      {
        setImageNG("selection",pN);
        setParametresImageNG(pN->getMaximum(),pN->getMinimum(),pN->getLuminance(),pN->getContraste());
      }
      ImageRGB* pR = dynamic_cast<ImageRGB*>(i);
      if (pR != NULL)
      {
        setImageRGB("selection",pR);
        setParametresImageNG(-1,-1,-1,0.0);
      }
    } 
  } 
  else{
    setParametresImageNG(-1,-1,-1,0.0);
  }

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les boutons ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonModifierNom_clicked()
{
  // Etape 11 (TO DO)
  int n;
  string nom;
  char mn[150];
  nom=getNomImage();
  n=getIndiceImageSelectionnee();
  if(n!=-1){
    strcpy(mn,nom.c_str());
    PhotoShop::getInstance().getImageParIndice(n)->setNom(mn);
  }
  else{
    dialogueErreur("erreur modification","aucune image selectionner");
  }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonOperande1_clicked()
{
    // Etape 12 (TO DO)
  int n;
  n=getIndiceImageSelectionnee();
  if(n!=-1){
    Image*i=PhotoShop::getInstance().getImageParIndice(n);
    ImageB* pB = dynamic_cast<ImageB*>(i);
    if (pB != NULL)
    {
      setImageB("operande1",pB);
      PhotoShop::operande1=pB;
    }
    ImageNG* pN = dynamic_cast<ImageNG*>(i);
    if (pN != NULL)
    {
      setImageNG("operande1",pN);
      PhotoShop::operande1=pN;
    }
    ImageRGB* pR = dynamic_cast<ImageRGB*>(i);
    if (pR != NULL)
    {
      setImageRGB("operande1",pR);
      PhotoShop::operande1=pR;
    }
  }
  else{
    dialogueErreur("selection","aucune image selectionnee");
  }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonSupprimeOperande1_clicked()
{
    // Etape 12 (TO DO)
  if(PhotoShop::operande1!= NULL)
  {
    Image*i=PhotoShop::getInstance().getImageParId(PhotoShop::operande1->getId());
    ImageB* pB = dynamic_cast<ImageB*>(i);
    if (pB != NULL)
    {
      setImageB("operande1",NULL);
      PhotoShop::operande1=NULL;
    }
    ImageNG* pN = dynamic_cast<ImageNG*>(i);
    if (pN != NULL)
    {
      setImageNG("operande1",NULL);
      PhotoShop::operande1=NULL;
    }
    ImageRGB* pR = dynamic_cast<ImageRGB*>(i);
    if (pR != NULL)
    {
      setImageRGB("operande1",NULL);
      PhotoShop::operande1=NULL;
    }
  }
  else{
    dialogueErreur("suppression","aucune image disponible");
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonOperande2_clicked()
{
    // Etape 12 (TO DO)
  int n;
  n=getIndiceImageSelectionnee();
  if(n!=-1){
    Image*i=PhotoShop::getInstance().getImageParIndice(n);
    ImageB* pB = dynamic_cast<ImageB*>(i);
    if (pB != NULL)
    {
      setImageB("operande2",pB);
      PhotoShop::operande2=pB;
    }
    ImageNG* pN = dynamic_cast<ImageNG*>(i);
    if (pN != NULL)
    {
      setImageNG("operande2",pN);
      PhotoShop::operande2=pN;
    }
    ImageRGB* pR = dynamic_cast<ImageRGB*>(i);
    if (pR != NULL)
    {
      setImageRGB("operande2",pR);
      PhotoShop::operande2=pR;
    }
  }
  else{
    dialogueErreur("selection","aucune image selectionnee");
  }


}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonSupprimerOperande2_clicked()
{
    // Etape 12 (TO DO)
  if(PhotoShop::operande2!= NULL)
  {
    Image*i=PhotoShop::getInstance().getImageParId(PhotoShop::operande1->getId());
    ImageB* pB = dynamic_cast<ImageB*>(i);
    if (pB != NULL)
    {
      setImageB("operande2",NULL);
      PhotoShop::operande2=NULL;
    }
    ImageNG* pN = dynamic_cast<ImageNG*>(i);
    if (pN != NULL)
    {
      setImageNG("operande2",NULL);
      PhotoShop::operande2=NULL;
    }
    ImageRGB* pR = dynamic_cast<ImageRGB*>(i);
    if (pR != NULL)
    {
      setImageRGB("operande2",NULL);
      PhotoShop::operande2=NULL;
    }
  }
  else{
    dialogueErreur("suppression","aucune image disponible");
  }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonResultat_clicked()
{
    // Etape 12 (TO DO)
    PhotoShop::getInstance().ajouteImage(PhotoShop::resultat);
    affichetable();
    PhotoShop::resultat=NULL;
    setImageNG("resultat",NULL);


}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonSupprimerResultat_clicked()
{
    // Etape 12 (TO DO)
    delete PhotoShop::resultat;
    PhotoShop::resultat=NULL;
    setImageNG("resultat",NULL);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonTraitement_clicked()
{
    // Etape 12 (TO DO)
  string n;
  int m;
  n=getTraitementSelectionne();
  delete PhotoShop::resultat;
  PhotoShop::resultat=NULL;
  setImageNG("resultat",NULL);
  setResultatBoolean(1);

  ImageRGB* pR1 = dynamic_cast<ImageRGB*>(PhotoShop::operande1);
  ImageRGB* pR2 = dynamic_cast<ImageRGB*>(PhotoShop::operande2);
  ImageRGB*pR;
  if(pR1!=NULL){
    pR=pR1;
  }
  else{
    pR=pR2;
  }
  if (pR != NULL){
    if(n=="Eclaircir (+ val)"){
      m=dialogueDemandeInt("Eclaircir","entrez un nombre positif");
      if(m>0){
        ImageRGB *resultat=new ImageRGB();
        ImageNG r,v,b;
        r=pR->getRouge()+m;
        v=pR->getVert()+m;
        b=pR->getBleu()+m;
        resultat->setRGB(r,v,b);
        PhotoShop::resultat=resultat;
        setImageRGB("resultat",resultat);
        setResultatBoolean(-1);
      }
      else{
        dialogueErreur("erreur de valeur","entrez un entier positif");
      }
    }
          if(n=="Eclaircir (++)"){
            ImageRGB *resultat=new ImageRGB();
            ImageNG r,v,b;
            r=pR->getRouge()++;
            v=pR->getVert()++;
            b=pR->getBleu()++;
            resultat->setRGB(r,v,b);
            PhotoShop::resultat=resultat;
            setImageRGB("resultat",resultat);
            setResultatBoolean(-1);
          }
          if(n=="Assombrir (- val)"){
            m=dialogueDemandeInt("Eclaircir","entrez un nombre positif");
            if(m>0){
              ImageRGB *resultat=new ImageRGB();
              ImageNG r,v,b;
              r=pR->getRouge()-m;
              v=pR->getVert()-m;
              b=pR->getBleu()-m;
              resultat->setRGB(r,v,b);
              PhotoShop::resultat=resultat;
              setImageRGB("resultat",resultat);
              setResultatBoolean(-1);
            }
            else{
              dialogueErreur("erreur de valeur","entrez un entier positif");
            }
          }
          if(n=="Assombrir (--)"){
            ImageRGB *resultat=new ImageRGB();
            ImageNG r,v,b;
            r=pR->getRouge()--;
            v=pR->getVert()--;
            b=pR->getBleu()--;
            resultat->setRGB(r,v,b);
            PhotoShop::resultat=resultat;
            setImageRGB("resultat",resultat);
            setResultatBoolean(-1);
          }
          if(n=="Filtre moyenneur"){
            m=dialogueDemandeInt("entrez la taille","nombre positif impaire");
            if((m<0 || m>255) || m%2==0)
            {
              dialogueErreur("valeur incorrecte","entrez des nombre impaire(0,255)");
            }
            else{
              ImageRGB *resultat=new ImageRGB();
              ImageNG r,v,b;
              r=pR->getRouge();
              v=pR->getVert();
              b=pR->getBleu();
              r=Traitements::FiltreMoyenneur(r,m);
              v=Traitements::FiltreMoyenneur(v,m);
              b=Traitements::FiltreMoyenneur(b,m);
              resultat->setRGB(r,v,b);
              PhotoShop::resultat=resultat;
              setImageRGB("resultat",resultat);
              setResultatBoolean(-1);
            }
          }
          if(n=="Filtre médian"){
            m=dialogueDemandeInt("entrez la taille","nombre positif impaire");
            if((m<0 || m>255) || m%2==0)
            {
              dialogueErreur("valeur incorrecte","entrez des nombre impaire(0,255)");
            }
            else{
              ImageRGB *resultat=new ImageRGB();
              ImageNG r,v,b;
              r=pR->getRouge();
              v=pR->getVert();
              b=pR->getBleu();
              r=Traitements::FiltreMedian(r,m);
              v=Traitements::FiltreMedian(v,m);
              b=Traitements::FiltreMedian(b,m);
              resultat->setRGB(r,v,b);
              PhotoShop::resultat=resultat;
              setImageRGB("resultat",resultat);
              setResultatBoolean(-1);
            }
          }
          if(n=="Erosion"){
            m=dialogueDemandeInt("entrez la taille","nombre positif impaire");
            if((m<0 || m>255) || m%2==0)
            {
              dialogueErreur("valeur incorrecte","entrez des nombre impaire(0,255)");
            }
            else{
              ImageRGB *resultat=new ImageRGB();
              ImageNG r,v,b;
              r=pR->getRouge();
              v=pR->getVert();
              b=pR->getBleu();
              r=Traitements::Erosion(r,m);
              v=Traitements::Erosion(v,m);
              b=Traitements::Erosion(b,m);
              resultat->setRGB(r,v,b);
              PhotoShop::resultat=resultat;
              setImageRGB("resultat",resultat);
              setResultatBoolean(-1);
            }
          }
          if(n=="Dilatation"){
            m=dialogueDemandeInt("entrez la taille","nombre positif impaire");
            if((m<0 || m>255) || m%2==0)
            {
              dialogueErreur("valeur incorrecte","entrez des nombre impaire(0,255)");
            }
            else{
              ImageRGB *resultat=new ImageRGB();
              ImageNG r,v,b;
              r=pR->getRouge();
              v=pR->getVert();
              b=pR->getBleu();
              r=Traitements::Dilatation(r,m);
              v=Traitements::Dilatation(v,m);
              b=Traitements::Dilatation(b,m);
              resultat->setRGB(r,v,b);
              PhotoShop::resultat=resultat;
              setImageRGB("resultat",resultat);
              setResultatBoolean(-1);
            }
          }
          if(n=="Négatif"){
            ImageRGB *resultat=new ImageRGB();
            ImageNG r,v,b;
            r=pR->getRouge();
            v=pR->getVert();
            b=pR->getBleu();
            r=Traitements::Negatif(r);
            v=Traitements::Negatif(v);
            b=Traitements::Negatif(b);
            resultat->setRGB(r,v,b);
            PhotoShop::resultat=resultat;
            setImageRGB("resultat",resultat);
            setResultatBoolean(-1);
          }
        
  }
  else{
  
    if(PhotoShop::operande1!= NULL)
    {
      ImageNG* pN = dynamic_cast<ImageNG*>(PhotoShop::operande1);
      if (pN != NULL){
        if(n=="Eclaircir (+ val)"){
          m=dialogueDemandeInt("Eclaircir","entrez un nombre positif");
          if(m>0){
            setResultatBoolean(-1);
            ImageNG *resultat=new ImageNG();
            (*resultat)=(*pN)+m;
            PhotoShop::resultat=resultat;
            setImageNG("resultat",resultat);
          }
          else{
            dialogueErreur("erreur de valeur","entrez un entier positif");
          }
        }
        if(n=="Eclaircir (++)"){
          setResultatBoolean(-1);
          ImageNG *resultat=new ImageNG();
          (*resultat)=(*pN)++;
          PhotoShop::resultat=resultat;
          setImageNG("resultat",pN);
        }
        if(n=="Assombrir (- val)"){
          m=dialogueDemandeInt("Eclaircir","entrez un nombre positif");
          if(m>0){
            ImageNG *resultat=new ImageNG();
            (*resultat)=(*pN)-m;
            PhotoShop::resultat=resultat;
            setImageNG("resultat",resultat);
            setResultatBoolean(-1);
          }
          else{
            dialogueErreur("erreur de valeur","entrez un entier positif");
          }
        }
        if(n=="Assombrir (--)"){
          ImageNG *resultat=new ImageNG();
          (*resultat)=(*pN)--;
          PhotoShop::resultat=resultat;
          setImageNG("resultat",resultat);
          setResultatBoolean(-1);
        }
        if(n=="Seuillage"){
          m=dialogueDemandeInt("Seuille","entrez un nombre positif");
          if(m<0 || m>255)
          {
            dialogueErreur("erreur","valeur incorrecte");
          }
          else{
            ImageB *resultat=new ImageB();
            (*resultat)=Traitements::Seuillage(*pN,m);
            PhotoShop::resultat=resultat;
            setImageB("resultat",resultat);
            setResultatBoolean(-1);
          }
        }
        if(n=="Filtre moyenneur"){
          m=dialogueDemandeInt("entrez la taille","nombre positif impaire");
          if((m<0 || m>255) || m%2==0)
          {
            dialogueErreur("valeur incorrecte","entrez des nombre impaire(0,255)");
          }
          else{
            ImageNG *resultat=new ImageNG();
            (*resultat)=Traitements::FiltreMoyenneur(*pN,m);
            PhotoShop::resultat=resultat;
            setImageNG("resultat",resultat);
            setResultatBoolean(-1);
          }
        }
        if(n=="Filtre médian"){
          m=dialogueDemandeInt("entrez la taille","nombre positif impaire");
          if((m<0 || m>255) || m%2==0)
          {
            dialogueErreur("valeur incorrecte","entrez des nombre impaire(0,255)");
          }
          else{
            ImageNG *resultat=new ImageNG();
            (*resultat)=Traitements::FiltreMedian(*pN,m);
            PhotoShop::resultat=resultat;
            setImageNG("resultat",resultat);
            setResultatBoolean(-1);
          }
        }
        if(n=="Erosion"){
          m=dialogueDemandeInt("entrez la taille","nombre positif impaire");
          if((m<0 || m>255) || m%2==0)
          {
            dialogueErreur("valeur incorrecte","entrez des nombre impaire(0,255)");
          }
          else{
            ImageNG *resultat=new ImageNG();
            (*resultat)=Traitements::Erosion(*pN,m);
            PhotoShop::resultat=resultat;
            setImageNG("resultat",resultat);
            setResultatBoolean(-1);
          }
        }
        if(n=="Dilatation"){
          m=dialogueDemandeInt("entrez la taille","nombre positif impaire");
          if((m<0 || m>255) || m%2==0)
          {
            dialogueErreur("valeur incorrecte","entrez des nombre impaire(0,255)");
          }
          else{
            ImageNG *resultat=new ImageNG();
            (*resultat)=Traitements::Dilatation(*pN,m);
            PhotoShop::resultat=resultat;
            setImageNG("resultat",resultat);
            setResultatBoolean(-1);
          }
        }
        if(n=="Négatif"){
          ImageNG *resultat=new ImageNG();
          (*resultat)=Traitements::Negatif(*pN);
          PhotoShop::resultat=resultat;
          setImageNG("resultat",resultat);
          setResultatBoolean(-1);
        }
        if(n=="Différence"){
          if(PhotoShop::operande2!= NULL){
            ImageNG* pNN = dynamic_cast<ImageNG*>(PhotoShop::operande2);
            if (pNN!= NULL){
              ImageNG *resultat=new ImageNG();
              try{
                (*resultat)=(*pN)-(*pNN);
                PhotoShop::resultat=resultat;
                setImageNG("resultat",resultat);
              }
              catch(XYException){
                setResultatBoolean(0);
              }
            }
            else{
              dialogueErreur("erreur","le type doit etre image ng");
            }
          }
          else{
            dialogueErreur("erreur","l'operation s'applique entre 2 image");
          }
        }
        if(n=="Comparaison (==)"){
          if(PhotoShop::operande2!= NULL){
            ImageNG* pNN = dynamic_cast<ImageNG*>(PhotoShop::operande2);
            if (pNN!= NULL){
              try{
                if((*pN)==(*pNN)){
                  setResultatBoolean(1);
                }
                else{
                  setResultatBoolean(0);
                }
              }
              catch(XYException){
                setResultatBoolean(0);
              }
              PhotoShop::resultat=NULL;
              setImageNG("resultat",NULL);
            }
            else{
              dialogueErreur("erreur","le type doit etre image ng");
            }
          }
          else{
            dialogueErreur("erreur","l'operation s'applique entre 2 image");
          }
        }
        if(n=="Comparaison (<)"){
          if(PhotoShop::operande2!= NULL){
            ImageNG* pNN = dynamic_cast<ImageNG*>(PhotoShop::operande2);
            if (pNN!= NULL){
              try{
                if((*pN)<(*pNN)){
                  setResultatBoolean(1);
                }
                else{
                  setResultatBoolean(0);
                }
              }
              catch(XYException){
                setResultatBoolean(0);
              }
              PhotoShop::resultat=NULL;
              setImageNG("resultat",NULL);
            }
            else{
              dialogueErreur("erreur","le type doit etre image ng");
            }
          }
          else{
            dialogueErreur("erreur","l'operation s'applique entre 2 image");
          }
        }
        if(n=="Comparaison (>)"){
          if(PhotoShop::operande2!= NULL){
            ImageNG* pNN = dynamic_cast<ImageNG*>(PhotoShop::operande2);
            if (pNN!= NULL){
              try{
                if((*pN)>(*pNN)){
                  setResultatBoolean(1);
                }
                else{
                  setResultatBoolean(0);
                }
              }
              catch(XYException){
                setResultatBoolean(0);
              }
              PhotoShop::resultat=NULL;
              setImageNG("resultat",NULL);
            }
            else{
              dialogueErreur("erreur","le type doit etre image ng");
            }
          }
          else{
            dialogueErreur("erreur","l'operation s'applique entre 2 image");
          }
        }
      }
      else{
        if(PhotoShop::operande2==NULL && PhotoShop::operande2==NULL){
          dialogueErreur("erreur","auccune image charger");
        }
        else{
          dialogueErreur("erreur","l'operation ne s'applique sur des image B");
        }
        
      }
    }
    else{
      if(PhotoShop::operande2!= NULL){
        ImageNG* pN = dynamic_cast<ImageNG*>(PhotoShop::operande2);
        if (pN != NULL){
          if(n=="Eclaircir (+ val)"){
            m=dialogueDemandeInt("Eclaircir","entrez un nombre positif");
            if(m>0){
              ImageNG *resultat=new ImageNG();
              (*resultat)=(*pN)+m;
              PhotoShop::resultat=resultat;
              setImageNG("resultat",resultat);
              setResultatBoolean(-1);
            }
            else{
              dialogueErreur("erreur de valeur","entrez un entier positif");
            }
          }
          if(n=="Eclaircir (++)"){
            ImageNG *resultat=new ImageNG();
            (*resultat)=(*pN)++;
            PhotoShop::resultat=resultat;
            setImageNG("resultat",pN);
            setResultatBoolean(-1);
          }
          if(n=="Assombrir (- val)"){
            m=dialogueDemandeInt("Eclaircir","entrez un nombre positif");
            if(m>0){
              ImageNG *resultat=new ImageNG();
              (*resultat)=(*pN)-m;
              PhotoShop::resultat=resultat;
              setImageNG("resultat",resultat);
              setResultatBoolean(-1);
            }
            else{
              dialogueErreur("erreur de valeur","entrez un entier positif");
            }
          }
          if(n=="Assombrir (--)"){
            ImageNG *resultat=new ImageNG();
            (*resultat)=(*pN)--;
            PhotoShop::resultat=resultat;
            setImageNG("resultat",resultat);
            setResultatBoolean(-1);
          }
          if(n=="Seuillage"){
            m=dialogueDemandeInt("Seuille","entrez un nombre positif");
            if(m<0 || m>255)
            {
              dialogueErreur("erreur","valeur incorrecte");
            }
            else{
              ImageB *resultat=new ImageB();
              (*resultat)=Traitements::Seuillage(*pN,m);
              PhotoShop::resultat=resultat;
              setImageB("resultat",resultat);
              setResultatBoolean(-1);
            }
          }
          if(n=="Filtre moyenneur"){
            m=dialogueDemandeInt("entrez la taille","nombre positif impaire");
            if((m<0 || m>255) || m%2==0)
            {
              dialogueErreur("valeur incorrecte","entrez des nombre impaire(0,255)");
            }
            else{
              ImageNG *resultat=new ImageNG();
              (*resultat)=Traitements::FiltreMoyenneur(*pN,m);
              PhotoShop::resultat=resultat;
              setImageNG("resultat",resultat);
              setResultatBoolean(-1);
            }
          }
          if(n=="Filtre médian"){
            m=dialogueDemandeInt("entrez la taille","nombre positif impaire");
            if((m<0 || m>255) || m%2==0)
            {
              dialogueErreur("valeur incorrecte","entrez des nombre impaire(0,255)");
            }
            else{
              ImageNG *resultat=new ImageNG();
              (*resultat)=Traitements::FiltreMedian(*pN,m);
              PhotoShop::resultat=resultat;
              setImageNG("resultat",resultat);
              setResultatBoolean(-1);
            }
          }
          if(n=="Erosion"){
            m=dialogueDemandeInt("entrez la taille","nombre positif impaire");
            if((m<0 || m>255) || m%2==0)
            {
              dialogueErreur("valeur incorrecte","entrez des nombre impaire(0,255)");
            }
            else{
              ImageNG *resultat=new ImageNG();
              (*resultat)=Traitements::Erosion(*pN,m);
              PhotoShop::resultat=resultat;
              setImageNG("resultat",resultat);
              setResultatBoolean(-1);
            }
          }
          if(n=="Dilatation"){
            m=dialogueDemandeInt("entrez la taille","nombre positif impaire");
            if((m<0 || m>255) || m%2==0)
            {
              dialogueErreur("valeur incorrecte","entrez des nombre impaire(0,255)");
            }
            else{
              ImageNG *resultat=new ImageNG();
              (*resultat)=Traitements::Dilatation(*pN,m);
              PhotoShop::resultat=resultat;
              setImageNG("resultat",resultat);
              setResultatBoolean(-1);
            }
          }
          if(n=="Négatif"){
            ImageNG *resultat=new ImageNG();
            (*resultat)=Traitements::Negatif(*pN);
            PhotoShop::resultat=resultat;
            setImageNG("resultat",resultat);
            setResultatBoolean(-1);
          }
        }
        else{

          dialogueErreur("erreur de type","l'operation s'applique a des image NB et rgb operande2");
        }
      }
      else{
        if(PhotoShop::operande2==NULL && PhotoShop::operande2==NULL){
          dialogueErreur("erreur","auccune image charger");
        }
        else{
          dialogueErreur("erreur","l'operation ne s'applique sur des image B");
        }
      }

    }
  }

}
void MainWindowPhotoShop::affichetable(){
  string type,dimension,m;
  videTableImages();
  PhotoShop::getInstance().i.reset();
  Image*im;
  ImageB* pB;
  ImageNG* pNG;
  ImageRGB* pRGB;
  while(!PhotoShop::getInstance().i.end()){
    im=PhotoShop::getInstance().i;
    pB = dynamic_cast<ImageB*>(im);
    if (pB != NULL)
    {
      type="B";
    }
    pNG = dynamic_cast<ImageNG*>(im);
    if (pNG != NULL) 
    {
      type="NG";
    }
    pRGB = dynamic_cast<ImageRGB*>(im);
    if (pRGB != NULL) 
    {
      type="RGB";
    }
    m=im->getNom();
    dimension=to_string(im->getDimension().getLargeur())+"X"+to_string(im->getDimension().getHauteur());
    ajouteTupleTableImages(im->getId(),type,dimension,m);
    PhotoShop::getInstance().i++;
  }
}