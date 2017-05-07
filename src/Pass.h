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

#ifndef PASS_H
#define PASS_H

#include <rcsc/geom/vector_2d.h>
#include <rcsc/player/soccer_action.h>
#include <rcsc/player/player_agent.h>

enum PASS_REGION
{
Region_11_PASS,
Region_10_PASS,
Region_13_PASS,
Region_9_PASS,
Region_12_PASS,
Region_1_PASS,
Region_illegal_PASS
};

class Pass    : public rcsc::SoccerBehavior
 {
private:
public:
    Pass( )
{}
    bool execute(  rcsc::PlayerAgent * agent );

    double
    get_weight_with_dist( rcsc::PlayerAgent * agent, rcsc::Vector2D target );

    double
    get_weight_with_X( rcsc::PlayerAgent * agent, rcsc::Vector2D target );

    double 
    get_weight_with_dist_opp( rcsc::PlayerAgent * agent, rcsc::Vector2D target );

    double
    get_weight_with_sector(rcsc::PlayerAgent * agent, rcsc::Vector2D target);

    PASS_REGION
    get_pass_region(rcsc::PlayerAgent * agent);

    double
    getBestSpeed ( rcsc::PlayerAgent * agent,rcsc::Vector2D target );

    double
    getBestSpeed_test_pass( rcsc::PlayerAgent * agent,rcsc::Vector2D target );

    bool
    pass_test ( rcsc::PlayerAgent * agent, rcsc::PlayerObject * teammate );

    int 
    getBallCycle ( const rcsc::PlayerAgent * agent, double dist );

    bool
    pass_test_through ( rcsc::PlayerAgent * agent, rcsc::PlayerObject * teammate );	
	
    bool
    pass_test_leading ( rcsc::PlayerAgent * agent, rcsc::PlayerObject * teammate );


     bool
     pass_cross ( rcsc::PlayerAgent * agent, rcsc::PlayerObject * teammate );

    double 
    getDashDist ( const rcsc::PlayerObject * player, int dash_count );
};

#endif
