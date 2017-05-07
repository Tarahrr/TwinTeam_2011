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
/***********************  CLASS LINE *****************************************/
/*****************************************************************************/

/*! This constructor creates a line by given the three coefficents of the line.
    A line is specified by the formula ay + bx + c = 0.
    \param dA a coefficients of the line
    \param dB b coefficients of the line
    \param dC c coefficients of the line */
Line::Line( double dA, double dB, double dC )
{
  m_a = dA;
  m_b = dB;
  m_c = dC;
}

Line::Line( )
{
  m_a = 0;
  m_b = 0;
  m_c = 0;
}

/*! This function prints the line to the specified output stream in the
    format y = ax + b.
    \param os output stream to which output is written
    \param l line that is written to output stream
    \return output sream to which output is appended. */
ostream& operator <<(ostream & os, Line l)
{
  double a = l.getACoefficient();
  double b = l.getBCoefficient();
  double c = l.getCCoefficient();

  // ay + bx + c = 0 -> y = -b/a x - c/a
  if( a == 0 )
    os << "x = " << -c/b;
  else
  {
    os << "y = ";
    if( b != 0 )
      os << -b/a << "x ";
    if( c > 0 )
       os << "- " <<  fabs(c/a);
    else if( c < 0 )
       os << "+ " <<  fabs(c/a);
  }
  return os;
}

/*! This method prints the line information to the specified output stream.
    \param os output stream to which output is written. */
void Line::show( ostream& os)
{
  os << *this;
}

/*! This method returns the intersection point between the current Line and
    the specified line.
    \param line line with which the intersection should be calculated.
    \return Point2D position that is the intersection point. */
Point2D Line::getIntersection( Line line )
{
  Point2D pos;
  double x, y;
  if( ( m_a / m_b ) ==  (line.getACoefficient() / line.getBCoefficient() ))
    return pos; // lines are parallel, no intersection
  if( m_a == 0 )            // bx + c = 0 and a2*y + b2*x + c2 = 0 ==> x = -c/b
  {                          // calculate x using the current line
    x = -m_c/m_b;                // and calculate the y using the second line
    y = line.getYGivenX(x);
  }
  else if( line.getACoefficient() == 0 )
  {                         // ay + bx + c = 0 and b2*x + c2 = 0 ==> x = -c2/b2
   x = -line.getCCoefficient()/line.getBCoefficient(); // calculate x using
   y = getYGivenX(x);       // 2nd line and calculate y using current line
  }
  // ay + bx + c = 0 and a2y + b2*x + c2 = 0
  // y = (-b2/a2)x - c2/a2
  // bx = -a*y - c =>  bx = -a*(-b2/a2)x -a*(-c2/a2) - c ==>
  // ==> a2*bx = a*b2*x + a*c2 - a2*c ==> x = (a*c2 - a2*c)/(a2*b - a*b2)
  // calculate x using the above formula and the y using the current line
  else
  {
    x = (m_a*line.getCCoefficient() - line.getACoefficient()*m_c)/
                    (line.getACoefficient()*m_b - m_a*line.getBCoefficient());
    y = getYGivenX(x);
  }

  return Point2D( x, y );
}


/*! This method calculates the intersection points between the current line
    and the circle specified with as center 'posCenter' and radius 'dRadius'.
    The number of solutions are returned and the corresponding points are put
    in the third and fourth argument of the method
    \param c circle with which intersection points should be found
    \param posSolution1 first intersection (if any)
    \param posSolution2 second intersection (if any) */
int Line::getCircleIntersectionPoints( Circle circle,
              Point2D *posSolution1, Point2D *posSolution2 )
{
  int    iSol;
  double dSol1=0, dSol2=0;
  double h = circle.getCenter().getX();
  double k = circle.getCenter().getY();

  // line:   x = -c/b (if a = 0)
  // circle: (x-h)^2 + (y-k)^2 = r^2, with h = center.x and k = center.y
  // fill in:(-c/b-h)^2 + y^2 -2ky + k^2 - r^2 = 0
  //         y^2 -2ky + (-c/b-h)^2 + k^2 - r^2 = 0
  // and determine solutions for y using abc-formula
  if( fabs(m_a) < EPSILON )
  {
    iSol = Geometry::abcFormula( 1, -2*k, ((-m_c/m_b) - h)*((-m_c/m_b) - h)
              + k*k - circle.getRadius()*circle.getRadius(), &dSol1, &dSol2);
    posSolution1->setPoint2D( (-m_c/m_b), dSol1 );
    posSolution2->setPoint2D( (-m_c/m_b), dSol2 );
    return iSol;
  }

  // ay + bx + c = 0 => y = -b/a x - c/a, with da = -b/a and db = -c/a
  // circle: (x-h)^2 + (y-k)^2 = r^2, with h = center.x and k = center.y
  // fill in:x^2 -2hx + h^2 + (da*x-db)^2 -2k(da*x-db) + k^2 - r^2 = 0
  //         x^2 -2hx + h^2 + da^2*x^2 + 2da*db*x + db^2 -2k*da*x -2k*db
  //                                                         + k^2 - r^2 = 0
  //       (1+da^2)*x^2 + 2(da*db-h-k*da)*x + h2 + db^2  -2k*db + k^2 - r^2 = 0
  // and determine solutions for x using abc-formula
  // fill in x in original line equation to get y coordinate
  double da = -m_b/m_a;
  double db = -m_c/m_a;

  double dA = 1 + da*da;
  double dB = 2*( da*db - h - k*da );
  double dC = h*h + db*db-2*k*db + k*k - circle.getRadius()*circle.getRadius();

  iSol = Geometry::abcFormula( dA, dB, dC, &dSol1, &dSol2 );

  posSolution1->setPoint2D( dSol1, da*dSol1 + db );
  posSolution2->setPoint2D( dSol2, da*dSol2 + db );
  return iSol;

}

/*! This method returns the tangent line to a Point2D. This is the line
    between the specified position and the closest point on the line to this
    position.
    \param pos Point2D point with which tangent line is calculated.
    \return Line line tangent to this position */
Line Line::getTangentLine( Point2D pos )
{
  // ay + bx + c = 0 -> y = (-b/a)x + (-c/a)
  // tangent: y = (a/b)*x + C1 -> by - ax + C2 = 0 => C2 = ax - by
  // with pos.y = y, pos.x = x
  return Line( m_b, -m_a, m_a*pos.getX() - m_b*pos.getY() );
}

/*! This method returns the closest point on a line to a given position.
    \param pos point to which closest point should be determined
    \return Point2D closest point on line to 'pos'. */
Point2D Line::getPointOnLineClosestTo( Point2D pos )
{
  Line l2 = getTangentLine( pos );  // get tangent line
  return getIntersection( l2 );     // and intersection between the two lines
}

/*! This method returns the distance between a specified position and the
    closest point on the given line.
    \param pos position to which distance should be calculated
    \return double indicating the distance to the line. */
double Line::getDistanceWithPoint( Point2D pos )
{
  return pos.getDistanceTo( getPointOnLineClosestTo( pos ) );
}

/*! This method determines whether the projection of a point on the
    current line lies between two other points ('point1' and 'point2')
    that lie on the same line.

    \param pos point of which projection is checked.
    \param point1 first point on line
    \param point2 second point on line
    \return true when projection of 'pos' lies between 'point1' and 'point2'.*/
bool Line::isInBetween( Point2D pos, Point2D point1,Point2D point2)
{
  pos          = getPointOnLineClosestTo( pos ); // get closest point
  double dDist = point1.getDistanceTo( point2 ); // get distance between 2 pos

  // if the distance from both points to the projection is smaller than this
  // dist, the pos lies in between.
  return pos.getDistanceTo( point1 ) <= dDist &&
         pos.getDistanceTo( point2 ) <= dDist;
}

/*! This method calculates the y coordinate given the x coordinate
    \param x coordinate
    \return y coordinate on this line */
double Line::getYGivenX( double x )
{
 if( m_a == 0 )
 {
   cerr << "(Line::getYGivenX) Cannot calculate Y coordinate: " ;
   show( cerr );
   cerr << endl;
   return 0;
 }
  // ay + bx + c = 0 ==> ay = -(b*x + c)/a
  return -(m_b*x+m_c)/m_a;
}

/*! This method calculates the x coordinate given the x coordinate
    \param y coordinate
    \return x coordinate on this line */
double Line::getXGivenY( double y )
{
 if( m_b == 0 )
 {
   cerr << "(Line::getXGivenY) Cannot calculate X coordinate\n" ;
   return 0;
 }
  // ay + bx + c = 0 ==> bx = -(a*y + c)/a
  return -(m_a*y+m_c)/m_b;
}

/*! This method creates a line given two points.
    \param pos1 first point
    \param pos2 second point
    \return line that passes through the two specified points. */
Line Line::makeLineFromTwoPoints( Point2D pos1, Point2D pos2 )
{
  // 1*y + bx + c = 0 => y = -bx - c
  // with -b the direction coefficient (or slope)
  // and c = - y - bx
  double dA, dB, dC;
  double dTemp = pos2.getX() - pos1.getX(); // determine the slope
  if( fabs(dTemp) < EPSILON )
  {
    // ay + bx + c = 0 with vertical slope=> a = 0, b = 1
    dA = 0.0;
    dB = 1.0;
  }
  else
  {
    // y = (-b)x -c with -b the slope of the line
    dA = 1.0;
    dB = -(pos2.getY() - pos1.getY())/dTemp;
  }
  // ay + bx + c = 0 ==> c = -a*y - b*x
  dC =  - dA*pos2.getY()  - dB * pos2.getX();
  return Line( dA, dB, dC );
}

/*! This method creates a line given a position and an angle.
    \param vec position through which the line passes
    \param angle direction of the line.
    \return line that goes through position 'vec' with angle 'angle'. */
Line Line::makeLineFromPositionAndAngle( Point2D vec, AngleDeg angle )
{
  // calculate point somewhat further in direction 'angle' and make
  // line from these two points.
  return makeLineFromTwoPoints( vec, vec+Point2D(1,angle,POLAR));
}

/*! This method returns the a coefficient from the line ay + bx + c = 0.
    \return a coefficient of the line. */
double Line::getACoefficient() const
{
  return m_a;
}

/*! This method returns the b coefficient from the line ay + bx + c = 0.
    \return b coefficient of the line. */
double Line::getBCoefficient() const
{
 return m_b;
}

/*! This method returns the c coefficient from the line ay + bx + c = 0.
    \return c coefficient of the line. */
double Line::getCCoefficient() const
{
 return m_c;
}


void Line::setABC(double a,double b,double c){

  m_a = a;
  m_b = b;
  m_c = c;
}

AngleRad Line::getAngle()
{    /*
        return the ang that is between 0-PI/2.0
      */
AngleRad kAngle=atan2(-m_b,m_a);
  if (-m_b*m_a>=0)  return kAngle;
    else return kAngle+M_PI;
}

AngleRad Line::getAngle(Line line)
{
   AngleRad ang = getAngle()-line.getAngle();
  if (ang>=0)
      return  ang;
      else  return ang+M_PI;
}

Line Line::getLineAngleBisector(Line line)
{ /* this method returns the ang-bisector of two lines--itself and line
    return a line whose angle is between 0-PI/2.0;
    use rad of deg for ang????????  not test yet
   */
  AngleRad  ang=getAngle(line);

	 ang=getAngle()-ang/2.0; //angle of bisector
                       // suitable for goal point determine
                       // not sure about other situations.
   Point2D interSection=getIntersection(line);
   return Line::makeLineFromPositionAndAngle(interSection,Rad2Deg(ang));
}

