# -------------------------------------------------
# qhull-qt.pro -- Qt project file
# -------------------------------------------------
QT -= gui
TARGET = qhull-qt
CONFIG += console \
    qtestlib \
    debug
CONFIG -= app_bundle
TEMPLATE = app
LIBS = ../../libqhull.a
DESTDIR = ../..
OBJECTS_DIR = ../../tmp/obj
MOC_DIR = ../../tmp/moc
RCC_DIR = ../../tmp/rcc
INCLUDEPATH = ../../cpp;../../cpp/road;../../tmp
VPATH = ../..
SOURCES += cpp/Coordinates.cpp
SOURCES += cpp/QhullVertexSet.cpp
SOURCES += cpp/QhullHyperplane.cpp
SOURCES += cpp/PointCoordinates.cpp
SOURCES += cpp/Qhull.cpp
SOURCES += cpp/QhullError.cpp
SOURCES += cpp/QhullEvent.cpp
SOURCES += cpp/QhullFacet.cpp
SOURCES += cpp/QhullFacetList.cpp
SOURCES += cpp/QhullFacetSet.cpp
SOURCES += cpp/QhullPoint.cpp
SOURCES += cpp/QhullPoints.cpp
SOURCES += cpp/QhullPointSet.cpp
SOURCES += cpp/QhullQh.cpp
SOURCES += cpp/QhullRidge.cpp
SOURCES += cpp/QhullSet.cpp
SOURCES += cpp/QhullStat.cpp
SOURCES += cpp/QhullVertex.cpp
SOURCES += cpp/RboxPoints.cpp
SOURCES += cpp/UsingQhullLib.cpp
SOURCES += cpp/road/RoadError.cpp
SOURCES += cpp/road/RoadLogEvent.cpp
SOURCES += cpp/road/RoadTest.cpp
SOURCES += cpp/qhulltest/Coordinates_test.cpp
SOURCES += cpp/qhulltest/PointCoordinates_test.cpp
SOURCES += cpp/qhulltest/Qhull_test.cpp
SOURCES += cpp/qhulltest/QhullFacet_test.cpp
SOURCES += cpp/qhulltest/QhullFacetList_test.cpp
SOURCES += cpp/qhulltest/QhullFacetSet_test.cpp
SOURCES += cpp/qhulltest/QhullHyperplane_test.cpp
SOURCES += cpp/qhulltest/QhullLinkedList_test.cpp
SOURCES += cpp/qhulltest/QhullPoint_test.cpp
SOURCES += cpp/qhulltest/QhullPoints_test.cpp
SOURCES += cpp/qhulltest/QhullPointSet_test.cpp
SOURCES += cpp/qhulltest/QhullRidge_test.cpp
SOURCES += cpp/qhulltest/QhullSet_test.cpp
SOURCES += cpp/qhulltest/qhulltest.cpp
SOURCES += cpp/qhulltest/QhullVertex_test.cpp
SOURCES += cpp/qhulltest/UsingQhullLib_test.cpp
SOURCES += cpp/qhulltest/RboxPoints_test.cpp
HEADERS += cpp/Coordinates.h
HEADERS += cpp/QhullHyperplane.h
HEADERS += cpp/functionObjects.h
HEADERS += cpp/PointCoordinates.h
HEADERS += cpp/Qhull.h
HEADERS += cpp/QhullError.h
HEADERS += cpp/QhullEvent.h
HEADERS += cpp/QhullFacet.h
HEADERS += cpp/QhullFacetList.h
HEADERS += cpp/QhullFacetSet.h
HEADERS += cpp/QhullIterator.h
HEADERS += cpp/QhullLinkedList.h
HEADERS += cpp/QhullPoint.h
HEADERS += cpp/QhullPoints.h
HEADERS += cpp/QhullPointSet.h
HEADERS += cpp/QhullQh.h
HEADERS += cpp/QhullRidge.h
HEADERS += cpp/QhullSet.h
HEADERS += cpp/QhullSets.h
HEADERS += cpp/QhullStat.h
HEADERS += cpp/QhullVertex.h
HEADERS += cpp/RboxPoints.h
HEADERS += cpp/UsingQhullLib.h
HEADERS += cpp/road/RoadError.h
HEADERS += cpp/road/RoadLogEvent.h
HEADERS += cpp/road/RoadTest.h
QMAKE_MOC_SRC += cpp/qhulltest/UsingQhullLib_test.cpp
