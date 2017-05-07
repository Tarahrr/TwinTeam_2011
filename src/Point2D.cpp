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
#include "Geometry.h"
#include <stdio.h>    // needed for sprintf

/*****************************************************************************/
/*******************   CLASS Point2D   ***********************************/
/*****************************************************************************/

/*! Constructor for the Point2D class. When the supplied
    Coordinate System type equals CARTESIAN, the arguments x and y
    denote the x- and y-coordinates of the new position. When it
    equals POLAR however, the arguments x and y denote the polar
    coordinates of the new position; in this case x is thus equal to
    the distance r from the origin and y is equal to the angle phi
    that the polar vector makes with the x-axis.
    \param x the x-coordinate of the new position when cs == CARTESIAN; the
    distance of the new position from the origin when cs = POLAR
    \param y the y-coordinate of the new position when cs = CARTESIAN; the
    angle that the polar vector makes with the x-axis when cs = POLAR
    \param cs a CoordSystemT indicating whether x and y denote cartesian
    coordinates or polar coordinates
    \return the Point2D corresponding to the given arguments */
Point2D::Point2D( double x, double y, CoordSystemT cs )
{
  setPoint2D( x, y, cs );
}

/*! Overloaded version of unary minus operator for Point2Ds. It returns the
    negative Point2D, i.e. both the x- and y-coordinates are multiplied by
    -1. The current Point2D itself is left unchanged.
    \return a negated version of the current Point2D */
Point2D Point2D::operator - ( )
{
  return ( Point2D( -m_x, -m_y ) );
}

/*! Overloaded version of the binary plus operator for adding a given double
    value to a Point2D. The double value is added to both the x- and
    y-coordinates of the current Point2D. The current Point2D itself is
    left unchanged.
    \param d a double value which has to be added to both the x- and
    y-coordinates of the current Point2D
    \return the result of adding the given double value to the current
    Point2D */
Point2D Point2D::operator + ( const double &d )
{
  return ( Point2D( m_x + d, m_y + d ) );
}

/*! Overloaded version of the binary plus operator for Point2Ds. It returns
    the sum of the current Point2D and the given Point2D by adding their
    x- and y-coordinates. The Point2Ds themselves are left unchanged.
    \param p a Point2D
    \return the sum of the current Point2D and the given Point2D */
Point2D Point2D::operator + ( const Point2D &p )
{
  return ( Point2D( m_x + p.m_x, m_y + p.m_y ) );
}

/*! Overloaded version of the binary minus operator for subtracting a
    given double value from a Point2D. The double value is
    subtracted from both the x- and y-coordinates of the current
    Point2D. The current Point2D itself is left unchanged.
    \param d a double value which has to be subtracted from both the x- and
    y-coordinates of the current Point2D
    \return the result of subtracting the given double value from the current
    Point2D */
Point2D Point2D::operator - ( const double &d )
{
  return ( Point2D( m_x - d, m_y - d ) );
}

/*! Overloaded version of the binary minus operator for
    Point2Ds. It returns the difference between the current
    Point2D and the given Point2D by subtracting their x- and
    y-coordinates. The Point2Ds themselves are left unchanged.

    \param p a Point2D
    \return the difference between the current Point2D and the given
    Point2D */
Point2D Point2D::operator - ( const Point2D &p )
{
  return ( Point2D( m_x - p.m_x, m_y - p.m_y ) );
}

/*! Overloaded version of the multiplication operator for multiplying a
    Point2D by a given double value. Both the x- and y-coordinates of the
    current Point2D are multiplied by this value. The current Point2D
    itself is left unchanged.
    \param d the multiplication factor
    \return the result of multiplying the current Point2D by the given
    double value */
Point2D Point2D::operator * ( const double &d  )
{
  return ( Point2D( m_x * d, m_y * d  ) );
}

/*! Overloaded version of the multiplication operator for
    Point2Ds. It returns the product of the current Point2D
    and the given Point2D by multiplying their x- and
    y-coordinates. The Point2Ds themselves are left unchanged.

    \param p a Point2D
    \return the product of the current Point2D and the given Point2D */
Point2D Point2D::operator * ( const Point2D &p )
{
  return ( Point2D( m_x * p.m_x, m_y * p.m_y ) );
}

/*! Overloaded version of the division operator for dividing a
    Point2D by a given double value. Both the x- and y-coordinates
    of the current Point2D are divided by this value. The current
    Point2D itself is left unchanged.

    \param d the division factor
    \return the result of dividing the current Point2D by the given double
    value */
Point2D Point2D::operator / ( const double &d )
{
  return ( Point2D( m_x / d, m_y / d  ) );
}

/*! Overloaded version of the division operator for Point2Ds. It
    returns the quotient of the current Point2D and the given
    Point2D by dividing their x- and y-coordinates. The
    Point2Ds themselves are left unchanged.

    \param p a Point2D
    \return the quotient of the current Point2D and the given one */
Point2D Point2D::operator / ( const Point2D &p )
{
  return ( Point2D( m_x / p.m_x, m_y / p.m_y ) );
}

/*! Overloaded version of the assignment operator for assigning a given double
    value to both the x- and y-coordinates of the current Point2D. This
    changes the current Point2D itself.
    \param d a double value which has to be assigned to both the x- and
    y-coordinates of the current Point2D */
void Point2D::operator = ( const double &d )
{
  m_x = d;
  m_y = d;
}

/*! Overloaded version of the sum-assignment operator for Point2Ds. It
    returns the sum of the current Point2D and the given Point2D by
    adding their x- and y-coordinates. This changes the current Point2D
    itself.
    \param p a Point2D which has to be added to the current Point2D */
void Point2D::operator +=( const Point2D &p )
{
  m_x += p.m_x;
  m_y += p.m_y;
}

/*! Overloaded version of the sum-assignment operator for adding a given double
    value to a Point2D. The double value is added to both the x- and
    y-coordinates of the current Point2D. This changes the current
    Point2D itself.
    \param d a double value which has to be added to both the x- and
    y-coordinates of the current Point2D */
void Point2D::operator += ( const double &d )
{
  m_x += d;
  m_y += d;
}

/*! Overloaded version of the difference-assignment operator for
    Point2Ds.  It returns the difference between the current
    Point2D and the given Point2D by subtracting their x- and
    y-coordinates. This changes the current Point2D itself.

    \param p a Point2D which has to be subtracted from the current
    Point2D */
void Point2D::operator -=( const Point2D &p )
{
  m_x -= p.m_x;
  m_y -= p.m_y;
}

/*! Overloaded version of the difference-assignment operator for
    subtracting a given double value from a Point2D. The double
    value is subtracted from both the x- and y-coordinates of the
    current Point2D. This changes the current Point2D itself.

    \param d a double value which has to be subtracted from both the x- and
    y-coordinates of the current Point2D */
void Point2D::operator -=( const double &d )
{
  m_x -= d;
  m_y -= d;
}

/*! Overloaded version of the multiplication-assignment operator for
    Point2Ds. It returns the product of the current Point2D
    and the given Point2D by multiplying their x- and
    y-coordinates. This changes the current Point2D itself.

    \param p a Point2D by which the current Point2D has to be
    multiplied */
void Point2D::operator *=( const Point2D &p )
{
  m_x *= p.m_x;
  m_y *= p.m_y;
}

/*! Overloaded version of the multiplication-assignment operator for
    multiplying a Point2D by a given double value. Both the x- and
    y-coordinates of the current Point2D are multiplied by this
    value. This changes the current Point2D itself.

    \param d a double value by which both the x- and y-coordinates of the
    current Point2D have to be multiplied */
void Point2D::operator *=( const double &d )
{
  m_x *= d;
  m_y *= d;
}

/*! Overloaded version of the division-assignment operator for
    Point2Ds. It returns the quotient of the current Point2D
    and the given Point2D by dividing their x- and
    y-coordinates. This changes the current Point2D itself.

    \param p a Point2D by which the current Point2D is divided */
void Point2D::operator /=( const Point2D &p )
{
  m_x /= p.m_x;
  m_y /= p.m_y;
}

/*! Overloaded version of the division-assignment operator for
    dividing a Point2D by a given double value. Both the x- and
    y-coordinates of the current Point2D are divided by this
    value. This changes the current Point2D itself.

    \param d a double value by which both the x- and y-coordinates of the
    current Point2D have to be divided */
void Point2D::operator /=( const double &d )
{
  m_x /= d;
  m_y /= d;
}

/*! Overloaded version of the inequality operator for Point2Ds. It
    determines whether the current Point2D is unequal to the given
    Point2D by comparing their x- and y-coordinates.

    \param p a Point2D
    \return true when either the x- or y-coordinates of the given Point2D
    and the current Point2D are different; false otherwise */
bool Point2D::operator !=( const Point2D &p )
{
  return ( ( m_x != p.m_x ) || ( m_y != p.m_y ) );
}

/*! Overloaded version of the inequality operator for comparing a
    Point2D to a double value. It determines whether either the x-
    or y-coordinate of the current Point2D is unequal to the given
    double value.

    \param d a double value with which both the x- and y-coordinates of the
    current Point2D have to be compared.
    \return true when either the x- or y-coordinate of the current Point2D
    is unequal to the given double value; false otherwise */
bool Point2D::operator !=( const double &d )
{
  return ( ( m_x != d ) || ( m_y != d ) );
}

/*! Overloaded version of the equality operator for Point2Ds. It
    determines whether the current Point2D is equal to the given
    Point2D by comparing their x- and y-coordinates.

    \param p a Point2D
    \return true when both the x- and y-coordinates of the given
    Point2D and the current Point2D are equal; false
    otherwise */
bool Point2D::operator ==( const Point2D &p )
{
  return ( ( m_x == p.m_x ) && ( m_y == p.m_y ) );
}

/*! Overloaded version of the equality operator for comparing a
    Point2D to a double value. It determines whether both the x-
    and y-coordinates of the current Point2D are equal to the
    given double value.

    \param d a double value with which both the x- and y-coordinates of the
    current Point2D have to be compared.
    \return true when both the x- and y-coordinates of the current Point2D
    are equal to the given double value; false otherwise */
bool Point2D::operator ==( const double &d )
{
  return ( ( m_x == d ) && ( m_y == d ) );
}

/*! Overloaded version of the C++ output operator for
    Point2Ds. This operator makes it possible to use Point2Ds
    in output statements (e.g.  cout << v). The x- and y-coordinates
    of the Point2D are printed in the format (x,y).

    \param os output stream to which information should be written
    \param v a Point2D which must be printed
    \return output stream containing (x,y) */
ostream& operator <<( ostream &os, Point2D v )
{
  return ( os << "( " << v.m_x << ", " << v.m_y << " )" );
}

/*! This method writes the current Point2D to standard output. It
    can also print a polar representation of the current Point2D.

    \param cs a CoordSystemtT indicating whether a POLAR or CARTESIAN
     representation of the current Point2D should be printed */
void Point2D::show( CoordSystemT cs )
{
  if( cs == CARTESIAN )
    cout << *this << endl;
  else
    cout << "( r: " << getMagnitude( ) << ", phi: " << getDirection( ) << "  )";
}

/*! This method writes the current Point2D to a string. It can
    also write a polar representation of the current Point2D.

    \param cs a CoordSystemtT indicating whether a POLAR or CARTESIAN
     representation of the current Point2D should be written
    \return a string containing a polar or Cartesian representation of the
    current Point2D depending on the value of the boolean argument */
string Point2D::str( CoordSystemT cs )
{
  char buf[ 1024 ];

  if( cs == CARTESIAN )
    sprintf( buf, "( %f, %f )", getX( ), getY( ) );
  else
    sprintf( buf, "( r: %f, phi: %f )", getMagnitude( ), getDirection( ) );

  string str( buf );
  return ( str );
}

/*! Set method for the x-coordinate of the current Point2D.

    \param dX a double value representing a new x-coordinate
    \return a boolean indicating whether the update was successful */
bool Point2D::setX( double dX )
{
  m_x = dX;
  return ( true );
}

/*! Get method for the x-coordinate of the current Point2D.

    \return the x-coordinate of the current Point2D */
double Point2D::getX( ) const
{
  return ( m_x );
}

/*! Set method for the y-coordinate of the current Point2D.

    \param dY a double value representing a new y-coordinate
    \return a boolean indicating whether the update was successful */
bool Point2D::setY( double dY )
{
  m_y = dY;
  return ( true );
}

/*! Get method for the y-coordinate of the current Point2D.

    \return the y-coordinate of the current Point2D */
double Point2D::getY( ) const
{
  return ( m_y );
}

/*! This method (re)sets the coordinates of the current
    Point2D. The given coordinates can either be polar or
    Cartesian coordinates. This is indicated by the value of the third
    argument.

    \param dX a double value indicating either a new Cartesian
    x-coordinate when cs=CARTESIAN or a new polar r-coordinate
    (distance) when cs=POLAR

    \param dY a double value indicating either a new Cartesian
    y-coordinate when cs=CARTESIAN or a new polar phi-coordinate
    (angle) when cs=POLAR

    \param cs a CoordSystemT indicating whether x and y denote
    cartesian coordinates or polar coordinates */
void Point2D::setPoint2D( double dX, double dY, CoordSystemT cs)
{
  if( cs == CARTESIAN )
  {
    m_x = dX;
    m_y = dY;
  }
  else
    *this = getPoint2DFromPolar( dX, dY );
}

/*! This method determines the distance between the current
    Point2D and a given Point2D. This is equal to the
    magnitude (length) of the vector connecting the two positions
    which is the difference vector between them.

    \param p a Point2D
    \return the distance between the current Point2D and the given
    Point2D */
double Point2D::getDistanceTo( const Point2D p )
{
  return ( ( *this - p ).getMagnitude( ) );
}
double Point2D::getDistanceTo(double x, double y)
{

  return sqrt( (m_x - x)*(m_x - x) + (m_y - y)*(m_y - y) );
}

/*! This method adjusts the coordinates of the current Point2D in
    such a way that the magnitude of the corresponding vector equals
    the double value which is supplied as an argument. It thus scales
    the vector to a given length by multiplying both the x- and
    y-coordinates by the quotient of the argument and the current
    magnitude. This changes the Point2D itself.

    \param d a double value representing a new magnitude

    \return the result of scaling the vector corresponding with the
    current Point2D to the given magnitude thus yielding a
    different Point2D */
Point2D Point2D::setMagnitude( double d )
{
  if( getMagnitude( ) > EPSILON )
     ( *this ) *= ( d / getMagnitude( ) );

  return ( *this );
}

/*! This method determines the magnitude (length) of the vector
    corresponding with the current Point2D using the formula of
    Pythagoras.

    \return the length of the vector corresponding with the current
    Point2D */
double Point2D::getMagnitude( ) const
{
  return ( sqrt( m_x * m_x + m_y * m_y ) );
}

/*! This method determines the direction of the vector corresponding
    with the current Point2D (the phi-coordinate in polar
    representation) using the arc tangent function. Note that the
    signs of x and y have to be taken into account in order to
    determine the correct quadrant.

    \return the direction in degrees of the vector corresponding with
    the current Point2D */
AngleDeg Point2D::getDirection( ) const
{
  return ( atan2Deg( m_y, m_x ) );
}

/*! This method determines whether the current Point2D is in front
    of a given Point2D, i.e. whether the x-coordinate of the
    current Point2D is larger than the x-coordinate of the given
    Point2D.

    \param p a Point2D to which the current Point2D must be compared
    \return true when the current Point2D is in front of the given
    Point2D; false otherwise */
bool Point2D::isInFrontOf( const Point2D &p )
{
  return ( ( m_x > p.getX( ) ) ? true : false );
}

/*! This method determines whether the x-coordinate of the current
    Point2D is in front of (i.e. larger than) a given double
    value.

    \param d a double value to which the current x-coordinate must be
    compared

    \return true when the current x-coordinate is in front of the
    given value; false otherwise */
bool Point2D::isInFrontOf( const double &d )
{
  return ( ( m_x > d ) ? true : false );
}

/*! This method determines whether the current Point2D is behind a
    given Point2D, i.e. whether the x-coordinate of the current
    Point2D is smaller than the x-coordinate of the given
    Point2D.

    \param p a Point2D to which the current Point2D must be
    compared

    \return true when the current Point2D is behind the given
    Point2D; false otherwise */
bool Point2D::isBehindOf( const Point2D &p )
{
  return ( ( m_x < p.getX( ) ) ? true : false );
}

/*! This method determines whether the x-coordinate of the current
    Point2D is behind (i.e. smaller than) a given double value.

    \param d a double value to which the current x-coordinate must be
    compared

    \return true when the current x-coordinate is behind the given
    value; false otherwise */
bool Point2D::isBehindOf( const double &d )
{
  return ( ( m_x < d ) ? true : false );
}

/*! This method determines whether the current Point2D is to the
    left of a given Point2D, i.e. whether the y-coordinate of the
    current Point2D is smaller than the y-coordinate of the given
    Point2D.

    \param p a Point2D to which the current Point2D must be
    compared

    \return true when the current Point2D is to the left of the
    given Point2D; false otherwise */
bool Point2D::isLeftOf( const Point2D &p )
{
  return ( ( m_y < p.getY( ) ) ? true : false );
}

/*! This method determines whether the y-coordinate of the current
    Point2D is to the left of (i.e. smaller than) a given double
    value.

    \param d a double value to which the current y-coordinate must be
    compared

    \return true when the current y-coordinate is to the left of the
    given value; false otherwise */
bool Point2D::isLeftOf( const double &d )
{
  return ( ( m_y < d ) ? true : false );
}

/*! This method determines whether the current Point2D is to the
    right of a given Point2D, i.e. whether the y-coordinate of the
    current Point2D is larger than the y-coordinate of the given
    Point2D.

    \param p a Point2D to which the current Point2D must be
    compared

    \return true when the current Point2D is to the right of the
    given Point2D; false otherwise */
bool Point2D::isRightOf( const Point2D &p )
{
  return ( ( m_y > p.getY( ) ) ? true : false );
}

/*! This method determines whether the y-coordinate of the current
    Point2D is to the right of (i.e. larger than) a given double
    value.

    \param d a double value to which the current y-coordinate must be
    compared

    \return true when the current y-coordinate is to the right of the
    given value; false otherwise */
bool Point2D::isRightOf( const double &d )
{
  return ( ( m_y > d ) ? true : false );
}

/*! This method determines whether the current Point2D is in
    between two given Point2Ds when looking in the x-direction,
    i.e. whether the current Point2D is in front of the first
    argument and behind the second.

    \param p1 a Point2D to which the current Point2D must be
    compared

    \param p2 a Point2D to which the current Point2D must be
    compared

    \return true when the current Point2D is in between the two
    given Point2Ds when looking in the x-direction; false
    otherwise */
bool Point2D::isBetweenX( const Point2D &p1, const Point2D &p2 )
{
  return ( ( isInFrontOf( p1 ) && isBehindOf( p2 ) ) ? true : false );
}

/*! This method determines whether the x-coordinate of the current
    Point2D is in between two given double values, i.e. whether
    the x-coordinate of the current Point2D is in front of the
    first argument and behind the second.

    \param d1 a double value to which the current x-coordinate must be
    compared

    \param d2 a double value to which the current x-coordinate must be
    compared

    \return true when the current x-coordinate is in between the two
    given values; false otherwise */
bool Point2D::isBetweenX( const double &d1, const double &d2 )
{
  return ( ( isInFrontOf( d1 ) && isBehindOf( d2 ) ) ? true : false );
}

/*! This method determines whether the current Point2D is in
    between two given Point2Ds when looking in the y-direction,
    i.e. whether the current Point2D is to the right of the first
    argument and to the left of the second.

    \param p1 a Point2D to which the current Point2D must be
    compared

    \param p2 a Point2D to which the current Point2D must be
    compared

    \return true when the current Point2D is in between the two
    given Point2Ds when looking in the y-direction; false
    otherwise */
bool Point2D::isBetweenY( const Point2D &p1, const Point2D &p2 )
{
  return ( ( isRightOf( p1 ) && isLeftOf( p2 ) ) ? true : false );
}

/*! This method determines whether the y-coordinate of the current
    Point2D is in between two given double values, i.e. whether
    the y-coordinate of the current Point2D is to the right of the
    first argument and to the left of the second.

    \param d1 a double value to which the current y-coordinate must be
    compared

    \param d2 a double value to which the current y-coordinate must be
    compared

    \return true when the current y-coordinate is in between the two
    given values; false otherwise */
bool Point2D::isBetweenY( const double &d1, const double &d2 )
{
  return ( ( isRightOf( d1 ) && isLeftOf( d2 ) ) ? true : false );
}

/*! This method normalizes a Point2D by setting the magnitude of
    the corresponding vector to 1. This thus changes the Point2D
    itself.

    \return the result of normalizing the current Point2D thus
    yielding a different Point2D */
Point2D Point2D::normalize( )
{
  return ( setMagnitude( 1.0 ) );
}

/*! This method rotates the vector corresponding to the current
    Point2D over a given angle thereby changing the current
    Point2D itself. This is done by calculating the polar
    coordinates of the current Point2D and adding the given angle
    to the phi-coordinate in the polar representation. The polar
    coordinates are then converted back to Cartesian coordinates to
    obtain the desired result.

    \param angle an angle in degrees over which the vector
    corresponding to the current Point2D must be rotated

    \return the result of rotating the vector corresponding to the
    current Point2D over the given angle thus yielding a different
    Point2D */
Point2D Point2D::rotate( AngleDeg angle )
{
  // determine the polar representation of the current Point2D
  double dMag    = this->getMagnitude( );
  double dNewDir = this->getDirection( ) + angle;  // add rotation angle to phi
  setPoint2D( dMag, dNewDir, POLAR );          // convert back to Cartesian
  return ( *this );
}

/*! This method converts the coordinates of the current Point2D
    (which are represented in an global coordinate system with the
    origin at (0,0)) into relative coordinates in a different
    coordinate system (e.g. relative to a player). The new coordinate
    system is defined by the arguments to the method. The relative
    coordinates are now obtained by aligning the relative coordinate
    system with the global coordinate system using a translation to
    make both origins coincide followed by a rotation to align the
    axes.

    \param origin the origin of the relative coordinate frame

    \param ang the angle between the world frame and the relative
    frame (reasoning from the world frame)

    \return the result of converting the current global Point2D
    into a relative Point2D */
Point2D Point2D::globalToRelative( Point2D origin, AngleDeg ang )
{
  // convert global coordinates into relative coordinates by aligning
  // relative frame and world frame. First perform translation to make
  // origins of both frames coincide. Then perform rotation to make
  // axes of both frames coincide (use negative angle since you rotate
  // relative frame to world frame).
  *this -= origin;
  return ( rotate( -ang ) );
}

/*! This method converts the coordinates of the current Point2D
    (which are represented in a relative coordinate system) into
    global coordinates in the world frame (with origin at (0,0)). The
    relative coordinate system is defined by the arguments to the
    method. The global coordinates are now obtained by aligning the
    world frame with the relative frame using a rotation to align the
    axes followed by a translation to make both origins coincide.

    \param origin the origin of the relative coordinate frame

    \param ang the angle between the world frame and the relative
    frame (reasoning from the world frame)

    \return the result of converting the current relative Point2D
    into an global Point2D */
Point2D Point2D::relativeToGlobal( Point2D origin, AngleDeg ang )
{
  // convert relative coordinates into global coordinates by aligning
  // world frame and relative frame. First perform rotation to make
  // axes of both frames coincide (use positive angle since you rotate
  // world frame to relative frame). Then perform translation to make
  // origins of both frames coincide.
  rotate( ang );
  *this += origin;
  return ( *this );
}

/*! This method returns a Point2D that lies somewhere on the
    vector between the current Point2D and a given
    Point2D. The desired position is specified by a given fraction
    of this vector (e.g. 0.5 means exactly in the middle of the
    vector). The current Point2D itself is left unchanged.

    \param p a Point2D which defines the vector to the current
    Point2D

    \param dFrac double representing the fraction of the connecting
    vector at which the desired Point2D lies.

    \return the Point2D which lies at fraction dFrac on the vector
    connecting p and the current Point2D */
Point2D Point2D::getPoint2DOnLineFraction( Point2D &p,
                                                       double      dFrac )
{
  // determine point on line that lies at fraction dFrac of whole line
  // example: this --- 0.25 ---------  p
  // formula: this + dFrac * ( p - this ) = this - dFrac * this + dFrac * p =
  //          ( 1 - dFrac ) * this + dFrac * p
  return ( ( *this ) * ( 1.0 - dFrac ) + ( p * dFrac ) );
}

/*! This method converts a polar representation of a Point2D into
    a Cartesian representation.

    \param dMag a double representing the polar r-coordinate, i.e. the
    distance from the point to the origin

    \param ang the angle that the polar vector makes with the x-axis,
    i.e. the polar phi-coordinate

    \return the result of converting the given polar representation
    into a Cartesian representation thus yielding a Cartesian
    Point2D */
Point2D Point2D::getPoint2DFromPolar( double dMag, AngleDeg ang )
{
  // cos(phi) = x/r <=> x = r*cos(phi); sin(phi) = y/r <=> y = r*sin(phi)
  return ( Point2D( dMag * cosDeg( ang ), dMag * sinDeg( ang ) ) );
}

/*! This method normalizes an angle. This means that the resulting
    angle lies between -180 and 180 degrees.

    \param angle the angle which must be normalized

    \return the result of normalizing the given angle */
AngleDeg Point2D::normalizeAngle( AngleDeg angle )
{
  while( angle > 180.0  ) angle -= 360.0;
  while( angle < -180.0 ) angle += 360.0;

  return ( angle );
}
