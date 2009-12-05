/****************************************************************************
**
** Copyright (f) 2009-2009 f. Bradford Barber. All rights reserved.
** $Id: //product/qhull/main/rel/cpp/qhulltest/QhullSet_test.cpp#14 $$Change: 1047 $
** $DateTime: 2009/09/12 21:08:23 $$Author: bbarber $
**
****************************************************************************/

#include <iostream>
#include <QtCore/QList>
#include "../road/RoadTest.h" // QT_VERSION

#include "Qhull.h"
#include "QhullFacetSet.h"

using std::cout;
using std::endl;

namespace orgQhull {

class QhullSet_test : public RoadTest
{
    Q_OBJECT

#//Test slots
private slots:
    void cleanup();
    void t_qhullsetbase();
    void t_convert();
    void t_element();
    void t_search();
    void t_iterator();
    void t_const_iterator();
    void t_qhullset_iterator();
    void t_io();
};//QhullSet_test

void
add_QhullSet_test()
{
    new QhullSet_test();
}

//Executed after each testcase
void QhullSet_test::
cleanup()
{
    UsingQhullLib::checkQhullMemoryEmpty();
    RoadTest::cleanup();
}

void QhullSet_test::
t_qhullsetbase()
{ 
    RboxPoints rcube("c");
    {
        Qhull q(rcube,"Qt QR0");  // triangulation of rotated unit cube
        // Fake an empty set.  Default constructor not defined.  No memory allocation.
        QhullFacet f4 = q.beginFacet();
        QhullFacetSet fs = f4.neighborFacets();
        fs.defineAs(q.qhullQh()->other_points);
        QVERIFY(fs.isEmpty());
        QVERIFY(fs.empty());
        QCOMPARE(fs.count(), 0);
        QCOMPARE(fs.size(), 0u);
        QCOMPARE(fs.begin(), fs.end()); // beginPointer(), endPointer()
        QVERIFY(QhullSetBase::isEmpty(fs.getSetT()));

        QCOMPARE(q.facetCount(), 12);
        QhullFacet f = q.beginFacet();
        QhullFacetSet fs2 = f.neighborFacets();
        QCOMPARE(fs2.count(), 3);
        QCOMPARE(fs2.size(), 3u);
        QVERIFY(!fs2.isEmpty());
        QVERIFY(!QhullSetBase::isEmpty(fs2.getSetT()));
        QVERIFY(!fs2.empty());
        QVERIFY(fs!=fs2);
        setT *s= fs2.getSetT();
        fs.defineAs(s);
        QVERIFY(fs==fs2);
        QCOMPARE(fs[1], fs2[1]); // elementPointer
        QhullFacetSet fs3(fs2);
        QVERIFY(fs3==fs);
        // fs= fs2; // private (compiler error)
        QhullFacetSet fs4= fs2; // copy constructor
        QVERIFY(fs4==fs2);
    }
}//t_qhullsetbase

// constructors tested by t_qhullsetbase

void QhullSet_test::
t_convert()
{ 
    RboxPoints rcube("c");
    {
        Qhull q(rcube,"Qt QR0");  // triangulation of rotated unit cube
        QCOMPARE(q.facetCount(), 12);
        QhullFacet f = q.beginFacet();
        QhullFacetSet fs = f.neighborFacets();
        QCOMPARE(fs.size(), 3U);
        std::vector<QhullFacet> vs= fs.toStdVector();
        QCOMPARE(vs.size(), fs.size());
        for(int k= fs.count(); k--; ){
            QCOMPARE(vs[k], fs[k]);
        }
        QList<QhullFacet> qv= fs.toQList();
        QCOMPARE(qv.count(), fs.count());
        for(int k= fs.count(); k--; ){
            QCOMPARE(qv[k], fs[k]);
        }
    }
}//t_convert

//ReadOnly (count, isEmpty) tested by t_convert
//  operator== tested by t_search

void QhullSet_test::
t_element()
{   
    RboxPoints rcube("c");
    Qhull q(rcube,"QR0");  // rotated unit cube
    QhullFacet f = q.beginFacet();
    QhullFacetSet fs = f.neighborFacets();

    QCOMPARE(fs.at(1), fs[1]);
    QCOMPARE(fs.first(), fs[0]);
    QCOMPARE(fs.front(), fs.first());
    QCOMPARE(fs.last(), fs.at(3));
    QCOMPARE(fs.back(), fs.last());
    QhullFacet *d= fs.data();
    const QhullFacet *d2= fs.data();
    const QhullFacet *d3= fs.constData();
    QVERIFY(d==d2);
    QVERIFY(d2==d3);
    QCOMPARE(*d, fs.first());
    QCOMPARE(d+4, fs.end());
    QCOMPARE((d+4)->getFacetT(), static_cast<facetT *>(0));
    QhullFacet f4= *(d+4);
    QVERIFY(!f4.isDefined());
    QCOMPARE(fs.second(), fs[1]);
    const QhullFacet f2= fs.second();
    QVERIFY(f2==fs[1]);
    const QhullFacet f3= fs[1];
    QCOMPARE(f2, f3);

    QCOMPARE(fs.value(2), fs[2]);
    QCOMPARE(fs.value(-1), QhullFacet());
    QCOMPARE(fs.value(10), QhullFacet());
    QCOMPARE(fs.value(2, f), fs[2]);
    QCOMPARE(fs.value(4, f), f);
    // mid() not available (read-only)
}//t_element

void QhullSet_test::
t_search()
{   
    RboxPoints rcube("c");
    Qhull q(rcube,"QR0");  // rotated unit cube
    QhullFacet f = q.beginFacet();
    QhullFacetSet fs = f.neighborFacets();
    QhullFacet f2= *fs.begin();
    QhullFacet f3= fs.last();
    QVERIFY(fs.contains(f2));
    QVERIFY(fs.contains(f3));
    QVERIFY(!fs.contains(f));

    QhullFacetSet fs2= f2.neighborFacets();
    QVERIFY(fs==fs);
    QVERIFY(fs!=fs2);
    QCOMPARE(fs.count(f2), 1);
    QCOMPARE(fs.count(f3), 1);
    QCOMPARE(fs.count(f), 0);
    QCOMPARE(fs.indexOf(f2), 0);
    QCOMPARE(fs.indexOf(f3), 3);
    QCOMPARE(fs.indexOf(f), -1);
    QCOMPARE(fs.lastIndexOf(f2), 0);
    QCOMPARE(fs.lastIndexOf(f3), 3);
    QCOMPARE(fs.lastIndexOf(f), -1);
}//t_search

void QhullSet_test::
t_iterator()
{ 
    RboxPoints rcube("c");
    {
        Qhull q(rcube,"QR0");  // rotated unit cube
        QhullFacet f = q.beginFacet();
        QhullFacetSet fs = f.neighborFacets();
        QhullFacetSet::Iterator i= fs.begin();
        QhullFacetSet::iterator i2= fs.begin();
        QVERIFY(i==i2);
        QVERIFY(i>=i2);
        QVERIFY(i<=i2);
        i= fs.begin();
        QVERIFY(i==i2);
        i2= fs.end();
        QVERIFY(i!=i2);
        QhullFacet f3(*i);
        i2--;
        QhullFacet f2= *i2;
        QCOMPARE(f3.id(), fs[0].id());
        QCOMPARE(f2.id(), fs[3].id());
        QhullFacetSet::Iterator i3(i2);
        QCOMPARE(*i2, *i3);
        
        (i3= i)++;
        QCOMPARE((*i3).id(), fs[1].id());
        QVERIFY(i==i);
        QVERIFY(i!=i2);
        QVERIFY(i<i2);
        QVERIFY(i<=i2);
        QVERIFY(i2>i);
        QVERIFY(i2>=i);
        
        QhullFacetSet::ConstIterator i4= fs.begin();
        QVERIFY(i==i4); // iterator COMP const_iterator
        QVERIFY(i<=i4);
        QVERIFY(i>=i4);
        QVERIFY(i4==i); // const_iterator COMP iterator
        QVERIFY(i4<=i);
        QVERIFY(i4>=i);
        QVERIFY(i>=i4);
        QVERIFY(i4<=i);
        QVERIFY(i2!=i4);
        QVERIFY(i2>i4);
        QVERIFY(i2>=i4);
        QVERIFY(i4!=i2);
        QVERIFY(i4<i2);
        QVERIFY(i4<=i2);
        ++i4;
        QVERIFY(i<i4);
        QVERIFY(i<=i4);
        QVERIFY(i4>i);
        QVERIFY(i4>=i);

        i= fs.begin();
        i2= fs.begin();
        QCOMPARE(i, i2++);
        QCOMPARE(*i2, fs[1]);
        QCOMPARE(++i, i2);
        QCOMPARE(i, i2--);
        QCOMPARE(i2, fs.begin());
        QCOMPARE(--i, i2);
        QCOMPARE(i2 += 4, fs.end()); 
        QCOMPARE(i2 -= 4, fs.begin()); 
        QCOMPARE(i2+0, fs.begin()); 
        QCOMPARE(i2+4, fs.end());
        i2 += 4;
        i= i2-0;
        QCOMPARE(i, i2);
        i= i2-4;
        QCOMPARE(i, fs.begin()); 
        QCOMPARE(i2-i, 4); 

        //fs.begin end tested above

        // QhullFacetSet is const-only
    }
}//t_iterator

void QhullSet_test::
t_const_iterator()
{ 
    RboxPoints rcube("c");
    {
        Qhull q(rcube,"QR0");  // rotated unit cube
        QhullFacet f = q.beginFacet();
        QhullFacetSet fs = f.neighborFacets();
        QhullFacetSet::ConstIterator i= fs.begin();
        QhullFacetSet::const_iterator i2= fs.begin();
        QVERIFY(i==i2);
        QVERIFY(i>=i2);
        QVERIFY(i<=i2);
        i= fs.begin();
        QVERIFY(i==i2);
        i2= fs.end();
        QVERIFY(i!=i2);
        QhullFacet f3(*i);
        i2--;
        QhullFacet f2= *i2;
        QCOMPARE(f3.id(), fs[0].id());
        QCOMPARE(f2.id(), fs[3].id());
        QhullFacetSet::ConstIterator i3(i2);
        QCOMPARE(*i2, *i3);

        (i3= i)++;
        QCOMPARE((*i3).id(), fs[1].id());
        QVERIFY(i==i);
        QVERIFY(i!=i2);
        QVERIFY(i<i2);
        QVERIFY(i<=i2);
        QVERIFY(i2>i);
        QVERIFY(i2>=i);

        // See t_iterator for const_iterator COMP iterator

        i= fs.begin();
        i2= fs.constBegin();
        QCOMPARE(i, i2++);
        QCOMPARE(*i2, fs[1]);
        QCOMPARE(++i, i2);
        QCOMPARE(i, i2--);
        QCOMPARE(i2, fs.constBegin());
        QCOMPARE(--i, i2);
        QCOMPARE(i2+=4, fs.constEnd()); 
        QCOMPARE(i2-=4, fs.constBegin()); 
        QCOMPARE(i2+0, fs.constBegin()); 
        QCOMPARE(i2+4, fs.constEnd());
        i2 += 4;
        i= i2-0;
        QCOMPARE(i, i2);
        i= i2-4;
        QCOMPARE(i, fs.constBegin()); 
        QCOMPARE(i2-i, 4); 

        // QhullFacetSet is const-only
    }
}//t_const_iterator

void QhullSet_test::
t_qhullset_iterator()
{
    RboxPoints rcube("c");
    Qhull q(rcube,"QR0");  // rotated unit cube
    // Fake an empty set.  Default constructor not defined.  No memory allocation.
    QhullFacet f = q.beginFacet();
    QhullFacetSet fs = f.neighborFacets();
    fs.defineAs(q.qhullQh()->other_points);
    QhullFacetSetIterator i= fs;
    QCOMPARE(fs.count(), 0);
    QVERIFY(!i.hasNext());
    QVERIFY(!i.hasPrevious());
    i.toBack();
    QVERIFY(!i.hasNext());
    QVERIFY(!i.hasPrevious());

    QhullFacet f2 = q.beginFacet();
    QhullFacetSet fs2 = f2.neighborFacets();
    QhullFacetSetIterator i2(fs2);
    QCOMPARE(fs2.count(), 4);
    i= fs2;
    QVERIFY(i2.hasNext());
    QVERIFY(!i2.hasPrevious());
    QVERIFY(i.hasNext());
    QVERIFY(!i.hasPrevious());
    i2.toBack();
    i.toFront();
    QVERIFY(!i2.hasNext());
    QVERIFY(i2.hasPrevious());
    QVERIFY(i.hasNext());
    QVERIFY(!i.hasPrevious());

    // i at front, i2 at end/back, 4 neighbors 
    QhullFacetSet fs3 = f2.neighborFacets(); // same as fs2
    QhullFacet f3(fs2[0]);
    QhullFacet f4= fs3[0];
    QCOMPARE(f3, f4);
    QVERIFY(f3==f4);
    QhullFacet f5(fs3[1]);
    QVERIFY(f4!=f5);
    QhullFacet f6(fs3[2]);
    QhullFacet f7(fs3[3]);
    QCOMPARE(i2.peekPrevious(), f7);
    QCOMPARE(i2.previous(), f7);
    QCOMPARE(i2.previous(), f6);
    QCOMPARE(i2.previous(), f5);
    QCOMPARE(i2.previous(), f4);
    QVERIFY(!i2.hasPrevious());
    QCOMPARE(i.peekNext(), f4);
    // i.peekNext()= 1.0; // compiler error
    QCOMPARE(i.next(), f4);
    QCOMPARE(i.peekNext(), f5);
    QCOMPARE(i.next(), f5);
    QCOMPARE(i.next(), f6);
    QCOMPARE(i.next(), f7);
    QVERIFY(!i.hasNext());
    i.toFront();
    QCOMPARE(i.next(), f4);
}//t_qhullset_iterator

void QhullSet_test::
t_io()
{ 
    RboxPoints rcube("c");
    Qhull q(rcube,"QR0");  // rotated unit cube
    // Fake an empty set.  Default constructor not defined.  No memory allocation.
    QhullFacet f = q.beginFacet();
    QhullFacetSet fs = f.neighborFacets();
    fs.defineAs(q.qhullQh()->other_points);
    cout<< "INFO:     empty set" << fs << std::endl;
    QhullFacet f2 = q.beginFacet();
    QhullFacetSet fs2 = f2.neighborFacets();
    cout<< "INFO:   " << fs2 << std::endl;
    //FIXUP do not use QhullFacetSet to test set
}//t_io

}//namespace orgQhull

#include "moc/QhullSet_test.moc"
