/* 
// -*-c++-*-

/*!
  \file bhv_emergency.h
  \brief behavior for emergency situation header file
*/

/*
 *Copyright:

 Copyright (C) Hidehisa AKIYAMA

 This code is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 3 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

 *EndCopyright:
 */

/////////////////////////////////////////////////////////////////////

#ifndef MARK_H
#define MARK_H

#include <rcsc/geom/vector_2d.h>
#include <rcsc/player/soccer_action.h>
#include <rcsc/player/player_agent.h>

#if 1
/*!
  \class Bhv_Emergency
  \brief behavior for emergency situations. just scan field.
 */


class Mark    : public rcsc::SoccerBehavior
 {
private:

public:
    /*!
      \brief accessible from global.
     */
    Mark()
{}


    bool execute(  rcsc::PlayerAgent * agent );
    bool mark_all_opp(rcsc::PlayerAgent * agent);

//     bool MarkOpponentAll(rcsc::PlayerAgent * agent);
};
#endif
#endif*/
