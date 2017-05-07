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
/********************* CLASS CIRCLE ******************************************/
/*****************************************************************************/

/*! This is the constructor of a circle.
    \param pos first point that defines the center of circle
    \param dR the radius of the circle
    \return circle with pos as center and radius as radius*/
Circle::Circle( Point2D pos, double dR )
{
  setCircle( pos, dR );
}

/*! This is the constructor of a circle which initializes a circle with a
    radius of zero. */
Circle::Circle( )
{
  setCircle( Point2D(-1000.0,-1000.0), 0);
}

/*! This method prints the circle information to the specified output stream
    in the following format: "c: (c_x,c_y), r: rad" where (c_x,c_y) denotes
    the center of the circle and rad the radius.
    \param os output stream to which output is written. */
void Circle::show( ostream& os)
{
  os << "c:" << m_posCenter << ", r:" << m_dRadius;
}

/*! This method sets the values of the circle.
    \param pos new center of the circle
    \param dR new radius of the circle
    ( > 0 )
    \return bool indicating whether radius was set */
bool Circle::setCircle( Point2D pos, double dR )
{
  setCenter( pos );
  return setRadius( dR  );
}
/*! This method sets the radius of the circle.
    \param dR new radius of the circle ( > 0 )
    \return bool indicating whether radius was set */
bool Circle::setRadius( double dR )
{
  if( dR > 0 )
  {
    m_dRadius = dR;
    return true;
  }
  else
  {
    m_dRadius = 0.0;
    return false;
  }
}

/*! This method returns the radius of the circle.
    \return radius of the circle */
double Circle::getRadius()
{
  return m_dRadius;
}

/*! This method sets the center of the circle.
    \param pos new center of the circle
    \return bool indicating whether center was set */
bool Circle::setCenter( Point2D pos )
{
  m_posCenter = pos;
  return true;
}

/*! This method returns the center of the circle.
    \return center of the circle */
Point2D Circle::getCenter()
{
  return m_posCenter;
}

/*! This method returns the circumference of the circle.
    \return circumference of the circle */
double Circle::getCircumference()
{
  return 2.0*M_PI*getRadius();
}

/*! This method returns the area inside the circle.
    \return area inside the circle */
double Circle::getArea()
{
  return M_PI*getRadius()*getRadius();
}

/*! This method returns a boolean that indicates whether 'pos' is
    located inside the circle.
 
   \param pos position of which should be checked whether it is
   located in the circle

   \return bool indicating whether pos lies inside the circle */
bool Circle::isInside( Point2D pos )
{
  return m_posCenter.getDistanceTo( pos ) < getRadius() ;
}

/*! This method returns the two possible intersection points between two
    circles. This method returns the number of solutions that were found.
    \param c circle with which intersection should be found
    \param p1 will be filled with first solution
    \param p2 will be filled with second solution
    \return number of solutions. */
int Circle::getIntersectionPoints( Circle c, Point2D *p1, Point2D *p2)
{
    double x0, y0, r0;
    double x1, y1, r1;

    x0 = getCenter( ).getX();
    y0 = getCenter( ).getY();
    r0 = getRadius( );
    x1 = c.getCenter( ).getX();
    y1 = c.getCenter( ).getY();
    r1 = c.getRadius( );

    double      d, dx, dy, h, a, x, y, p2_x, p2_y;

    // first calculate distance between two centers circles P0 and P1.
    dx = x1 - x0;
    dy = y1 - y0;
    d = sqrt(dx*dx + dy*dy);

    // normalize differences
    dx /= d; dy /= d;

    // a is distance between p0 and point that is the intersection point P2
    // that intersects P0-P1 and the line that crosses the two intersection
    // points P3 and P4.
    // Define two triangles: P0,P2,P3 and P1,P2,P3.
    // with distances a, h, r0 and b, h, r1 with d = a + b
    // We know a^2 + h^2 = r0^2 and b^2 + h^2 = r1^2 which then gives
    // a^2 + r1^2 - b^2 = r0^2 with d = a + b ==> a^2 + r1^2 - (d-a)^2 = r0^2
    // ==> r0^2 + d^2 - r1^2 / 2*d
    a = (r0*r0 + d*d - r1*r1) / (2.0 * d);

    // h is then a^2 + h^2 = r0^2 ==> h = sqrt( r0^2 - a^2 )
    double      arg = r0*r0 - a*a;
    h = (arg > 0.0) ? sqrt(arg) : 0.0;

    // First calculate P2
    p2_x = x0 + a * dx;
    p2_y = y0 + a * dy;

    // and finally the two intersection points
    x =  p2_x - h * dy;
    y =  p2_y + h * dx;
    p1->setPoint2D( x, y );
    x =  p2_x + h * dy;
    y =  p2_y - h * dx;
    p2->setPoint2D( x, y );

    return (arg < 0.0) ? 0 : ((arg == 0.0 ) ? 1 :  2);
}

/*! This method returns the size of the intersection area of two circles.
    \param c circle with which intersection should be determined
    \return size of the intersection area. */
double Circle::getIntersectionArea( Circle c )
{
  Point2D pos1, pos2, pos3;
  double d, h, dArea;
  AngleDeg ang;

  d = getCenter().getDistanceTo( c.getCenter() ); // dist between two centers
  if( d > c.getRadius() + getRadius() )           // larger than sum radii
    return 0.0;                                   // circles do not intersect
  if( d <= fabs(c.getRadius() - getRadius() ) )   // one totally in the other
  {
    double dR = min( c.getRadius(), getRadius() );// return area smallest circ
    return M_PI*dR*dR;
  }

  int iNrSol = getIntersectionPoints( c, &pos1, &pos2 );
  if( iNrSol != 2 )
    return 0.0;

  // the intersection area of two circles can be divided into two segments:
  // left and right of the line between the two intersection points p1 and p2.
  // The outside area of each segment can be calculated by taking the part
  // of the circle pie excluding the triangle from the center to the
  // two intersection points.
  // The pie equals pi*r^2 * rad(2*ang) / 2*pi = 0.5*rad(2*ang)*r^2 with ang
  // the angle between the center c of the circle and one of the two
  // intersection points. Thus the angle between c and p1 and c and p3 where
  // p3 is the point that lies halfway between p1 and p2.
  // This can be calculated using ang = asin( d / r ) with d the distance
  // between p1 and p3 and r the radius of the circle.
  // The area of the triangle is 2*0.5*h*d.

  pos3 = pos1.getPoint2DOnLineFraction( pos2, 0.5 );
  d = pos1.getDistanceTo( pos3 );
  h = pos3.getDistanceTo( getCenter() );
  ang = asin( d / getRadius() );

  dArea = ang*getRadius()*getRadius();
  dArea = dArea - d*h;

  // and now for the other segment the same story
  h = pos3.getDistanceTo( c.getCenter() );
  ang = asin( d / c.getRadius() );
  dArea = dArea + ang*c.getRadius()*c.getRadius();
  dArea = dArea - d*h;

  return dArea;
}

