 
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

#ifndef DRIBBLE_H
#define DRIBBLE_H

#include <rcsc/geom/vector_2d.h>
#include <rcsc/player/soccer_action.h>
#include <rcsc/player/player_agent.h>


/*!
  \class Bhv_Emergency
  \brief behavior for emergency situations. just scan field.
 */

enum DRIBBLE_REGION
{
Region_11,
Region_10,
Region_13,
Region_9,
Region_12,
Region_1,
Region_illegal
};



class Dribble    : public rcsc::SoccerBehavior
 {
private:

public:
    /*!
      \brief accessible from global.
     */
    Dribble()
{}


    /*!
      \brief execute action
      \param agent pointer to the agent itself
      \return true if action is performed
     */
    bool execute(  rcsc::PlayerAgent * agent );

DRIBBLE_REGION 
get_dribble_region(rcsc::PlayerAgent * agent);

rcsc::Vector2D
get_target_point( rcsc::PlayerAgent * agent);


bool
fast_dribble( rcsc::PlayerAgent * agent );
};

#endif
