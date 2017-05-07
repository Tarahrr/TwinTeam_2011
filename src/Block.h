/* 
// -*-c++-*-

!
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

#ifndef BLOCK_H
#define BLOCK_H

#include <rcsc/geom/vector_2d.h>
#include <rcsc/player/soccer_action.h>
#include <rcsc/player/player_agent.h>
#include <string.h>
//#include <Geometry.h>

// #define mount ( "message") { cout<<message; };

// mount("saman");

class Block
 {
private:

public:
    /*!
      \brief accessible from global.
     */
    Block()
{}
bool 
new_Method( rcsc::PlayerAgent * agent );
bool
getBlockPosition( rcsc::PlayerAgent *agent,const rcsc::PlayerObject * opp,rcsc::Vector2D *pos_block);
bool
getBlockPoint( rcsc::Vector2D pos_opp, rcsc::Vector2D pos_agent, float cycle, float my_block_speed, float their_block_speed,rcsc::Vector2D *pos_block );
bool
getBlockSubPoint(rcsc::Vector2D opttarget ,rcsc::Vector2D opponent_pos , rcsc::Vector2D selfpos , float ratio_speed ,float predis ,rcsc::Vector2D *pos_block);

bool execute( rcsc::PlayerAgent * agent );

double
get_block_dash_power( rcsc::PlayerAgent * agent, rcsc::Vector2D target );

    bool doBlock( rcsc::PlayerAgent * agent,rcsc::Vector2D ballPos, float ballSpeed, int playerNums, 
	    rcsc::Vector2D *predictPlayers, int &finishTime, float &finalX, float &finalY );

float
max ( float a , float b ) {
  if ( a > b ) return a;
  if ( b > a ) return b ;
  else return b ;
}
  
  
  double 
getBlockDashPower( const rcsc::PlayerAgent * agent,
                             const rcsc::Vector2D & blockPos );


//  bool execute(rcsc::PlayerAgent* agent);
rcsc::Vector2D 
get_best_block_point( rcsc::PlayerAgent * agent ,rcsc::Vector2D point ,rcsc::Vector2D Payan , rcsc::Vector2D target );
// void blockCalc(rcsc::Vector2D ballPos, rcsc::Vector2D ballVel, int playerNums, rcsc::Vector2D *predictPlayers,
// 				    int &finishTime, float &finalX, float &finalY);
// 				    bool MarlikBlockCalc(  rcsc::PlayerAgent * agent  ,rcsc::Vector2D ballPos, float ballSpeed, int playerNums, 
// 	    rcsc::Vector2D *predictPlayers, int &finishTime, float &finalX, float &finalY );

 };
#endif