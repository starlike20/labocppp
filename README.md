# Labo C++ - Projet Etapes

## Description
Ce projet est une collection d'étapes visant à développer des compétences avancées en programmation C++. Chaque étape introduit de nouvelles fonctionnalités et concepts clés, tels que la manipulation d'images, les structures de données, et la gestion des exceptions.

## Fonctionnalités principales
- **Traitement d'images** : Manipulation d'images en niveaux de gris, binaire, et couleur (RGB).
- **Structures de données** : Implémentation et utilisation de listes ordonnées, tableaux dynamiques, et itérateurs.
- **Gestion des exceptions** : Gestion robuste des erreurs à l'aide d'exceptions personnalisées (XYException, RGBException, etc.).
- **Interface graphique (MyQT)** : Intégration avec des interfaces utilisateur simples pour interagir avec les images.

## Structure du projet

### Dossiers principaux
- **images/** : Contient les fichiers d'images d'exemple (BMP, PNG, etc.).
- **classes/** : Contient les fichiers source et d'en-tête pour les classes principales comme `Image`, `Dimension`, `Couleur`, etc.
- **étapes/** : Chaque étape (ég. étape1, étape2, ...) correspond à une progression dans le projet, avec des fichiers et tests associés.

### Fichiers clés
- **makefile** : Scripts pour compiler les différentes étapes.
- **TestX.cpp** : Fichiers de test pour valider les fonctionnalités des étapes.
- **main.cpp** : Point d'entrée principal pour certaines étapes.

## Prérequis
- **Système d'exploitation** : Linux ou Windows avec un environnement de compilation C++.
- **Compilateur** : g++ (version 9 ou supérieure).
- **Bibliothèques** : Qt pour les interfaces graphiques (si applicable).

## Instructions d'installation et d'exécution
1. **Clônez le dépôt** :
   ```bash
   git clone <url-du-dépôt>
   ```

2. **Naviguez vers l'étape souhaitée** :
   ```bash
   cd étapeX
   ```

3. **Compilez le projet** :
   ```bash
   make
   ```

4. **Exécutez le programme** :
   ```bash
   ./TestX
   ```

## Fonctionnalités par étape
### Étape 1 : Introduction aux Dimensions et ImagesNG
- Mise en place de classes de base pour manipuler des dimensions et des images en niveaux de gris.

### Étape 2 : Ajout de Couleurs et Gestion Avancée
- Intégration des couleurs avec des fonctionnalités avancées pour la gestion d'images.

### Étape 3-5 : Itérateurs et Structures de Données Dynamiques
- Implémentation de listes dynamiques et d'itérateurs.

### Étapes Avancées : Exception Handling, Images RGB et Interfaces Graphiques
- Gestion d'images en couleur (RGB) avec des exceptions robustes.
- Intégration Qt pour des interfaces graphiques simples.

## Licence
Ce projet est distribué sous la licence MIT.

## Remerciements
Merci aux enseignants et mentors pour leur accompagnement et leurs conseils tout au long de ce projet.

