// -*-c++-*-

/*
 *Copyright:

 Copyright (C) Hidehisa AKIYAMA

 This code is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 3, or (at your option)
 any later version.

 This code is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this code; see the file COPYING.  If not, write to
 the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.

 *EndCopyright:
 */

/////////////////////////////////////////////////////////////////////

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "role_offensive_half.h"

#include "bhv_chain_action.h"
#include "bhv_basic_offensive_kick.h"
#include "bhv_basic_move.h"

#include <rcsc/player/player_agent.h>
#include <rcsc/player/debug_client.h>

#include <rcsc/common/logger.h>
#include <rcsc/action/body_turn_to_ball.h>
#include <rcsc/action/body_go_to_point.h>
#include "strategy.h"
#include <rcsc/action/neck_turn_to_ball.h>
#include <rcsc/action/neck_turn_to_ball_or_scan.h>
#include "neck_offensive_intercept_neck.h"
#include <rcsc/action/body_intercept.h>
#include "bhv_basic_tackle.h"
#include "Block.h"
#include <rcsc/common/server_param.h>

using namespace rcsc;

const std::string RoleOffensiveHalf::NAME( "OffensiveHalf" );

/*-------------------------------------------------------------------*/
/*!

 */
namespace {
rcss::RegHolder role = SoccerRole::creators().autoReg( &RoleOffensiveHalf::create,
                                                       RoleOffensiveHalf::NAME );
}

/*-------------------------------------------------------------------*/
/*!

 */
bool
RoleOffensiveHalf::execute( PlayerAgent * agent )
{
    bool kickable = agent->world().self().isKickable();
    if ( agent->world().existKickableTeammate()
         && agent->world().teammatesFromBall().front()->distFromBall()
         < agent->world().ball().distFromSelf() )
    {
        kickable = false;
    }

    if ( kickable )
    {
        doKick( agent );
    }
    else
    {
        doMove( agent );
    }

    return true;
}

/*-------------------------------------------------------------------*/
/*!

 */
void
RoleOffensiveHalf::doKick( PlayerAgent * agent )
{
    if ( Bhv_ChainAction().execute( agent ) )
    {
        return;
    }

    Bhv_BasicOffensiveKick().execute( agent );
}

/*-------------------------------------------------------------------*/
/*!

 */
void
RoleOffensiveHalf::doMove( PlayerAgent * agent )
{
  #if 1
    dlog.addText( Logger::TEAM,
                  __FILE__": Bhv_BasicMove" );

    //-----------------------------------------------
    // tackle
    if ( Bhv_BasicTackle( 0.8, 80.0 ).execute( agent ) )
    {
        return ;
    }

    const WorldModel & wm = agent->world();
//     bool intercept = false;
    /*--------------------------------------------------------*/
    // chase ball
    const int self_min = wm.interceptTable()->selfReachCycle();
    const int mate_min = wm.interceptTable()->teammateReachCycle();
    const int opp_min = wm.interceptTable()->opponentReachCycle();
    
    
    
    if ( ! wm.existKickableTeammate()
         and ( self_min <= 3
              || ( self_min <= mate_min
                   and self_min < opp_min + 3 )
              )
         )
    {
        Body_Intercept().execute( agent );
        agent->setNeckAction( new Neck_OffensiveInterceptNeck() );

        return ;
    }
    
        if ( self_min < mate_min and opp_min < mate_min and Block().execute(agent))
    {
      agent->setNeckAction(new Neck_OffensiveInterceptNeck());
      return ;
    } 

    
    double dist;
    double dash_power = Strategy::get_normal_dash_power( wm );    
    const Vector2D target_point = Strategy::i().getPosition( wm.self().unum() );
    const rcsc::AbstractPlayerObject *  opp = wm.getOpponentNearestToSelf(10,false);
    double opp_dist = opp->distFromSelf();
    if (  opp_dist < 15 and wm.self().pos().x < -5 ) dash_power = ServerParam::i().maxDashPower() * .9;

    double dist_thr = wm.ball().distFromSelf() * 0.1;

    if ( dist_thr < 1.0 ) dist_thr = 1.0;
    if ( ! Body_GoToPoint( target_point - Vector2D ( 4, 0 ), dist_thr, dash_power
                           ).execute( agent ) )
    {
        Body_TurnToBall().execute( agent );
    }

    if ( wm.existKickableOpponent()
         and wm.ball().distFromSelf() < 18.0 )
    {
        agent->setNeckAction( new Neck_TurnToBall() );
    }
    else
    {
        agent->setNeckAction( new Neck_TurnToBallOrScan() );
    }
#endif
    return ;

}
