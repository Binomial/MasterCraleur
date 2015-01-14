# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/GNU-Linux-x86
TARGET = ScrabbleQT
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui widgets
SOURCES += main.cpp src/controller/anagramint/Dictionnary.cpp src/controller/anagramint/FindWord.cpp src/controller/anagramstring/Permut.cpp src/controller/dawg/Node.cpp src/controller/dawg/Trie.cpp src/model/Bundle.cpp src/model/GameBoard.cpp src/model/Player.cpp src/view/Console.cpp src/view/mafenetre.cpp
HEADERS += header/controller/anagramint/Dictionnary.h header/controller/anagramint/FindWord.h header/controller/anagramstring/Permut.h header/controller/dawg/Node.h header/controller/dawg/Trie.h header/model/Bundle.h header/model/GameBoard.h header/model/Player.h header/view/Console.h header/view/mafenetre.h
FORMS +=
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += 
equals(QT_MAJOR_VERSION, 4) {
QMAKE_CXXFLAGS += -std=c++11
}
equals(QT_MAJOR_VERSION, 5) {
CONFIG += c++11
}
