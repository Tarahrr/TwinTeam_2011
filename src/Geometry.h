/***************************************************************************
 *   Copyright (C) 2009 by BlueGene MAS Lab.                               *
 *   info@bluegene.ir                                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation;                                         *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
/*
Copyright (c) 2000-2003, Jelle Kok, University of Amsterdam
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

3. Neither the name of the University of Amsterdam nor the names of its
contributors may be used to endorse or promote products derived from this
software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*! \file Geometry.h
<pre>
<b>File:</b>          Geometry.h
<b>Project:</b>       Robocup Soccer Simulation Team: UvA Trilearn
<b>Authors:</b>       Jelle Kok
<b>Created:</b>       12/02/2001
<b>Last Revision:</b> $ID$
<b>Contents:</b>      Header file for the classes Point2D, Geometry, Line,
               Circle and Rectangle. All the member
               data and member method declarations for all these classes can be
               found in this file together with some auxiliary functions for
               numeric and goniometric purposes.
<hr size=2>
<h2><b>Changes</b></h2>
<b>Date</b>             <b>Author</b>          <b>Comment</b>
12/02/2001       Jelle Kok       Initial version created
09/06/2001       Remco de Boer   Version including full documentation completed
</pre>
*/

#ifndef _GEOMETRY_
#define _GEOMETRY_

#include "math.h"       // needed for M_PI constant
#include <string>       // needed for string
#include <iostream>

using namespace std;

typedef double AngleRad;  /*!< Type definition for angles in degrees. */
typedef double AngleDeg;  /*!< Type definition for angles in radians. */

#define EPSILON 0.0001  /*!< Value used for floating point equality tests. */

// auxiliary numeric functions for determining the
// maximum and minimum of two given double values and the sign of a value
double max     ( double d1, double d2 );
double min     ( double d1, double d2 );
int    sign    ( double d1            );

// auxiliary goniometric functions which enable you to
// specify angles in degrees rather than in radians
AngleDeg Rad2Deg ( AngleRad x             );
AngleRad Deg2Rad ( AngleDeg x             );
double cosDeg  ( AngleDeg x             );
double sinDeg  ( AngleDeg x             );
double tanDeg  ( AngleDeg x             );
AngleDeg atanDeg ( double x             );
double atan2Deg( double x,  double y  );
AngleDeg acosDeg ( double x             );
AngleDeg asinDeg ( double x             );

// various goniometric functions
bool   isAngInInterval     ( AngleDeg ang,    AngleDeg angMin,    AngleDeg angMax );
AngleDeg getBisectorTwoAngles( AngleDeg angMin, AngleDeg angMax );

/*! CoordSystem is an enumeration of the different specified
    coordinate systems.  The two possibilities are CARTESIAN or
    POLAR. These values are for instance used in the initializing a
    Point2D. The CoordSystem indicates whether the supplied
    arguments represent the position in cartesian or in polar
    coordinates. */
enum CoordSystemT {
  CARTESIAN,
  POLAR
};

/*****************************************************************************/
/********************   CLASS PONIT2D   **********************************/
/*****************************************************************************/

/*! This class contains an x- and y-coordinate of a position (x,y) as
    member data and methods which operate on this position. The
    standard arithmetic operators are overloaded and can thus be
    applied to positions (x,y). It is also possible to represent a
    position in polar coordinates (r,phi), since the class contains a
    method to convert these into cartesian coordinates (x,y). */
class Point2D
{
  // private member data
private:

  double m_x;   /*!< x-coordinate of this position */
  double m_y;   /*!< y-coordinate of this position */

  // public methods
public:
  // constructor for Point2D class
  Point2D                               ( double            vx = 0,
                                              double            vy = 0,
                                              CoordSystemT      cs =CARTESIAN);

  // overloaded arithmetic operators
  Point2D        operator -             (                                );
  Point2D        operator +             ( const double      &d           );
  Point2D        operator +             ( const Point2D &p           );
  Point2D        operator -             ( const double      &d           );
  Point2D        operator -             ( const Point2D &p           );
  Point2D        operator *             ( const double      &d           );
  Point2D        operator *             ( const Point2D &p           );
  Point2D        operator /             ( const double      &d           );
  Point2D        operator /             ( const Point2D &p           );
  void               operator =             ( const double      &d           );
  void               operator +=            ( const Point2D &p           );
  void               operator +=            ( const double      &d           );
  void               operator -=            ( const Point2D &p           );
  void               operator -=            ( const double      &d           );
  void               operator *=            ( const Point2D &p           );
  void               operator *=            ( const double      &d           );
  void               operator /=            ( const Point2D &p           );
  void               operator /=            ( const double      &d           );
  bool               operator !=            ( const Point2D &p           );
  bool               operator !=            ( const double      &d           );
  bool               operator ==            ( const Point2D &p           );
  bool               operator ==            ( const double      &d           );

  // methods for producing output
  friend ostream&    operator <<            ( ostream           &os,
                                              Point2D       p            );
  void               show                   ( CoordSystemT      cs =CARTESIAN);
  string             str                    ( CoordSystemT      cs =CARTESIAN);

  // set- and get methods for private member variables
  bool               setX                   ( double            dX           );
  double             getX                   (                          ) const;
  bool               setY                   ( double            dY           );
  double             getY                   (                          ) const;

/*CmorQ high level*/
  bool               addX                   ( double          addX           );
  bool               addY                   ( double          addY           );


  // set- and get methods for derived position information
  void               setPoint2D         ( double            dX = 0,
                                              double            dY = 0,
                                              CoordSystemT      cs =CARTESIAN);
  double             getDistanceTo          ( const Point2D p            );
  double             getDistanceTo          ( double            x,
                                              double            y            );

  Point2D        setMagnitude           ( double            d            );
  double             getMagnitude           (                          ) const;
  AngleDeg             getDirection           (                          ) const;

  // comparison methods for positions
  bool               isInFrontOf            ( const Point2D &p           );
  bool               isInFrontOf            ( const double      &d           );
  bool               isBehindOf             ( const Point2D &p           );
  bool               isBehindOf             ( const double      &d           );
  bool               isLeftOf               ( const Point2D &p           );
  bool               isLeftOf               ( const double      &d           );
  bool               isRightOf              ( const Point2D &p           );
  bool               isRightOf              ( const double      &d           );
  bool               isBetweenX             ( const Point2D &p1,
                                              const Point2D &p2          );
  bool               isBetweenX             ( const double      &d1,
                                              const double      &d2          );
  bool               isBetweenY             ( const Point2D &p1,
                                              const Point2D &p2          );
  bool               isBetweenY             ( const double      &d1,
                                              const double      &d2          );

  // conversion methods for positions
  Point2D        normalize              (                                );
  Point2D        rotate                 ( AngleDeg            angle        );
  Point2D        globalToRelative       ( Point2D       orig,
                                              AngleDeg            ang          );
  Point2D        relativeToGlobal       ( Point2D       orig,
                                              AngleDeg            ang          );
  Point2D        getPoint2DOnLineFraction( Point2D  &p,
                                              double            dFrac        );

  // static class methods
  static Point2D getPoint2DFromPolar( double            dMag,
                                              AngleDeg            ang          );
  static AngleDeg      normalizeAngle         ( AngleDeg            angle        );
};

/*****************************************************************************/
/*********************   CLASS GEOMETRY   ************************************/
/*****************************************************************************/

/*! This class contains several static methods dealing with geometry.*/
class Geometry
{

public:

  // geometric series
  static double getLengthGeomSeries(double dFirst,double dRatio,double dSum  );
  static double getSumGeomSeries   (double dFirst,double dRatio,double dLen  );
  static double getSumInfGeomSeries(double dFirst,double dRatio              );
  static double getFirstGeomSeries (double dSum,  double dRatio,double dLen  );
  static double getFirstInfGeomSeries(double dSum,double dRatio              );

  // abc formula
  static int    abcFormula(double a,double b, double c, double *s1,double *s2);
};

/*****************************************************************************/
/********************** CLASS CIRCLE *****************************************/
/*****************************************************************************/

/*!This class represents a circle. A circle is defined by one Point2D
   (which denotes the center) and its radius. */
class Circle
{
    Point2D m_posCenter;            /*!< Center of the circle  */
    double      m_dRadius;              /*!< Radius of the circle  */

public:
    Circle( );
    Circle( Point2D pos, double dR );

    void        show                  ( ostream& os = cout );

    // get and set methods
    bool        setCircle             ( Point2D pos,
                                        double      dR  );
    bool        setRadius             ( double dR       );
    double      getRadius             (                 );
    bool        setCenter             ( Point2D pos );
    Point2D getCenter             (                 );
    double      getCircumference      (                 );
    double      getArea               (                 );

    // calculate intersection points and area with other circle
    bool        isInside              ( Point2D pos );
    int         getIntersectionPoints ( Circle      c,
                                        Point2D *p1,
                                        Point2D *p2 );
    double      getIntersectionArea   ( Circle c        );


}  ;

/*****************************************************************************/
/*********************** CLASS LINE ******************************************/
/*****************************************************************************/

/*!This class contains the representation of a line. A line is defined
   by the formula ay + bx + c = 0. The coefficients a, b and c are stored
   and used in the calculations. */
class Line
{
  // a line is defined by the formula: ay + bx + c = 0
  double m_a; /*!< This is the a coefficient in the line ay + bx + c = 0 */
  double m_b; /*!< This is the b coefficient in the line ay + bx + c = 0 */
  double m_c; /*!< This is the c coefficient in the line ay + bx + c = 0 */

public:
  Line( double a, double b, double c );
  Line();
  // print methods
  void        show( ostream& os = cout );
  friend      ostream& operator << (ostream & os, Line l);

  // get intersection points with this line
  Point2D getIntersection            ( Line        line                  );
  int         getCircleIntersectionPoints( Circle      circle,
                                           Point2D *posSolution1,
                                           Point2D *posSolution2         );
  Line        getTangentLine             ( Point2D pos                   );
  Point2D getPointOnLineClosestTo    ( Point2D pos                   );
  double      getDistanceWithPoint       ( Point2D pos                   );
  bool        isInBetween                ( Point2D pos,
                                           Point2D point1,
                                           Point2D point2                );

  // calculate associated variables in the line
  double      getYGivenX                 ( double      x );
  double      getXGivenY                 ( double      y );
  double      getACoefficient            (               ) const;
  double      getBCoefficient            (               ) const;
  double      getCCoefficient            (               ) const;
  // static methods to make a line using an easier representation.
  static Line makeLineFromTwoPoints      ( Point2D pos1,
                                           Point2D pos2                  );
  static Line makeLineFromPositionAndAngle( Point2D vec,
                                           AngleDeg angle                      );
  void setABC(double a,double b,double c);
  AngleRad getAngle			(	);
  AngleRad getAngle     (Line line);
  Line   getLineAngleBisector		(Line 		line);		
};

/*****************************************************************************/
/********************** CLASS RECTANGLE **************************************/
/******************************************************************************/
/*!This class represents a rectangle. A rectangle is defined by two
   Point2Ds the one at the upper left corner and the one at the
   right bottom. */
class Rect
{
  Point2D m_posLeftTop;     /*!< top left position of the rectangle      */
  Point2D m_posRightBottom; /*!< bottom right position of the rectangle  */

public:
  Rect                          ( Point2D pos, Point2D pos2 );

  void        show              ( ostream& os = cout                );

  // checks whether point lies inside the rectangle
  bool        isInside          ( Point2D pos                   );

  // standard get and set methosd
  void        setRectanglePoints( Point2D pos1,
                                  Point2D pos2                  );
  bool        setPosLeftTop     ( Point2D pos                   );
  Point2D getPosLeftTop     (                                   );
  bool        setPosRightBottom ( Point2D pos                   );
  Point2D getPosRightBottom (                                   );


};

class ControlPoint
{
public:

	ControlPoint(){};
	~ControlPoint(){};
	Point2D CP[15][50];
	int	CpNum[15];
	double weight[15][50];
	void  GetPositionCP(char * posFile);
};


#endif
