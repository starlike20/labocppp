.SILENT:

COMP=g++ -D DEBUG -Wall
CLASSES=classes/

Test5:	Test5.cpp objets/Image.o objets/ImageRGB.o objets/ImageNG.o objets/ImageB.o objets/Dimension.o objets/MyQT.o objets/Couleur.o
	echo creation de Test5
	$(COMP) -o Test5 Test5.cpp -I classes/ objets/Couleur.o objets/Image.o objets/MyQT.o objets/ImageNG.o objets/Dimension.o objets/ImageRGB.o objets/ImageB.o -lSDL -lpthread -Wl,-O1 -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so
	#ne j'ai eu une erreur ici -o Test1 Test1

objets/Dimension.o:	$(CLASSES)Dimension.cpp $(CLASSES)Dimension.h
	echo creation de Dimension.o
	$(COMP) classes/Dimension.cpp -c -o objets/Dimension.o

objets/Couleur.o:	$(CLASSES)Couleur.cpp $(CLASSES)Couleur.h
	echo creation de couleur.objets
	$(COMP) classes/Couleur.cpp -c -o objets/Couleur.o

objets/MyQT.o:	$(CLASSES)MyQT.cpp $(CLASSES)MyQT.h 
	echo creation de MyQT.o
	$(COMP) classes/MyQT.cpp -c -o objets/MyQT.o -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++

objets/Image.o:	$(CLASSES)Image.cpp $(CLASSES)Image.h objets/MyQT.o
	echo creation de Image.o
	$(COMP) classes/Image.cpp -c -o objets/Image.o

objets/ImageNG.o:	$(CLASSES)ImageNG.cpp $(CLASSES)ImageNG.h objets/MyQT.o objets/Image.o
	echo creation de ImageNG.o
	$(COMP) classes/ImageNG.cpp -c -o objets/ImageNG.o 

objets/ImageRGB.o:	$(CLASSES)ImageRGB.cpp $(CLASSES)ImageRGB.h objets/MyQT.o objets/Image.o
	echo creation de ImageRGB.o
	$(COMP) classes/ImageRGB.cpp -c -o objets/ImageRGB.o 

objets/ImageB.o:	$(CLASSES)ImageB.cpp $(CLASSES)ImageB.h objets/MyQT.o objets/Image.o
	echo creation de ImageB.o
	$(COMP) classes/ImageB.cpp -c -o objets/ImageB.o 

clean:
	rm -f objets/*.o core

clobber:	clean
	rm -f Test5

