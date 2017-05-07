#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "Dribble_fast.h"

#include <rcsc/action/body_advance_ball.h>
#include <rcsc/action/body_dribble.h>
#include <rcsc/action/body_hold_ball.h>
#include <rcsc/action/body_clear_ball2009.h>
#include <rcsc/action/body_intercept.h>
#include <rcsc/action/neck_scan_field.h>
#include <rcsc/action/neck_turn_to_ball.h>
#include <rcsc/action/neck_turn_to_low_conf_teammate.h>
#include <rcsc/action/body_stop_ball.h>
#include <rcsc/action/body_smart_kick.h>

#include <rcsc/geom.h>

#include <rcsc/player/player_agent.h>
#include <rcsc/player/debug_client.h>

#include <rcsc/common/logger.h>
#include <rcsc/common/server_param.h>
#include <rcsc/geom/sector_2d.h>
#include <rcsc/geom/circle_2d.h>

#define PITCH_LENGTH 105
#define PITCH_WIDTH 68


using namespace rcsc;
using namespace std;
/*-------------------------------------------------------------------*/
/*!

 */
bool
DribbleFast::execute( rcsc::PlayerAgent * agent )
{
    const rcsc::WorldModel & wm = agent->world();
    Vector2D target;
    Vector2D ball = wm.self().pos();
    double X = wm.self().pos().x;
    double Y = wm.self().pos().y;
    target.x = PITCH_LENGTH / 2 ;

    if ( X <= -40 )
    {
        if ( Y <= 34 and Y >= 30 ) target.y = 31;
        if ( Y >= 25 and Y < 30 ) target.y = 27;
        if ( Y < 25 and Y >= 20 ) target.y = 22;
        if ( Y < 20 and Y > 10 ) target.y = 15;
        if ( Y >= 5 and Y <= 10 ) target.y = 8;
        if ( Y > 0 and Y < 5 ) target.y = 3;

        if ( Y >= -34 and Y >= -30 ) target.y = -31;
        if ( Y <= -25 and Y > -30 ) target.y = -27;
        if ( Y > -25 and Y <= -20 ) target.y = -22;
        if ( Y > -20 and Y < -10 ) target.y = -15;
        if ( Y <= -5 and Y >= -10 ) target.y = -8;
        if ( Y < 0 and Y > -5 ) target.y = -3;

    }

    if ( X > -40 and X < -30 )
    {
        if ( Y <= 34 and Y >= 30 ) target.y = 31;
        if ( Y >= 25 and Y < 30 ) target.y = 27;
        if ( Y < 25 and Y >= 20 ) target.y = 22;
        if ( Y < 20 and Y > 10 ) target.y = 15;
        if ( Y >= 5 and Y <= 10 ) target.y = 8;
        if ( Y > 0 and Y < 5 ) target.y = 3;

        if ( Y >= -34 and Y <= -30 ) target.y = -31;
        if ( Y <= -25 and Y > -30 ) target.y = -27;
        if ( Y > -25 and Y <= -20 ) target.y = -22;
        if ( Y > -20 and Y > -10 ) target.y = -15;
        if ( Y <= -5 and Y >= -10 ) target.y = -8;
        if ( Y < 0 and Y > -5 ) target.y = -3;

    }

    if ( X >= -30 and X < -20 )
    {
        if ( Y <= 34 and Y >= 30 ) target.y = 31;
        if ( Y >= 25 and Y < 30 ) target.y = 27;
        if ( Y < 25 and Y >= 20 ) target.y = 22;
        if ( Y < 20 and Y > 10 ) target.y = 15;
        if ( Y >= 5 and Y <= 10 ) target.y = 8;
        if ( Y > 0 and Y < 5 ) target.y = 3;

        if ( Y >= -34 and Y <= -30 ) target.y = -31;
        if ( Y <= -25 and Y > -30 ) target.y = -27;
        if ( Y > -25 and Y <= -20 ) target.y = -22;
        if ( Y > -20 and Y < -10 ) target.y = -15;
        if ( Y <= -5 and Y >= -10 ) target.y = -8;
        if ( Y < 0 and Y > -5 ) target.y = -3;

    }

    if ( X >= -20 and X < -10 )
    {
        if ( Y <= 34 and Y >= 30 ) target.y = 31;
        if ( Y >= 25 and Y < 30 ) target.y = 27;
        if ( Y < 25 and Y >= 20 ) target.y = 22;
        if ( Y < 20 and Y > 10 ) target.y = 15;
        if ( Y >= 5 and Y <= 10 ) target.y = 8;
        if ( Y > 0 and Y < 5 ) target.y = 3;

        if ( Y >= -34 and Y <= -30 ) target.y = -31;
        if ( Y <= -25 and Y > -30 ) target.y = -27;
        if ( Y > -25 and Y <= -20 ) target.y = -22;
        if ( Y > -20 and Y < -10 ) target.y = -15;
        if ( Y <= -5 and Y >= -10 ) target.y = -8;
        if ( Y < 0 and Y < -5 ) target.y = -3;

    }

    if ( X >= -10 and X < 0 )
    {
        if ( Y >= 34 and Y <= 30 ) target.y = 31;
        if ( Y <= 25 and Y > 30 ) target.y = 27;
        if ( Y > 25 and Y <= 20 ) target.y = 22;
        if ( Y > 20 and Y < 10 ) target.y = 15;
        if ( Y <= 5 and Y >= 10 ) target.y = 8;
        if ( Y < 0 and Y > 5 ) target.y = 3;

        if ( Y >= -34 and Y <= -30 ) target.y = -31;
        if ( Y <= -25 and Y > -30 ) target.y = -27;
        if ( Y > -25 and Y <= -20 ) target.y = -22;
        if ( Y > -20 and Y < -10 ) target.y = -15;
        if ( Y <= -5 and Y >= -10 ) target.y = -8;
        if ( Y < 0 and Y > -5 ) target.y = -3;

    }

    if ( X >= 0 and X < 10 )
    {
        if ( Y <= 34 and Y >= 30 ) target.y = 31;
        if ( Y >= 25 and Y < 30 ) target.y = 26;
        if ( Y < 25 and Y >= 20 ) target.y = 21;
        if ( Y < 20 and Y > 10 ) target.y = 15;
        if ( Y >= 5 and Y <= 10 ) target.y = 8;
        if ( Y > 0 and Y < 5 ) target.y = 3;

        if ( Y >= -34 and Y <= -30 ) target.y = -31;
        if ( Y <= -25 and Y > -30 ) target.y = -26;
        if ( Y > -25 and Y <= -20 ) target.y = -21;
        if ( Y > -20 and Y < -10 ) target.y = -15;
        if ( Y <= -5 and Y >= -10 ) target.y = -8;
        if ( Y < 0 and Y > -5 ) target.y = -3;

    }

    if ( X >= 10 and X < 20 )
    {
        if ( Y <= 34 and Y >= 30 ) target.y = 30;
        if ( Y >= 25 and Y < 30 ) target.y = 26;
        if ( Y < 25 and Y >= 20 ) target.y = 21;
        if ( Y < 20 and Y > 10 ) target.y = 15;
        if ( Y >= 5 and Y <= 10 ) target.y = 8;
        if ( Y > 0 and Y < 5 ) target.y = 3;

        if ( Y >= -34 and Y <= -30 ) target.y = -30;
        if ( Y <= -25 and Y > -30 ) target.y = -26;
        if ( Y > -25 and Y <= -20 ) target.y = -21;
        if ( Y > -20 and Y < -10 ) target.y = -15;
        if ( Y <= -5 and Y >= -10 ) target.y = -8;
        if ( Y < 0 and Y > -5 ) target.y = -3;

    }

    if ( X >= 20 and X < 30 )
    {
        if ( Y <= 34 and Y >= 30 ) target.y = 30;
        if ( Y >= 25 and Y < 30 ) target.y = 27;
        if ( Y < 25 and Y >= 20 ) target.y = 23;
        if ( Y < 20 and Y > 10 ) target.y = 15;
        if ( Y >= 5 and Y <= 10 ) target.y = 7;
        if ( Y > 0 and Y < 5 ) target.y = 2;

        if ( Y >= -34 and Y <= -30 ) target.y = -30;
        if ( Y <= -25 and Y > -30 ) target.y = -27;
        if ( Y > -25 and Y <= -20 ) target.y = -23;
        if ( Y > -20 and Y < -10 ) target.y = -15;
        if ( Y <= -5 and Y >= -10 ) target.y = -7;
        if ( Y < 0 and Y > -5 ) target.y = -2;
    }

    if ( X >= 30 and X < 36 )
    {
        if ( Y <= 34 and Y >= 30 ) target.y = 32;
        if ( Y >= 25 and Y < 30 ) target.y = 27;
        if ( Y < 25 and Y >= 20 ) target.y = 22;
        if ( Y < 20 and Y > 10 ) target.y = 15;
        if ( Y >= 5 and Y <= 10 ) target.y = 8;
        if ( Y > 0 and Y < 5 ) target.y = 3;

        if ( Y >= -34 and Y <= -30 ) target.y = -32;
        if ( Y <= -25 and Y > -30 ) target.y = -27;
        if ( Y > -25 and Y <= -20 ) target.y = -22;
        if ( Y > -20 and Y < -10 ) target.y = -15;
        if ( Y <= -5 and Y >= -10 ) target.y = -8;
        if ( Y < 0 and Y > -5 ) target.y = -3;
    }
#if 1
    if ( X >= 36 and X < 40 )
    {
        if ( Y <= 34 and Y >= 30 ) target.y = 31;
        if ( Y >= 25 and Y < 30 ) target.y = 26;
        if ( Y < 25 and Y >= 20 ) target.y = 21;
        if ( Y < 20 and Y > 10 ) target.y = 15;
        if ( Y >= 5 and Y <= 10 ) target.y = 8;
        if ( Y > 0 and Y < 5 ) target.y = 3;

        if ( Y >= -34 and Y <= -30 ) target.y = -31;
        if ( Y <= -25 and Y > -30 ) target.y = -26;
        if ( Y > -25 and Y <= -20 ) target.y = -21;
        if ( Y > -20 and Y < -10 ) target.y = -15;
        if ( Y <= -5 and Y >= -10 ) target.y = -8;
        if ( Y < 0 and Y > -5 ) target.y = -3;

    }
//         if ( X >= 40 ) target.y = 0;
#endif
#if 1
    if ( X > 40 )
    {
        if (  fabs ( Y ) >= 10 and fabs ( Y ) <= 20 ) target.y = .5;
        if (  fabs ( Y ) >  20 and fabs ( Y ) <= 30 )
        {
            if ( Y < 0 ) target.y = -10;
            if ( Y > 0 ) target.y =  10;
        }
        if (  fabs ( Y ) > 30 )
        {
            if ( Y > 30 ) target.y = 5 ;
            if ( Y < 30 ) target.y = -5;
        }
        else target.y = 0;
    }
#endif
#if 0
    if ( X > 44 and Y <= 34 and Y >= 30 ) target.y = 5;
    if ( Y >= 25 and Y < 30 ) target.y = 23;
    if ( Y < 25 and Y >= 20 ) target.y = 15;
    if ( Y < 20 and Y > 10 ) target.y = 10;
    if ( Y >= 5 and Y <= 10 ) target.y = 8;
    if ( Y > 0 and Y < 5 ) target.y = 3;

    if ( X > 44 and Y >= -34 and Y <= -30 ) target.y = -5;
    if ( Y <= -25 and Y > -30 ) target.y = -23;
    if ( Y > -25 and Y <= -20 ) target.y = -15;
    if ( Y > -20 and Y < -10 ) target.y = -10;
    if ( Y <= -5 and Y >= -10 ) target.y = -8;
    if ( Y < 0 and Y > -5 ) target.y = -3;
#endif
#if 0
    double w_dist = PITCH_WIDTH / 10;

    vector<Vector2D> points_ii;
    vector<Vector2D> points_jj;
    vector<Vector2D> points_hh;

    Vector2D point[];
    for ( int ii = 0; ii < 11; ii ++ )
    {

        point[ii] = ( 36.0, w_dist * ii );
        points_ii.push_back(point[ii]);

    }

    for ( int jj = 10; jj < 21; jj ++ )
    {

        point[jj] = ( 16.0, w_dist * jj );
        points_ii.push_back(point[jj]);
    }

    for ( int hh = 10; hh < 21; h ++ )
    {

        point[hh] = ( 16.0, w_dist * hh );
        points_ii.push_back(point[hh]);
    }

    Vector2D point1 ( 36.0, 0 );
    Vector2D point2 ( 36.0, w_dist );
    Vector2D point3 ( 36.0, w_dist * 2 );
    Vector2D point4 ( 36.0, w_dist * 3 );
    Vector2D point5 ( 36.0, w_dist * 5 );
    Vector2D point6 ( 36.0, 0 );
    Vector2D point7 ( 36.0, - w_dist );
    Vector2D point8 ( 36.0, - w_dist * 2 );
    Vector2D point9 ( 36.0, - w_dist * 3 );
    Vector2D point10 ( 36.0,- w_dist * 5 );

    Vector2D point11 ( 16.0, 0 );
    Vector2D point12 ( 16.0, w_dist );
    Vector2D point13 ( 16.0, w_dist * 2 );
    Vector2D point14 ( 16.0, w_dist * 3 );
    Vector2D point15 ( 16.0, w_dist * 5 );
    Vector2D point16 ( 16.0, 0 );
    Vector2D point17 ( 16.0, - w_dist );
    Vector2D point18 ( 16.0, - w_dist * 2 );
    Vector2D point19 ( 16.0, - w_dist * 3 );
    Vector2D point20 ( 16.0,- w_dist * 5 );

    Vector2D point21 ( 0.0, 0 );
    Vector2D point22 ( 0.0, w_dist );
    Vector2D point23 ( 0.0, w_dist * 2 );
    Vector2D point24 ( 0.0, w_dist * 3 );
    Vector2D point25 ( 0.0, w_dist * 5 );
    Vector2D point26 ( 0.0, 0 );
    Vector2D point27 ( 0.0, - w_dist );
    Vector2D point28 ( 0.0, - w_dist * 2 );
    Vector2D point29 ( 0.0, - w_dist * 3 );
    Vector2D point30 ( 0.0,- w_dist * 5 );

    Vector2D point31 ( -10.0, 0 );
    Vector2D point32 ( -10.0, w_dist );
    Vector2D point33 ( -10.0, w_dist * 2 );
    Vector2D point34 ( -10.0, w_dist * 3 );
    Vector2D point35 ( -10.0, w_dist * 5 );
    Vector2D point36 ( -10.0, 0 );
    Vector2D point37 ( -10.0, - w_dist );
    Vector2D point38 ( -10.0, - w_dist * 2 );
    Vector2D point39 ( -10.0, - w_dist * 3 );
    Vector2D point40 ( -10.0,- w_dist * 5 );
#endif
    Vector2D pos_agent = wm.self().pos();

    /*    vector<Vector2D> points;

        Polygon2D poly (points);*/


//     double ball_speed = rcsc::ServerParam::i().maxDashPower();
    double dist = wm.self().pos().dist( target );

    rcsc::Vector2D one_step_vel
    = rcsc::KickTable::calc_max_velocity( (wm.self().pos().abs() - target ).th(),
                                          agent->world().self().kickRate(),
                                          agent->world().ball().vel() );

    double one_step_speed = one_step_vel.r();
    float ball_speed = 1.2 ;
#if 0
    if ( wm.self().pos().x  > 31 and wm.self().pos().absY() > 17 ) ball_speed = .8;
    if ( wm.self().pos().x  > 36 and wm.self().pos().absY() < 17 ) ball_speed = .9;
#endif

    double radius = 3;
    if ( wm.self().pos().x >= 36 and wm.self().pos().absY() > 17 ) radius = 2;
    Circle2D circle ( wm.self().pos(), radius );
    Line2D line_to_me ( wm.self().pos(), target );
    Vector2D inter_1,inter_2;
    int intersect = circle.intersection(line_to_me,&inter_1,&inter_2);

    if ( X <= 39 )
    {
        if ( inter_1.x > wm.self().pos().x and inter_2.x < wm.self().pos().x ) target = inter_1;
        if ( inter_1.x < wm.self().pos().x and inter_2.x > wm.self().pos().x ) target = inter_2;
    }

    Line2D line ( pos_agent, Vector2D ( target.x * 2, target.y * 2) );
    const rcsc::PlayerPtrCont & opps = wm.opponentsFromSelf();
    const rcsc::PlayerObject * nearest_opp
    = ( opps.empty()
        ? static_cast< rcsc::PlayerObject * >( 0 )
        : opps.front() );

    bool origin = false;
    Circle2D opp_cir ( pos_agent, 3 );
    Vector2D inter1_line,inter2_line;
    vector<Vector2D> opp_vec;
    
    const rcsc::PlayerPtrCont::const_iterator opps_end = opps.end();
    for ( rcsc::PlayerPtrCont::const_iterator it = opps.begin();
            it != opps_end;
            ++it )
    {
      	opp_vec.push_back( (*it)->pos() );
	if ( opp_vec.size() < 1 ) origin = true;
	if ( opp_vec.size() >= 1)
	{
	  opp_cir.assign( (*it)->pos(),3 );
	  int line_inter_num = opp_cir.intersection(line,&inter1_line,&inter2_line);
	  double ddist = line.dist((*it)->pos());
	  if ( ddist > 3 )
	  {
	    if ( line_inter_num < 2 ) origin = true;;
	  }
	  else if ( line_inter_num != 0 ) origin = true;
	}
    }


    bool safe = false;
    bool safe_short = false;

    Segment2D me_to_h ( wm.self().pos(), target + Vector2D ( 3.0, 0.0));
    Triangle2D check (wm.self().pos(), target + Vector2D ( 3.0, 4.0), target + Vector2D ( 3.0, -4.0) );
    Sector2D check_seg ( wm.self().pos() - Vector2D ( 1.0, 0 ), 1, 6,
                         ( wm.self().pos() - target ).th() - 20,( wm.self().pos() - target ).th() + 20 );
    Sector2D sector ( pos_agent - Vector2D ( 1,0 ) ,2 , 8, wm.self().body() - 20, wm.self().body() + 20);

    // long dribble
    rcsc::Vector2D vertex_1,vertex_2,vertex_3;
    vertex_3 = pos_agent + rcsc::Vector2D (-1.0, 0.0);
    vertex_1 = vertex_3  + rcsc::Vector2D (5.7, -8.0);
    vertex_2 = vertex_3  + rcsc::Vector2D (5.7,  8.0);
    int safe_num_long = wm.countOpponentsIn(rcsc::Triangle2D(vertex_3,vertex_1,vertex_2),20,true) +
                        wm.countOpponentsIn(rcsc::Rect2D(vertex_1,vertex_2+rcsc::Vector2D(10.0,0.0)),20,true);
    if ( safe_num_long == 0 )
    {
        safe = true;
        if ( safe )
        {
            ball_speed = 1.0;
            if ( X > 36 ) ball_speed = 1.1;
        }

    }

    double ball_speed_short;
    rcsc::Vector2D vertex_1s,vertex_2s,vertex_3s;
    vertex_3s = pos_agent + rcsc::Vector2D (-1.0, 0.0);
    vertex_1s = vertex_3s  + rcsc::Vector2D (3.1, -4.3);
    vertex_2s = vertex_3s  + rcsc::Vector2D (3.1,  4.3);
    int safe_num_short = wm.countOpponentsIn(rcsc::Triangle2D(vertex_3,vertex_1,vertex_2),20,true) +
                         wm.countOpponentsIn(rcsc::Rect2D(vertex_1,vertex_2+rcsc::Vector2D(10.0,0.0)),20,true);
    if ( safe_num_short == 0 )
    {
        safe_short = true;
        if ( safe_short )
        {
            ball_speed_short = 0.90;
        }
    }


#if 0
    double dist_to_point;
    const PlayerObject * near_opp;
    near_opp = wm.getOpponentNearestTo(pos_agent,10,&dist_to_point);
    Vector2D opp_near_pred = near_opp->inertiaPoint( 1 );
    Circle2D cir ( opp_near_pred, 2 );

    if ( X < 36 and  wm.existOpponentIn<Triangle2D>(check, 10, false) == 0 and wm.existOpponentIn<Sector2D>(check_seg, 10, false) == 0 )
        safe = true;

    if ( X >= 36 and wm.existOpponentIn<Sector2D>(sector,10,false) == 0 )
    {
        if (  wm.existOpponentIn<Triangle2D>(check, 10, false) == 0 and  wm.existOpponentIn<Circle2D>(cir, 10, false) == 0 and wm.existOpponentIn<Sector2D>(check_seg, 10, false) == 0 )
            safe = true;
    }
    cout<<" SAFE : "<<safe<<endl;

#endif

//     if ( origin ){
    
    if ( one_step_speed > ball_speed )
    {
        if ( safe )
        {
            if ( Body_SmartKick( target, ball_speed,ball_speed - 0.30 ,1 ).execute(agent))
            {
                agent->setNeckAction(new rcsc::Neck_TurnToBall() );
                return true;
            }
        }
    }
    if ( one_step_speed > ball_speed_short )
    {
        if ( safe_short )
        {
            if ( Body_SmartKick( target, ball_speed_short,ball_speed_short - 0.30 ,1 ).execute(agent))
            {
                agent->setNeckAction(new rcsc::Neck_TurnToBall() );
                return true;
            }
        }
    }
//     }
    return false;

#if 0
    if ( Body_Dribble(target, 3,ball_speed,1,true ).execute(agent))
    {
        agent->setNeckAction(new rcsc::Neck_TurnToBall() );
    }
    return true;
#endif

}
