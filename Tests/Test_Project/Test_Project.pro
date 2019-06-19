CONFIG+=console c++14

INCLUDEPATH+="googletest/include"
INCLUDEPATH+="googlemock/include"
INCLUDEPATH+="googletest/"
INCLUDEPATH+="googlemock/"
INCLUDEPATH+="../../"
SOURCES += \
    main.cpp \
    googlemock/src/gmock-all.cc \
    googletest/src/gtest-all.cc

HEADERS += \
    ../../list.h \
    ../../osrbtree.h \
    ../../splaytree.h \
    ../../stllist.h \
    ../../stlmap.h \
    ../../stlvector.h \
    ../../structurerepresentor.h \
    ../../randomgenerator.h
