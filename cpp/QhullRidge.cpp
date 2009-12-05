/****************************************************************************
**
** Copyright (C) 2008-2009 C. Bradford Barber. All rights reserved.
** $Id: //product/qhull/main/rel/cpp/QhullRidge.cpp#11 $$Change: 1052 $
** $DateTime: 2009/09/27 23:20:48 $$Author: bbarber $
**
****************************************************************************/

#//! QhullRidge -- Qhull's ridge structure, ridgeT, as a C++ class

#include "QhullSets.h"
#include "QhullVertex.h"
#include "QhullRidge.h"

#ifdef _MSC_VER  // Microsoft Visual C++ -- warning level 4 
#pragma warning( disable : 4611)  // interaction between '_setjmp' and C++ object destruction is non-portable
#pragma warning( disable : 4996)  // function was declared deprecated(strcpy, localtime, etc.)
#endif

namespace orgQhull {

#//class statics
ridgeT QhullRidge::
s_empty_ridge= {};

#//Constructor, destructor, etc.

#//Accessors
//! Return next ridge and optional vertex for a 3d facet and ridge
//! Returns !isDefined() if no more ridges 
//! Does not use qh_qh or qh_errexit()
QhullRidge QhullRidge::
nextRidge3d(const QhullFacet f, QhullVertex *nextVertex) const
{
    vertexT *v= 0;
    ridgeT *ridge= qh_nextridge3d(getRidgeT(), f.getFacetT(), &v);
    if(!ridge){
        throw QhullError(10030, "Qhull error nextRidge3d:  missing next ridge for facet %d ridge %d.  Does facet contain ridge?", f.id(), id());
    }
    if(nextVertex!=0){
        *nextVertex= QhullVertex(v);
    }
    return QhullRidge(ridge);
}//nextRidge3d


}//namespace orgQhull

#//Global functions

using std::endl;
using std::ostream;
using orgQhull::QhullRidge;
using orgQhull::QhullVertex;
using orgQhull::UsingQhullLib;

ostream &
operator<<(ostream &os, const QhullRidge &r)
{      
    os<< r.print(UsingQhullLib::NOqhRunId); 
    return os; 
}//<< QhullRidge

//! Duplicate of qh_printridge [io.c]
//!  if pr.run_id==UsingQhullLib::NOqhRunId, no access to qh [needed for QhullVertex/QhullPoint]
ostream &
operator<<(ostream &os, const QhullRidge::PrintRidge &pr)
{ 
    QhullRidge r= *pr.ridge;
    os<< "     - r" << r.id();
    if(r.getRidgeT()->tested){
        os<< " tested";
    }
    if(r.getRidgeT()->nonconvex){
        os<< " nonconvex";
    }
    os<< endl;
    os<< r.vertices().print(pr.run_id, "           vertices:");
    //FIXUP -- what if top or bottom are NULL?
    if(r.getRidgeT()->top && r.getRidgeT()->bottom){
        os<< "           between f" << r.topFacet().id() << " and f" << r.bottomFacet().id() << endl;
    }
    return os;
}//<< PrintRidge
