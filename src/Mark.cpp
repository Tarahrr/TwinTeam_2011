#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "Mark.h"
#include "strategy.h"

#include <rcsc/action/body_advance_ball.h>
#include <rcsc/action/body_dribble.h>
#include <rcsc/action/body_hold_ball.h>
#include <rcsc/action/body_pass.h>
#include <rcsc/action/neck_scan_field.h>
#include <rcsc/action/neck_turn_to_low_conf_teammate.h>

#include <rcsc/player/player_agent.h>
#include <rcsc/player/debug_client.h>



#include <Geometry.h>

#include <math.h>


#include <rcsc/common/logger.h>
#include <rcsc/common/server_param.h>
#include <rcsc/geom/sector_2d.h>
#include <rcsc/player/say_message_builder.h>
#include <rcsc/action/body_go_to_point.h>
#include <rcsc/player/intercept_table.h>
#include <strategy.h>
#include <rcsc/action/body_intercept.h>

using namespace std;
using namespace rcsc;
/*-------------------------------------------------------------------*/
/*!

 */
bool
Mark::execute( rcsc::PlayerAgent * agent )
{
//   Strategy::
    const rcsc::WorldModel & wm = agent->world();
    if ( Strategy::get_ball_area(wm.ball().pos()) == Strategy::BA_CrossBlock and Strategy::get_ball_area(wm.ball().pos()) == Strategy::BA_Danger)
    {
#if 0  
if ( wm.getTeammateNearestToBall(10,false)->unum() == wm.self().unum() )
        {
//             Body_Intercept().execute(agent);
	    return false;

        }
#endif
// 	const rcsc::PlayerObject *tmm = wm.getTeammateNearestToBall(3,false) ;
// 	if(tmm->unum() == wm.self().unum()) return false;

        if ( mark_all_opp(agent) )
            return true;
    }
    return false;
}
bool
Mark::mark_all_opp (rcsc::PlayerAgent * agent)

{
    const rcsc::WorldModel & wm = agent->world();
    int number[10] = {2,3,4,5,6,7,8,9,10,11};
    const rcsc::PlayerObject * opp = wm.getOpponentNearestToSelf(10,false);
    const rcsc::PlayerPtrCont & opps = wm.opponentsFromSelf();
    if ( opps.size() == 0 ) return false;
    if ( !opp ) return false;
    int num = opp->unum();
    bool success = true ;
    Circle2D cir  (opp->pos(),3.14);
    if ( wm.existTeammateIn(cir,10,false)) success = false;

    if (success)
    {
        if (opp->pos().y > wm.ball().pos().y)
        {

            if (opp->pos().x < wm.ball().pos().x)
            {
                Vector2D point = Vector2D(opp->pos().x+1 , opp->pos().y-1);
                Body_GoToPoint2010(point,0.1,rcsc::ServerParam::i().maxDashPower()).execute(agent);
                agent->setNeckAction ( new Neck_TurnToLowConfTeammate );
                return true ;
            }

            if (opp->pos().x > wm.ball().pos().x )
            {
                Vector2D point = Vector2D(opp->pos().x-1 , opp->pos().y-1);
                Body_GoToPoint2010(point,0.1,rcsc::ServerParam::i().maxDashPower()).execute(agent);
                agent->setNeckAction ( new Neck_TurnToLowConfTeammate );
                return true;
            }

        }
        if (opp->pos().y < wm.ball().pos().y)
        {
            if (opp->pos().x < wm.ball().pos().x)
            {
                Vector2D point = Vector2D(opp->pos().x+1 , opp->pos().y+1);
                Body_GoToPoint2010(point,0.1,rcsc::ServerParam::i().maxDashPower()).execute(agent);
                agent->setNeckAction ( new Neck_TurnToLowConfTeammate );
                return true;
            }
            if (opp->pos().x > wm.ball().pos().x)
            {
                Vector2D point = Vector2D(opp->pos().x-1 , opp->pos().y+1);
                Body_GoToPoint2010(point,0.1,rcsc::ServerParam::i().maxDashPower()).execute(agent);
                agent->setNeckAction ( new Neck_TurnToLowConfTeammate );
                return true;
            }
        }
        else
        {
            if (opp->pos().y > wm.ball().pos().y)
            {
                Vector2D point = Vector2D(opp->pos().x , opp->pos().y-1);
                Body_GoToPoint2010(point,0.1,rcsc::ServerParam::i().maxDashPower()).execute(agent);
                agent->setNeckAction ( new Neck_TurnToLowConfTeammate );
                return true;
            }
            if (opp->pos().y < wm.ball().pos().y)
            {
                Vector2D point = Vector2D(opp->pos().x , opp->pos().y+1);
                Body_GoToPoint2010(point,0.1,rcsc::ServerParam::i().maxDashPower()).execute(agent);
                agent->setNeckAction ( new Neck_TurnToLowConfTeammate );
                return true;
            }
        }
    }


    return false ;
}
