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

/*! \file Geometry.cpp
<pre>
<b>File:</b>          Geometry.cpp
<b>Project:</b>       Robocup Soccer Simulation Team: UvA Trilearn
<b>Authors:</b>       Jelle Kok
<b>Created:</b>       13/02/2001
<b>Last Revision:</b> $ID$
<b>Contents:</b>      class declarations of different geometry classes:<BR>
                       - Point2D: representation of a point
                       - Line:        representation of a line
                       - Rectangle:   representation of a rectangle
                       - Circle:      representation of a circle
                       - Geometry:    different geometry methods

Furthermore it contains some goniometric functions to work with sine, cosine
and tangent functions using degrees and some utility functions to return
the maximum and the minimum of two values.
<hr size=2>
<h2><b>Changes</b></h2>
<b>Date</b>             <b>Author</b>          <b>Comment</b>
12/02/2001       Jelle Kok       Initial version created
</pre>
*/

#include "Geometry.h"
#include <stdio.h>    // needed for sprintf

/*! This function returns the sign of a give double.
    1 is positive, -1 is negative
    \param d1 first parameter
    \return the sign of this double */
int sign( double d1 )
{
  return (d1>0)?1:-1;
}

/*! This function returns the maximum of two given doubles.
    \param d1 first parameter
    \param d2 second parameter
    \return the maximum of these two parameters */
double max( double d1, double d2 )
{
  return (d1>d2)?d1:d2;
}

/*! This function returns the minimum of two given doubles.
    \param d1 first parameter
    \param d2 second parameter
    \return the minimum of these two parameters */
double min( double d1, double d2 )
{
  return (d1<d2)?d1:d2;
}


/*! This function converts an angle in radians to the corresponding angle in
    degrees.
    \param x an angle in radians
    \return the corresponding angle in degrees */
AngleDeg Rad2Deg( AngleRad x )
{
  return ( x * 180 / M_PI );
}

/*! This function converts an angle in degrees to the corresponding angle in
    radians.
    \param x an angle in degrees
    \return the corresponding angle in radians */
AngleRad Deg2Rad( AngleDeg x )
{
  return ( x * M_PI / 180 );
}

/*! This function returns the cosine of a given angle in degrees using the
    built-in cosine function that works with angles in radians.
    \param x an angle in degrees
    \return the cosine of the given angle */
double cosDeg( AngleDeg x )
{
  return ( cos( Deg2Rad( x ) ) );
}

/*! This function returns the sine of a given angle in degrees using the
    built-in sine function that works with angles in radians.
    \param x an angle in degrees
    \return the sine of the given angle */
double sinDeg( AngleDeg x )
{
  return ( sin( Deg2Rad( x ) ) );
}

/*! This function returns the tangent of a given angle in degrees using the
    built-in tangent function that works with angles in radians.
    \param x an angle in degrees
    \return the tangent of the given angle */
double tanDeg( AngleDeg x )
{
  return ( tan( Deg2Rad( x ) ) );
}

/*! This function returns the principal value of the arc tangent of x
    in degrees using the built-in arc tangent function which returns
    this value in radians.
    \param x a double value
    \return the arc tangent of the given value in degrees */
AngleDeg atanDeg( double x )
{
  return ( Rad2Deg( atan( x ) ) );
}

/*! This function returns the principal value of the arc tangent of y/x in
    degrees using the signs of both arguments to determine the quadrant of the
    return value. For this the built-in 'atan2' function is used which returns
    this value in radians.
    \param x a double value
    \param y a double value
    \return the arc tangent of y/x in degrees taking the signs of x and y into
    account */
double atan2Deg( double x, double y )
{
  if( fabs( x ) < EPSILON && fabs( y ) < EPSILON )
    return ( 0.0 );

  return ( Rad2Deg( atan2( x, y ) ) );
}

/*! This function returns the principal value of the arc cosine of x in degrees
    using the built-in arc cosine function which returns this value in radians.
    \param x a double value
    \return the arc cosine of the given value in degrees */
AngleDeg acosDeg( double x )
{
  if( x >= 1 )
    return ( 0.0 );
  else if( x <= -1 )
    return ( 180.0 );

  return ( Rad2Deg( acos( x ) ) );
}

/*! This function returns the principal value of the arc sine of x in degrees
    using the built-in arc sine function which returns this value in radians.
    \param x a double value
    \return the arc sine of the given value in degrees */
AngleDeg asinDeg( double x )
{
  if( x >= 1 )
    return ( 90.0 );
  else if ( x <= -1 )
    return ( -90.0 );

  return ( Rad2Deg( asin( x ) ) );
}

/*! This function returns a boolean value which indicates whether the value
   'ang' (from interval [-180..180] lies in the interval [angMin..angMax].
    Examples: isAngInInterval( -100, 4, -150) returns false
             isAngInInterval(   45, 4, -150) returns true
    \param ang angle that should be checked
    \param angMin minimum angle in interval
    \param angMax maximum angle in interval
    \return boolean indicating whether ang lies in [angMin..angMax] */
bool isAngInInterval( AngleDeg ang, AngleDeg angMin, AngleDeg angMax )
{
  // convert all angles to interval 0..360
  if( ( ang    + 360 ) < 360 ) ang    += 360;
  if( ( angMin + 360 ) < 360 ) angMin += 360;
  if( ( angMax + 360 ) < 360 ) angMax += 360;

  if( angMin < angMax ) // 0 ---false-- angMin ---true-----angMax---false--360
    return angMin < ang && ang < angMax ;
  else                  // 0 ---true--- angMax ---false----angMin---true---360
    return !( angMax < ang && ang < angMin );
}

/*! This method returns the bisector (average) of two angles. It deals
    with the boundary problem, thus when 'angMin' equals 170 and 'angMax'
    equals -100, -145 is returned.
    \param angMin minimum angle [-180,180]
    \param angMax maximum angle [-180,180]
    \return average of angMin and angMax. */
AngleDeg getBisectorTwoAngles( AngleDeg angMin, AngleDeg angMax )
{
  // separate sine and cosine part to circumvent boundary problem
  return Point2D::normalizeAngle(
            atan2Deg( (sinDeg( angMin) + sinDeg( angMax ) )/2.0,
                      (cosDeg( angMin) + cosDeg( angMax ) )/2.0 ) );
}



/*****************************************************************************/
/********************** CLASS GEOMETRY ***************************************/
/*****************************************************************************/

/*! A geometric series is one in which there is a constant ratio between each
    element and the one preceding it. This method determines the
    length of a geometric series given its first element, the sum of the
    elements in the series and the constant ratio between the elements.
    Normally: s = a + ar + ar^2 + ...  + ar^n
    Now: dSum = dFirst + dFirst*dRatio + dFirst*dRatio^2 + .. + dFist*dRatio^n
    \param dFirst first term of the series
    \param dRatio ratio with which the the first term is multiplied
    \param dSum the total sum of all the serie
    \return the length(n in above example) of the series */
double Geometry::getLengthGeomSeries( double dFirst, double dRatio, double dSum )
{
  if( dRatio < 0 )
    cerr << "(Geometry:getLengthGeomSeries): negative ratio" << endl;

  // s = a + ar + ar^2 + .. + ar^n-1 and thus sr = ar + ar^2 + .. + ar^n
  // subtract: sr - s = - a + ar^n) =>  s(1-r)/a + 1 = r^n = temp
  // log r^n / n = n log r / log r = n = length
  double temp = (dSum * ( dRatio - 1 ) / dFirst) + 1;
  if( temp <= 0 )
    return -1.0;
  return log( temp ) / log( dRatio ) ;
}

/*! A geometric series is one in which there is a constant ratio between each
    element and the one preceding it. This method determines the sum of a
    geometric series given its first element, the ratio and the number of steps
    in the series
    Normally: s = a + ar + ar^2 + ...  + ar^n
    Now: dSum = dFirst + dFirst*dRatio + ... + dFirst*dRatio^dSteps
    \param dFirst first term of the series
    \param dRatio ratio with which the the first term is multiplied
    \param dSum the number of steps to be taken into account
    \return the sum of the series */
double Geometry::getSumGeomSeries( double dFirst, double dRatio, double dLength)
{
  // s = a + ar + ar^2 + .. + ar^n-1 and thus sr = ar + ar^2 + .. + ar^n
  // subtract: s - sr = a - ar^n) =>  s = a(1-r^n)/(1-r)
  return dFirst * ( 1 - pow( dRatio, dLength ) ) / ( 1 - dRatio ) ;
}

/*! A geometric series is one in which there is a constant ratio between each
    element and the one preceding it. This method determines the sum of an
    infinite geometric series given its first element and the constant ratio
    between the elements. Note that such an infinite series will only converge
    when 0<r<1.
    Normally: s = a + ar + ar^2 + ar^3 + ....
    Now: dSum = dFirst + dFirst*dRatio + dFirst*dRatio^2...
    \param dFirst first term of the series
    \param dRatio ratio with which the the first term is multiplied
    \return the sum of the series */
double Geometry::getSumInfGeomSeries( double dFirst, double dRatio )
{
  if( dRatio > 1 )
    cerr << "(Geometry:CalcLengthGeomSeries): series does not converge" <<endl;

  // s = a(1-r^n)/(1-r) with n->inf and 0<r<1 => r^n = 0
  return dFirst / ( 1 - dRatio );
}

/*! A geometric series is one in which there is a constant ratio between each
    element and the one preceding it. This method determines the first element
    of a geometric series given its element, the ratio and the number of steps
    in the series
    Normally: s = a + ar + ar^2 + ...  + ar^n
    Now: dSum = dFirst + dFirst*dRatio + ... + dFirst*dRatio^dSteps
    \param dSum sum of the series
    \param dRatio ratio with which the the first term is multiplied
    \param dSum the number of steps to be taken into account
    \return the first element (a) of a serie */
double Geometry::getFirstGeomSeries( double dSum, double dRatio, double dLength)
{
  // s = a + ar + ar^2 + .. + ar^n-1 and thus sr = ar + ar^2 + .. + ar^n
  // subtract: s - sr = a - ar^n) =>  s = a(1-r^n)/(1-r) => a = s*(1-r)/(1-r^n)
  return dSum *  ( 1 - dRatio )/( 1 - pow( dRatio, dLength ) ) ;
}

/*! A geometric series is one in which there is a constant ratio between each
    element and the one preceding it. This method determines the first element
    of an infinite geometric series given its first element and the constant
    ratio between the elements. Note that such an infinite series will only
    converge when 0<r<1.
    Normally: s = a + ar + ar^2 + ar^3 + ....
    Now: dSum = dFirst + dFirst*dRatio + dFirst*dRatio^2...
    \param dSum sum of the series
    \param dRatio ratio with which the the first term is multiplied
    \return the first term of the series */
double Geometry::getFirstInfGeomSeries( double dSum, double dRatio )
{
  if( dRatio > 1 )
    cerr << "(Geometry:getFirstInfGeomSeries):series does not converge" <<endl;

  // s = a(1-r^n)/(1-r) with r->inf and 0<r<1 => r^n = 0 => a = s ( 1 - r)
  return dSum * ( 1 - dRatio );
}

/*! This method performs the abc formula (Pythagoras' Theorem) on the given
    parameters and puts the result in *s1 en *s2. It returns the number of
    found coordinates.
    \param a a parameter in abc formula
    \param b b parameter in abc formula
    \param c c parameter in abc formula
    \param *s1 first result of abc formula
    \param *s2 second result of abc formula
    \return number of found x-coordinates */
int Geometry::abcFormula(double a, double b, double c, double *s1, double *s2)
{
  double dDiscr = b*b - 4*a*c;       // discriminant is b^2 - 4*a*c
  if (fabs(dDiscr) < EPSILON )       // if discriminant = 0
  {
    *s1 = -b / (2 * a);              //  only one solution
    return 1;
  }
  else if (dDiscr < 0)               // if discriminant < 0
    return 0;                        //  no solutions
  else                               // if discriminant > 0
  {
    dDiscr = sqrt(dDiscr);           //  two solutions
    *s1 = (-b + dDiscr ) / (2 * a);
    *s2 = (-b - dDiscr ) / (2 * a);
    return 2;
  }
}




bool Point2D::addX( double addX )
{
  m_x += addX;
  return ( true );
}
bool Point2D::addY( double addY )
{
  m_y += addY;
  return ( true );
}


/*****************************************************************************/
/********************** TESTING PURPOSES *************************************/
/*****************************************************************************/

/*
#include<iostream.h>

int main( void )
{
  double dFirst = 1.0;
  double dRatio = 2.5;
  double dSum   = 63.4375;
  double dLength = 4.0;

  printf( "sum: %f\n", Geometry::getSumGeomSeries( dFirst, dRatio, dLength));
  printf( "length: %f\n", Geometry::getLengthGeomSeries( dFirst, dRatio, dSum));
}

int main( void )
{
  Line l1(1,-1,3 );
  Line l2(1,-0.2,10 );
 Line l3 = Line::makeLineFromTwoPoints( Point2D(1,-1), Point2D(2,-2) );
 l3.show();
 cout << endl;
 l1.show();
 l2.show();
  l1.getIntersection( l2 ).show();
}


int main( void )
{
  Line l( 1, -1, 0 );
  Point2D s1, s2;
  int i = l.getCircleIntersectionPoints( Circle( Point2D(1,1),1) &s1,&s2 );
  printf( "number of solutions: %d\n", i );
  if( i == 2 )
  {
    cout << s1 << " " << s2 ;
  }
  else if( i == 1 )
  {
    cout << s1;
  }
  cout << "line: " << l;
}

int main( void )
{
  Circle c11( Point2D( 10, 0 ), 10);
  Circle c12( Point2D( 40, 3 ), 40 );
  Circle c21( Point2D(  0,0 ), 5);
  Circle c22( Point2D(  3,0 ), 40 );

  Point2D p1, p2;

  cout << c11.getIntersectionArea( c21 ) << endl;
  cout << c12.getIntersectionArea( c21 ) << endl;
  cout << c22.getIntersectionArea( c11 ) << endl;
  cout << c12.getIntersectionArea( c22 ) << endl;
  return 0;
}

int main( void )
{
  cout << getBisectorTwoAngles( -155.3, 179.0 ) << endl;
  cout << getBisectorTwoAngles( -179.3, 179.0 ) << endl;
}
*/
