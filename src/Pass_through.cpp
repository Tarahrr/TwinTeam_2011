#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "Pass_through.h"
#include"strategy.h"

#include "Pass.h"


#include <rcsc/player/self_intercept_v13.h>
#include <rcsc/player/player_intercept.h>

#include <rcsc/action/body_advance_ball.h>
#include <rcsc/action/body_dribble.h>
#include <rcsc/action/body_hold_ball.h>
#include <rcsc/action/body_smart_kick.h>
#include <rcsc/action/body_kick_one_step.h>
#include <rcsc/action/neck_scan_field.h>
#include <rcsc/action/neck_turn_to_point.h>
#include <rcsc/action/neck_turn_to_low_conf_teammate.h>
#include <rcsc/player/say_message_builder.h>
#include <rcsc/player/player_agent.h>
#include <rcsc/player/debug_client.h>

#include <rcsc/common/logger.h>
#include <rcsc/common/server_param.h>
#include <rcsc/geom/sector_2d.h>

using namespace rcsc;
using namespace std;
/*-------------------------------------------------------------------*/
/*!

 */

bool
PassThrough::execute ( rcsc::PlayerAgent * agent, rcsc::PlayerObject * teammate )
{

return false;

}

#if 0
{

    const rcsc::WorldModel & wm = agent->world();

    rcsc::Segment2D 	seg1 (teammate->pos(),Vector2D( teammate->pos().x + 20, teammate->pos().y ));
    AngleDeg orgin_dir = seg1.direction();
    
    rcsc::Segment2D     seg2 (teammate->pos(),20,orgin_dir + 45);
    rcsc::Segment2D 	seg3 (teammate->pos(),20,orgin_dir - 45);
    Circle2D cir1 ( teammate->pos(), 12 );
    Circle2D cir2 ( teammate->pos(),  6 );
    Vector2D intr[5];

    cir1.intersection(seg1,&intr[0],NULL);
    cir1.intersection(seg2,&intr[1],NULL);
    cir1.intersection(seg3,&intr[2],NULL);

    cir2.intersection(seg1,&intr[3],NULL);
    cir2.intersection(seg2,&intr[4],NULL);
    cir2.intersection(seg3,&intr[5],NULL);

   double reach__x = 6.5;
    bool is_offe = ( teammate->pos().x < -36 ? true : false );
    if ( is_offe ) reach__x = 5;
    
      intr[0] = Vector2D( teammate->pos().x + reach__x, teammate->pos().y );
      intr[0] = Vector2D( teammate->pos().x + reach__x, teammate->pos().y + 5 );    
      intr[0] = Vector2D( teammate->pos().x + reach__x, teammate->pos().y - 5 );
    
    Vector2D target =intr [ 0 ];
    Vector2D target_check;
    bool success = true;
    
    if ( intr[0].x > intr[1].x )
    {
        if ( intr[0].x > intr[2].x )
            target = intr[0];
        target_check = intr[3];
    }
    if ( intr[0].x < intr[1].x )
    {
        if ( intr[1].x > intr[2].x )
            target = intr[1];
        target_check = intr[4];
    }

    if ( intr[2].x > intr[1].x )
    {
        if ( intr[2].x > intr[0].x )
            target = intr[2];
        target_check = intr[5];
    }

    rcsc::Segment2D 	ceg  ( wm.self().pos(),target);
    Vector2D inter;
    Circle2D self ( wm.self().pos(),wm.self().pos().dist(target) /2 );
    self.intersection(ceg,&inter,NULL);

    const rcsc::PlayerObject * opp = wm.getOpponentNearestTo(target,5,NULL);

    int tmm_to_reach = teammate->playerTypePtr()->cyclesToReachDistance(teammate->pos().dist(target_check));
    int cycle_to_reach_opp = opp->playerTypePtr()->cyclesToReachDistance(opp->pos().dist(target_check));

    const rcsc::PlayerObject * opp_line = wm.getOpponentNearestTo(inter,5,NULL);
    int opp_line_reach = opp_line->playerTypePtr()->cyclesToReachDistance(opp_line->pos().dist(inter));
    int ball_line_reach = wm.ball().calc_travel_step(wm.ball().pos().dist(inter),1.5);


    const rcsc::PlayerObject * opp_tar = wm.getOpponentNearestTo(target,5,NULL);
//     if (!opp_tar) return false;
    int opp_tar_reach = opp_tar->playerTypePtr()->cyclesToReachDistance(opp_tar->pos().dist(target));
    int cycle_to_tar_tmm = teammate->playerTypePtr()->cyclesToReachDistance(teammate->pos().dist(target));

//     rcsc::Sector2D sec (wm.self().pos(),.5, wm.self().pos().dist(target),( wm.self().pos() -target ).th() + 15, ( wm.self().pos() - target ).th() - 15 );

    agent->setNeckAction(new Neck_TurnToPoint(target));

    rcsc::Segment2D seg ( wm.self().pos(),target );
//     if ( teammate->pos().x < wm.self().pos().x + 5 ) success =  false;

   
    rcsc::Vector2D top_left;
    rcsc::Vector2D bottom_right;
    bool is_offe_ = ( wm.self().pos().dist( teammate->pos() ) > 12 ? true : false );
    double rect_dist = 8;
    if ( is_offe_ ) rect_dist = 10;
    
    if ( teammate->pos().x > wm.self().pos().x )
    {
        top_left.x = wm.self().pos().x;
        bottom_right.x = teammate->pos().x + rect_dist;
    }
    else
    {
        top_left.x = teammate->pos().x - rect_dist;
        bottom_right.x = wm.self().pos().x;
    }
    if ( teammate->pos().y < wm.self().pos().y )
    {
        top_left.y = teammate->pos().y - rect_dist;
        bottom_right.y = wm.self().pos().y;
    }
    else
    {
        top_left.y = wm.self().pos().y;
        bottom_right.y = teammate->pos().y + rect_dist;
    }

    rcsc::Rect2D rect ( top_left, bottom_right );


/*    const PlayerPtrCont::const_iterator
    t_end = wm.opponentsFromBall().end();
    for ( PlayerPtrCont::const_iterator
            it = wm.opponentsFromBall().begin();
            it != t_end;
            ++it )
    {*/
//         Circle2D cir ( (*it)->pos(),3 );

//         if ( cir.intersection(seg,NULL,NULL) > 0 ) success = false;
        
//         if ( opp_line_reach < ball_line_reach /*- 2*/ ) success =  false;
if ( teammate->unum() < 9 ) success = false;
	if ( cycle_to_reach_opp + 2 < cycle_to_tar_tmm /*- 2*/ ) success = false;
//         if ( opp_tar_reach < cycle_to_tar_tmm /*- 2*/ ) success = false;
    if ( wm.existOpponentIn<Rect2D>(rect,5,false) ) success =  false;
        double speed = Pass().getBestSpeed(agent,target);
        if (success)
        {
	  	cout<<" TPASS " <<endl;

            Body_SmartKick( target, speed, speed * .98, 1).execute(agent);
            return true;
        }
//     }
    return false;
}
# endif
