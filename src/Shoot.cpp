// #ifdef HAVE_CONFIG_H
// #include <config.h>
// #endif
// 
// #include "Dribble.h"
// 
// #include <rcsc/action/body_advance_ball.h>
// #include <rcsc/action/body_dribble.h>
// #include <rcsc/action/body_hold_ball.h>
// #include <rcsc/action/body_pass.h>
// #include <rcsc/action/neck_scan_field.h>
// #include <rcsc/action/neck_turn_to_low_conf_teammate.h>
// 
// #include <rcsc/player/player_agent.h>
// #include <rcsc/player/debug_client.h>
// 
// #include <rcsc/common/logger.h>
// #include <rcsc/common/server_param.h>
// #include <rcsc/geom/sector_2d.h>
// 
// using namespace rcsc;
// /*-------------------------------------------------------------------*/
// /*!
// 
//  */
// bool
// Dribble::execute( rcsc::PlayerAgent * agent )
// {
// 	const rcsc::WorldModel & wm = agent->world();
// 	Vector2D pos_agent=wm.self().pos();
// 	Vector2D drib_target = get_target_point( agent );
//             const int max_dash_step
//                 = wm.self().playerType()
//                 .cyclesToReachDistance( wm.self().pos().dist( drib_target ) );
//  if (        rcsc::Body_Dribble( drib_target,
//                                 1.0,
//                                 rcsc::ServerParam::i().maxDashPower(),
//                                 std::min( 5, max_dash_step )
//                                 ).execute( agent ))
//  {
//     std::cout<<"dribble -> "<< wm.time().cycle() <<std::endl;
//    agent->setNeckAction(new Neck_ScanField());
//    return true;}
//  return false;
// 
// 	
// 
// 
// }
// 
// DRIBBLE_REGION
// Dribble::get_dribble_region(PlayerAgent * agent)
// {
// 	const rcsc::WorldModel & wm = agent->world();
// 	Vector2D pos_agent=wm.self().pos();
// 	if(pos_agent.x < 52.5 and pos_agent.x >36.5 and pos_agent.y < 17 and pos_agent.y >-17)
// 
// 		return Region_11;
// 
// 	if(pos_agent.x < 52.5 and pos_agent.x >36.5 and pos_agent.y < -17 and pos_agent.y >-34)
// 
// 		return Region_10;
// 
// 	if(pos_agent.x < 52.5 and pos_agent.x >36.5 and pos_agent.y < 34 and pos_agent.y >17)
// 
// 		return Region_13;
// 
// 	if(pos_agent.x < 36.5 and pos_agent.x >0 and pos_agent.y < -15 and pos_agent.y >-34)
// 
// 		return Region_9;
// 
// 	if(pos_agent.x < 36.5 and pos_agent.x >0 and pos_agent.y < 34 and pos_agent.y > 15)
// 
// 		return Region_12;
// 
// 	if(pos_agent.x < 36.5 and pos_agent.x > 0 and pos_agent.y < 15 and pos_agent.y >-15)
// 
// 		return Region_1;
// 	else return Region_illegal;
// 
// }
// 
// rcsc::Vector2D
// Dribble::get_target_point(PlayerAgent * agent)
// {
// 	const WorldModel & wm = agent->world();
// 	Vector2D target_point;
// 	Vector2D pos_agent=wm.self().pos();
// 	if(get_dribble_region( agent) == Region_11)
// 	{
// 		Vector2D target_point(52.5 , 0.0);
// 		return target_point;
// 	}
// 	if(get_dribble_region( agent) == Region_10)
// 	{
// 		Vector2D target_point(49.0 , -10.0);
// 		return target_point;
// 	}	
// 	if(get_dribble_region( agent) == Region_13)
// 	{
// 		Vector2D target_point(49.0 , 10.0);
// 		return target_point;
// 	}
// 	if(get_dribble_region( agent) == Region_9)
// 	{
// 		Vector2D target_point(45.5 , -25.0);
// 		return target_point;
// 	}
// 	if(get_dribble_region( agent) == Region_12)
// 	{
// 		Vector2D target_point(45.5 , 25.0);
// 		return target_point;
// 	}
// 	if(get_dribble_region( agent) == Region_1)
// 	{
// 		Vector2D target_point((pos_agent.x+10.0),pos_agent.y);
// 		return target_point;
// 	}
// 	if(get_dribble_region( agent) == Region_illegal)
// 	{
// 		Vector2D target_point((pos_agent.x+10.0),pos_agent.y);
// 		return target_point;
// 	}
// 
// }
