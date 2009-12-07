/****************************************************************************
**
** Copyright (C) 2009-2009 C. Bradford Barber. All rights reserved.
** $Id: //product/qhull/main/rel/cpp/PointCoordinates.h#8 $$Change: 1094 $
** $DateTime: 2009/11/24 20:04:16 $$Author: bbarber $
**
****************************************************************************/

#ifndef QHPOINTCOORDINATES_H
#define QHPOINTCOORDINATES_H

#include "QhullPoints.h"
#include "Coordinates.h"

#include <ostream>
#include <vector>

extern "C" {
    #include "../src/qhull_a.h"
};

namespace orgQhull {

#//Types
    //! Zero or more points with Coordinates, count, and dimension
    class PointCoordinates;

class PointCoordinates : public QhullPoints {

private:
#//Field
    Coordinates         point_coordinates;	//! array of point coordinates
                                                //! may have extraCoordinates() 
    std::string         point_comment;          //! Comment describing PointCoordinates

public:
#//Construct
                        PointCoordinates();
    explicit            PointCoordinates(int dimension);
    explicit            PointCoordinates(const std::string &comment);
                        PointCoordinates(int dimension, const std::string &comment);
                        PointCoordinates(int dimension, const std::string &comment, int coordinateCount, const coordT *c); // may be invalid
                        //! Use append() and appendPoints() for Coordinates and vector<coordT>
                        PointCoordinates(const PointCoordinates &other);
    PointCoordinates   &operator=(const PointCoordinates &other);
    ~PointCoordinates();

#//Convert
    //! QhullPoints coordinates, constData, data, count, size
#ifndef QHULL_NO_STL
    void	        append(const std::vector<coordT> &coordinates) { if(!coordinates.empty()){ append((int)coordinates.size(), &coordinates[0]); } } 
    std::vector<coordT> toStdVector() const { return point_coordinates.toStdVector(); }
#endif //QHULL_NO_STL
#ifdef QHULL_USES_QT
    void	        append(const QList<coordT> &coordinates) { if(!coordinates.isEmpty()){ append(coordinates.count(), &coordinates[0]); } } 
    QList<coordT>       toQList() const { return point_coordinates.toQList(); }
#endif //QHULL_USES_QT


#//GetSet
    //! See QhullPoints for coordinates, coordinateCount, dimension, empty, isEmpty, ==, !=
    void                checkValid() const;
    std::string         comment() const { return point_comment; }
    void                makeValid() { defineAs(point_coordinates.count(), point_coordinates.data()); }
    const Coordinates  &getCoordinates() const { return point_coordinates; }
    void                setComment(const std::string &s) { point_comment= s; }
    void                setDimension(int i);

private:
    void                defineAs(int coordinateCount, coordT *c) { QhullPoints::defineAs(coordinateCount, c); }
    //! defineAs() otherwise disabled
public:

#//ElementAccess
    //! See QhullPoints for at, back, first, front, last, mid, [], value

#//Foreach
    //! See QhullPoints for begin, constBegin, end
    Coordinates::ConstIterator	beginCoordinates() const { return point_coordinates.begin(); }
    Coordinates::Iterator       beginCoordinates() { return point_coordinates.begin(); }
    Coordinates::ConstIterator  beginCoordinates(int pointIndex) const;
    Coordinates::Iterator	beginCoordinates(int pointIndex);
    Coordinates::ConstIterator  endCoordinates() const { return point_coordinates.end(); }
    Coordinates::Iterator       endCoordinates() { return point_coordinates.end(); }

#//Search
    //! See QhullPoints for contains, count, indexOf, lastIndexOf

#//Modify
    void                append(int count, const coordT *c);  //! Dimension previously defined
    void                append(const coordT &c) { append(1, &c); } //! Dimension previously defined
    void                append(const QhullPoint &p);
    //! See convert for std::vector and QList
    void	        append(const Coordinates &c) { append(c.count(), c.data()); } 
    void                append(const PointCoordinates &other);
    void                appendComment(const std::string &s);
    void                appendPoints(std::istream &in);
    PointCoordinates    operator+(const PointCoordinates &other) const;
    PointCoordinates   &operator+=(const PointCoordinates &other) { append(other); return *this; }
    PointCoordinates   &operator+=(const coordT &c) { append(c); return *this; }
    PointCoordinates   &operator+=(const QhullPoint &p) { append(p); return *this; }
    PointCoordinates   &operator<<(const PointCoordinates &other) { return *this += other; }
    PointCoordinates   &operator<<(const coordT &c) { return *this += c; }
    PointCoordinates   &operator<<(const QhullPoint &p) { return *this += p; }
                        // reserve() is non-const
    void	        reserveCoordinates(int newCoordinates);

#//Helpers
private:
    int                 indexOffset(int i) const;

};//PointCoordinates

}//namespace orgQhull

#//Global functions

std::ostream           &operator<<(std::ostream &os, const orgQhull::PointCoordinates &p);

#endif // QHPOINTCOORDINATES_H