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
/********************* CLASS RECTANGLE ***************************************/
/*****************************************************************************/

/*! This is the constructor of a Rectangle. Two points will be given. The
    order does not matter as long as two opposite points are given (left
    top and right bottom or right top and left bottom).
    \param pos first point that defines corner of rectangle
    \param pos2 second point that defines other corner of rectangle
    \return rectangle with 'pos' and 'pos2' as opposite corners. */
Rect::Rect( Point2D pos, Point2D pos2 )
{
  setRectanglePoints( pos, pos2 );
}

/*! This method sets the upper left and right bottom point of the current
    rectangle.
    \param pos first point that defines corner of rectangle
    \param pos2 second point that defines other corner of rectangle */
void Rect::setRectanglePoints( Point2D pos1, Point2D pos2 )
{
  m_posLeftTop.setX    ( max( pos1.getX(), pos2.getX() ) );
  m_posLeftTop.setY    ( min( pos1.getY(), pos2.getY() ) );
  m_posRightBottom.setX( min( pos1.getX(), pos2.getX() ) );
  m_posRightBottom.setY( max( pos1.getY(), pos2.getY() ) );
}

/*! This method prints the rectangle to the specified output stream in the
    format rect( top_left_point, bottom_right_point ).
    \param os output stream to which rectangle is written. */
void Rect::show( ostream& os )
{
  os << "rect(" << m_posLeftTop << " " << m_posRightBottom << ")";
}

/*! This method determines whether the given position lies inside the current
    rectangle.
    \param pos position which is checked whether it lies in rectangle
    \return true when 'pos' lies in the rectangle, false otherwise */
bool Rect::isInside( Point2D pos )
{
  return pos.isBetweenX( m_posRightBottom.getX(), m_posLeftTop.getX() ) &&
         pos.isBetweenY( m_posLeftTop.getY(),     m_posRightBottom.getY() );

}

/*! This method sets the top left position of the rectangle
    \param pos new top left position of the rectangle
    \return true when update was successful */
bool Rect::setPosLeftTop( Point2D pos )
{
  m_posLeftTop = pos;
  return true;
}

/*! This method returns the top left position of the rectangle
    \return top left position of the rectangle */
Point2D Rect::getPosLeftTop(  )
{
  return m_posLeftTop;
}

/*! This method sets the right bottom position of the rectangle
    \param pos new right bottom position of the rectangle
    \return true when update was succesfull */
bool Rect::setPosRightBottom( Point2D pos )
{
  m_posRightBottom = pos;
  return true;
}

/*! This method returns the right bottom position of the rectangle
    \return top right bottom of the rectangle */
Point2D Rect::getPosRightBottom(  )
{
  return m_posRightBottom;
}

