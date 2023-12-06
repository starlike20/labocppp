.SILENT:

COMP=g++ #-D DEBUG -Wall
CLASSES=classes/

Test10b: Test10b.cpp objets/PhotoShop.o objets/Traitements.o objets/ArrayList.o objets/Iterateur.o objets/Exception.o objets/XYException.o objets/RGBException.o objets/Image.o objets/ImageRGB.o objets/ImageNG.o objets/ImageB.o objets/Dimension.o objets/MyQT.o objets/Couleur.o objets/SortedArrayList.o
	echo creation de Test10b
	$(COMP) -o Test10b Test10b.cpp -I classes/ objets/PhotoShop.o objets/Traitements.o objets/ArrayList.o objets/Iterateur.o objets/Exception.o objets/XYException.o objets/RGBException.o objets/Couleur.o objets/Image.o objets/MyQT.o objets/ImageNG.o objets/Dimension.o objets/ImageRGB.o objets/ImageB.o objets/SortedArrayList.o -lSDL -lpthread -Wl,-O1 -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so

Test10a: Test10a.cpp objets/PhotoShop.o objets/Traitements.o objets/ArrayList.o objets/Iterateur.o objets/Exception.o objets/XYException.o objets/RGBException.o objets/Image.o objets/ImageRGB.o objets/ImageNG.o objets/ImageB.o objets/Dimension.o objets/MyQT.o objets/Couleur.o objets/SortedArrayList.o
	echo creation de Test10a
	$(COMP) -o Test10a Test10a.cpp -I classes/ objets/PhotoShop.o objets/Traitements.o objets/ArrayList.o objets/Iterateur.o objets/Exception.o objets/XYException.o objets/RGBException.o objets/Couleur.o objets/Image.o objets/MyQT.o objets/ImageNG.o objets/Dimension.o objets/ImageRGB.o objets/ImageB.o objets/SortedArrayList.o -lSDL -lpthread -Wl,-O1 -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so

objets/Dimension.o: $(CLASSES)Dimension.cpp $(CLASSES)Dimension.h
	echo creation de Dimension.o
	$(COMP) classes/Dimension.cpp -c -o objets/Dimension.o

objets/Couleur.o: $(CLASSES)Couleur.cpp $(CLASSES)Couleur.h
	echo creation de couleur.objets
	$(COMP) classes/Couleur.cpp -c -o objets/Couleur.o

objets/MyQT.o: $(CLASSES)MyQT.cpp $(CLASSES)MyQT.h
	echo creation de MyQT.o
	$(COMP) classes/MyQT.cpp -c -o objets/MyQT.o -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++

objets/Image.o: $(CLASSES)Image.cpp $(CLASSES)Image.h objets/MyQT.o
	echo creation de Image.o
	$(COMP) classes/Image.cpp -c -o objets/Image.o

objets/ImageNG.o: $(CLASSES)ImageNG.cpp $(CLASSES)ImageNG.h objets/MyQT.o objets/Image.o
	echo creation de ImageNG.o
	$(COMP) classes/ImageNG.cpp -c -o objets/ImageNG.o

objets/ImageRGB.o: $(CLASSES)ImageRGB.cpp $(CLASSES)ImageRGB.h objets/MyQT.o objets/Image.o
	echo creation de ImageRGB.o
	$(COMP) classes/ImageRGB.cpp -c -o objets/ImageRGB.o

objets/ImageB.o: $(CLASSES)ImageB.cpp $(CLASSES)ImageB.h objets/MyQT.o objets/Image.o
	echo creation de ImageB.o
	$(COMP) classes/ImageB.cpp -c -o objets/ImageB.o

objets/Exception.o: $(CLASSES)Exception.cpp $(CLASSES)Exception.h objets/MyQT.o
	echo creation Exception.o
	$(COMP) classes/Exception.cpp -c -o objets/Exception.o

objets/XYException.o: $(CLASSES)XYException.cpp $(CLASSES)XYException.h objets/MyQT.o objets/Exception.o
	echo creation XYException.o
	$(COMP) classes/XYException.cpp -c -o objets/XYException.o

objets/RGBException.o: $(CLASSES)RGBException.cpp $(CLASSES)RGBException.h objets/MyQT.o objets/Exception.o
	echo creation RGBException.o
	$(COMP) classes/RGBException.cpp -c -o objets/RGBException.o

objets/Iterateur.o: $(CLASSES)Iterateur.cpp $(CLASSES)Iterateur.h
	echo creation Iterateur.o
	$(COMP) classes/Iterateur.cpp -c -o objets/Iterateur.o

objets/ArrayList.o: $(CLASSES)ArrayList.cpp $(CLASSES)ArrayList.h
	echo creation ArrayList.o
	$(COMP) classes/ArrayList.cpp -c -o objets/ArrayList.o

objets/Traitements.o: $(CLASSES)Traitements.cpp $(CLASSES)Traitements.h objets/SortedArrayList.o
	echo creation Traitements.o
	$(COMP) classes/Traitements.cpp objets/SortedArrayList.o -c -o objets/Traitements.o

objets/SortedArrayList.o: $(CLASSES)SortedArrayList.cpp $(CLASSES)SortedArrayList.h objets/ArrayList.o
	echo creation SortedArrayList.o
	$(COMP) classes/SortedArrayList.cpp -c -o objets/SortedArrayList.o

objets/PhotoShop.o:	$(CLASSES)PhotoShop.cpp $(CLASSES)PhotoShop.h 
	echo creation PhotoShop.o
	$(COMP) classes/PhotoShop.cpp -c -o objets/PhotoShop.o


clean:
	rm -f objets/*.o core

clobber: clean
	rm -f Test9
