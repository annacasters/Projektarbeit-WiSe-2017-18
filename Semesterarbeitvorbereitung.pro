TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    sneaker.cpp

DISTFILES += \
    daten.txt \
    sneakersammlung.xml

data.path = $$OUT_PWD/

data.files += $$PWD/*.txt

data.files += $$PWD/*.xml


INSTALLS += data

HEADERS += \
    sneaker.h

