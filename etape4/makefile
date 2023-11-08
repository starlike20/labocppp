.SILENT:

COMP=g++ -D DEBUG
CLASSES=classes/

Test4:	Test4.cpp objets/ImageNG.o objets/Dimension.o objets/MyQT.o
	echo creation de Test4
	$(COMP) -o Test4 Test4.cpp objets/MyQT.o objets/ImageNG.o objets/Dimension.o -lSDL -lpthread -Wl,-O1 -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so
	#ne j'ai eu une erreur ici -o Test1 Test1

objets/ImageNG.o:	$(CLASSES)ImageNG.cpp $(CLASSES)ImageNG.h objets/MyQT.o
	echo creation de ImageNG.o
	$(COMP) classes/ImageNG.cpp -c -o objets/ImageNG.o 

objets/Dimension.o:	$(CLASSES)Dimension.cpp $(CLASSES)Dimension.h
	echo creation de Dimension.o
	$(COMP) classes/Dimension.cpp -c -o objets/Dimension.o
objets/MyQT.o:	$(CLASSES)MyQT.cpp $(CLASSES)MyQT.h
	echo creation de MyQT.o
	$(COMP) classes/MyQT.cpp -c -o objets/MyQT.o -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++

clean:
	rm -f objets/*.o core

clobber:	clean
	rm -f Test4

