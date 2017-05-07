#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "Clear.h"

#include <rcsc/action/body_advance_ball.h>
#include <rcsc/action/body_dribble.h>
#include <rcsc/action/body_hold_ball.h>
#include <rcsc/action/body_clear_ball2009.h>
#include <rcsc/action/body_pass.h>
#include <rcsc/action/neck_scan_field.h>
#include <rcsc/action/neck_turn_to_low_conf_teammate.h>

#include <rcsc/player/player_agent.h>
#include <rcsc/player/debug_client.h>

#include <rcsc/common/logger.h>
#include <rcsc/common/server_param.h>
#include <rcsc/geom/sector_2d.h>
#include <rcsc/geom/circle_2d.h>
using namespace rcsc;
/*-------------------------------------------------------------------*/
/*!

 */
bool
Clear::execute( rcsc::PlayerAgent * agent )
{
	const rcsc::WorldModel & wm = agent->world();
		const rcsc::Circle2D c( wm.self().pos() , 5 );
	if(wm.existOpponentIn( c , 3, true ))
	{
		    Body_ClearBall2009();
	}	
}