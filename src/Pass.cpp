#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

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
#include <rcsc/geom/rect_2d.h>
#include "Pass_through.h"
using namespace rcsc;
using namespace std;
/*-------------------------------------------------------------------*/
/*!

 */



bool
Pass::execute ( rcsc::PlayerAgent * agent )
{

    const rcsc::WorldModel & wm = agent->world();

    const rcsc::PlayerPtrCont & opps = wm.opponentsFromSelf();
    const rcsc::PlayerObject * nearest_opp
    = ( opps.empty()
        ? static_cast< rcsc::PlayerObject * > ( 0 )
        : opps.front() );
    const double nearest_opp_dist = ( nearest_opp
                                      ? nearest_opp->distFromSelf()
                                      : 1000.0 );
    const rcsc::Vector2D nearest_opp_pos = ( nearest_opp
                                           ? nearest_opp->pos()
                                           : rcsc::Vector2D ( -1000.0, 0.0 ) );
/// pass_Test
    std::vector< rcsc::PlayerObject* > teammates;
    rcsc::PlayerPtrCont::const_iterator end = wm.teammatesFromSelf().end();
    for ( rcsc::PlayerPtrCont::const_iterator it = wm.teammatesFromSelf().begin();
            it != end;
            ++it )
    {
        if ( ( *it )->posCount() < 3
                && ( *it )->unum() > 1
                && ( *it )->pos().x < wm.offsideLineX() )
        {
            teammates.push_back ( ( *it ) );
        }
    }

    if ( teammates.empty() )
    {
        return false;
    }
    rcsc::PlayerObject* tmp_po;

    for ( unsigned int i = 0; i < teammates.size() - 1; i++ )
    {
        for ( unsigned int j = i + 1 ; j < teammates.size() ; j++ )
        {
            if ( teammates[i]->pos().x < teammates[j]->pos().x )
            {
                tmp_po = teammates[i];
                teammates[i] = teammates[j];
                teammates[j] = tmp_po;
            }
        }
    }

    for ( unsigned int i = 0; i < teammates.size(); i++ )
    {
// /*
//         if ( pass_test_leading ( agent, teammates.at ( i ) ) )
//         {
//             cout << " leading_Pass    " <<" cycle  ->   "<< wm.time().cycle() << /*agent->world().time() <<*/ "Unum ->   "  << agent->world().self().unum() << endl<< endl;
//             return true;
//         }

	if ( PassThrough().execute( agent, teammates.at ( i )))
        {
	   cout << " through_Pass    " <<" cycle  ->   "<< wm.time().cycle() << agent->world().time() <<"Unum ->   "  << agent->world().self().unum() << endl << endl;
	    return true;
        }


        if ( pass_test ( agent, teammates.at ( i ) ) )
       {
            cout << " Pass   " <<" cycle  ->   "<< wm.time().cycle() << /*agent->world().time() <<*/ "Unum ->   "  << agent->world().self().unum() << endl<< endl;
           return true;
        }
#if 0
	if(pass_cross( agent , teammates.at ( i ) )  )
        {
            cout << " Pass cross  " <<" cycle  ->   "<< wm.time().cycle() << /*agent->world().time() <<*/ "Unum ->   "  << agent->world().self().unum() << endl<< endl;
            return true;
        }
#endif
    }


/// Pass_wieght

    rcsc::Vector2D target,pred_pos,pos_tmm;
    double weight=0.0;
    int mode = 0;
    double first_speed = 100;
    bool is_def= false;
    bool is_mid= false;
    bool is_off = false;

    if ( wm.self().unum() < 6 ) is_def = true;
    if ( wm.self().unum() > 5 and wm.self().unum() < 9 ) is_mid = true;
    if ( wm.self().unum() > 8 ) is_off = true;
    if ( is_def == true ) mode = 1;
    if ( is_mid == true ) mode = 2;
    if ( is_off == true ) mode = 3;


    const PlayerPtrCont::const_iterator
    t_end = wm.teammatesFromSelf().end();
    for ( PlayerPtrCont::const_iterator
            it = wm.teammatesFromSelf().begin();
            it != t_end;
            ++it )
    {



        target = ( *it )->pos();

        if ( (*it)->distFromSelf() < 3 )
        {
            return false;
        }
        if ( ( *it )->posCount() > 3 )
        {
            return false;
        }
        if ( wm.offsideLineX() < target.x )
        {
            return false;
        }
        double checker = 5;
        if ( wm.self().pos().x < 10 and wm.self().pos().x > -10 )
        {
            checker = 5;
        }
        if ( wm.self().pos().x <= - 20 )
        {
            checker = 1;
        }
        if ( Strategy::get_ball_area(wm.self().pos()) == Strategy::BA_Cross )
        {
            checker = 25;
        }
        if (wm.self().pos().x - checker  > target.x )
        {
            return false;
        }
/// rect
        const rcsc::Vector2D self_rect (wm.self().pos().x , wm.self().pos().y + 3 ) ;
        const rcsc::Vector2D target_rect (target.x , target.y - 3 );
        Rect2D rect ( self_rect ,  target_rect);
        if ( wm.existOpponentIn ( rect,3, false ) )
        {
            return false ;
        }
        if ( wm.self().unum() < 6 and (*it)->unum() < 6 )
        {
            return false;
        }


/// mode 1
        if ( mode == 1)

        {
//		cout<< "mode 1  ->  "<<< " Unum ->   "  << agent->world().self().unum() << endl;
            weight = get_weight_with_dist ( agent,target )+ get_weight_with_X ( agent,target ) + get_weight_with_dist_opp (agent,target);
            if ( weight >= 7 )
            {
                if ( rcsc::Body_SmartKick(target,getBestSpeed(agent,target),
                                          getBestSpeed(agent,target)-0.0000001 ,2 ).execute( agent ) )
                {
                    rcsc::KickTable::Sequence seq;
                    rcsc::KickTable::instance().simulate ( wm,
                                                           target,
                                                           first_speed,
                                                           first_speed * 0.94,
                                                           3,seq );

                    agent->setNeckAction ( new Neck_TurnToPoint ( target ) );
                }
            }
        }
        weight = get_weight_with_dist ( agent,target ) + get_weight_with_sector ( agent,target ) + get_weight_with_X ( agent,target ) + get_weight_with_dist_opp ( agent,target );

/// mode 2

        if ( mode == 2)
        {
//		cout<< "mode 2  ->  "<<< " Unum ->   "  << agent->world().self().unum() << endl;

            if ( weight >= 15 )
            {
                if ( rcsc::Body_SmartKick(target,getBestSpeed(agent, target),
                                          getBestSpeed(agent,target) -0.00001 ,2 ).execute( agent ) )
                {
                    rcsc::KickTable::Sequence seq;
                    rcsc::KickTable::instance().simulate ( wm,
                                                           target,
                                                           first_speed,
                                                           first_speed * 0.94,
                                                           3,seq );

                    agent->setNeckAction ( new Neck_TurnToPoint ( target ) );
                }
            }
        }

/// mode 3

        if ( mode == 3 )
        {
//		cout<< "mode 3  ->  "<<< " Unum ->   "  << agent->world().self().unum() << endl;

            if ( weight >= 13 )
            {
                if ( rcsc::Body_SmartKick(target,getBestSpeed(agent ,target),
                                          getBestSpeed(agent,target) -0.00001 ,2 ).execute( agent ) )
                {
                    rcsc::KickTable::Sequence seq;
                    rcsc::KickTable::instance().simulate ( wm,
                                                           target,
                                                           first_speed,
                                                           first_speed * 0.94,
                                                           3,seq );

                    agent->setNeckAction ( new Neck_TurnToPoint ( target ) );
                }
            }
        }
        return true;
    }
}


/// region


PASS_REGION
Pass::get_pass_region ( rcsc::PlayerAgent * agent )
{
    const rcsc::WorldModel & wm = agent->world();
    Vector2D pos_agent=wm.self().pos();
    if (pos_agent.x < 52.5 and pos_agent.x >36.5 and pos_agent.y < 17 and pos_agent.y >-17)
    {
        return Region_11_PASS;
    }
    if (pos_agent.x < 52.5 and pos_agent.x >36.5 and pos_agent.y < -17 and pos_agent.y >-34)
    {
        return Region_10_PASS;
    }
    if (pos_agent.x < 52.5 and pos_agent.x >36.5 and pos_agent.y < 34 and pos_agent.y >17)
    {
        return Region_13_PASS;
    }
    if (pos_agent.x < 36.5 and pos_agent.x >0 and pos_agent.y < -15 and pos_agent.y >-34)
    {
        return Region_9_PASS;
    }
    if (pos_agent.x < 36.5 and pos_agent.x >0 and pos_agent.y < 34 and pos_agent.y > 15)
    {
        return Region_12_PASS;
    }
    if ( pos_agent.x < 0 and pos_agent.y < 35 and pos_agent.y >-35)
    {
        return Region_1_PASS;
    }
    else
    {
        return Region_illegal_PASS;
    }
}

/// sector
double
Pass::get_weight_with_sector ( rcsc::PlayerAgent * agent, rcsc::Vector2D target )
{
    double value;
    const rcsc::WorldModel & wm = agent->world();

    std::vector< rcsc::Vector2D > opponents;
    rcsc::Sector2D sector ( wm.self().pos(),1,4, (wm.self().pos() - target).th() + 20, (wm.self().pos() -target).th() - 20 );

    const PlayerPtrCont::const_iterator
    o_end = wm.opponentsFromSelf().end();
    for ( PlayerPtrCont::const_iterator
            it = wm.opponentsFromSelf().begin();
            it != o_end;
            ++it )
    {

        if (wm.existOpponentIn ( sector,10, false ) )
        {

            value = 5.0;
            opponents.push_back((*it)->pos());

        }
        else
        {
            value = 10.0;
        }
    }
    if ( opponents.size() < 1 ) value = 10.0;

//		cout<<"value  sector_pass  ->    "<<  value << endl ;
    return value;
}

/// dist agent from target
double
Pass::get_weight_with_dist ( rcsc::PlayerAgent * agent, rcsc::Vector2D target )
{
    const rcsc::WorldModel & wm = agent->world();
    double value;
    int target_dist_to_me;
    target_dist_to_me = wm.self().pos().dist ( target );
    if ( get_pass_region ( agent ) == Region_1_PASS )
    {
        if ( target_dist_to_me <= 5 )

            value = 3.0;

        if ( target_dist_to_me > 5  and target_dist_to_me >= 10 )

            value = 4.0;

        if ( target_dist_to_me > 10 and target_dist_to_me < 15 )

            value = 7.0;

        if ( target_dist_to_me >= 15 and target_dist_to_me < 20 )

            value = 8.0;

        if ( target_dist_to_me >= 20 and target_dist_to_me < 25 )

            value = 9.0;

        else
            value = 2.0;

    }
    else
    {
        if ( target_dist_to_me <= 5 )

            value = 5.0;

        if ( target_dist_to_me > 5  and target_dist_to_me >= 10 )

            value = 6.0;

        if ( target_dist_to_me > 10 and target_dist_to_me < 15 )

            value = 7.0;

        if ( target_dist_to_me >= 15 and target_dist_to_me < 20 )

            value = 8.0;

        if ( target_dist_to_me >= 20 and target_dist_to_me < 25 )

            value = 9.0;

        else
            value = 2.0;
    }
//	cout<<"value dist agent from target_pass ->    " << value << endl ;

    return value;
}

/// is forward
double
Pass::get_weight_with_X ( rcsc::PlayerAgent * agent, rcsc::Vector2D target )
{
    const rcsc::WorldModel & wm = agent->world();
    const PlayerPtrCont::const_iterator
    t_end = wm.opponentsFromSelf().end();
    double value;
    Vector2D player_Pos = target ;
    Vector2D pos_agent=wm.self().pos();

    if (get_pass_region( agent) == Region_1_PASS)
    {
        if (player_Pos.x > pos_agent.x)
        {
            value=10.0;
        }
        else
        {
            value=0.0;
        }
    }
    else
    {
        if (player_Pos.x > pos_agent.x)
        {
            value=8.0;
        }
        else
        {
            value=4.0;
        }
    }
//	cout<< "value is forward_pass  ->     " << value << endl ;
    return value;
}

/// dist opp

double
Pass::get_weight_with_dist_opp ( rcsc::PlayerAgent * agent, rcsc::Vector2D target )
{
    int value;
    const rcsc::WorldModel & wm = agent->world();
    double target_dist_to_opp;

    const PlayerPtrCont::const_iterator
    t_end = wm.opponentsFromSelf().end();
    int unum;
    Vector2D origin;
    Circle2D C_1 ( origin, 30 );
    if ( wm.existOpponentIn ( C_1, 1, false ) )
    {
        for ( PlayerPtrCont::const_iterator
                it = wm.opponentsFromSelf().begin();
                it != t_end;
                ++it )
        {
            target_dist_to_opp = target.dist ( ( *it )->pos() );
            unum = ( *it )->unum();
            if ( target_dist_to_opp > 35 )
                value= 7.0;
            if ( target_dist_to_opp > 25 and target_dist_to_opp <= 35 )
                value = 6.0;
            if ( target_dist_to_opp > 15 and target_dist_to_opp <= 25 )
                value = 5.0;
            if ( target_dist_to_opp > 10 and target_dist_to_opp <= 15 )
                value = 4.0;
            if ( target_dist_to_opp > 5 and target_dist_to_opp <= 10 )
                value = 3.0;
            else
                value = 0.0;
            cout<<"value distopp_pass->    "<< value << endl ;
            return value;

        }
    }
    else return 10.0;

}
/// get best speed
double
Pass::getBestSpeed( rcsc::PlayerAgent * agent,rcsc::Vector2D target )
{
    int target_dist_to_me;
    const rcsc::WorldModel & wm = agent->world();
    target_dist_to_me = wm.self().pos().dist ( target );
    double speed;

    if (target_dist_to_me < 10.0 )
    {
        speed = 1.3;
    }
    if (target_dist_to_me >= 10.0 and target_dist_to_me < 15.0 )
    {
        speed =1.6;
    }
    if (target_dist_to_me >= 15.0 and target_dist_to_me < 20.0 )
    {
        speed =2.1;
    }
    if (target_dist_to_me >= 20.0  and  target_dist_to_me < 30.0)
    {
        speed =2.6;
    }
    if (target_dist_to_me >= 30.0)
    {
	speed= 3.0;
    }
//    cout <<" speed _getBestSpeed " << speed <<endl;
    return speed  ;
}

double
Pass::getBestSpeed_test_pass( rcsc::PlayerAgent * agent,rcsc::Vector2D target )
{
    int target_dist_to_me;
    const rcsc::WorldModel & wm = agent->world();
    target_dist_to_me = wm.self().pos().dist ( target );
    double speed;

    if (target_dist_to_me < 10.0 )
    {
        speed = 1.5;
    }
    if (target_dist_to_me >= 10.0 and target_dist_to_me < 20.0 )
    {
        speed =2.0;
    }
    if (target_dist_to_me >= 20.0 and target_dist_to_me < 40.0 )
    {
        speed =2.5;
    }
    if (target_dist_to_me >= 40.0 )
    {
        speed =3.0;
    }
//    cout <<" speed _getBestSpeed_leading_through_pass " << speed <<endl;
    return speed  ;
}




bool
Pass::pass_test ( rcsc::PlayerAgent * agent, rcsc::PlayerObject * teammate )
{
    const rcsc::WorldModel & wm = agent->world();
    if ( teammate->pos().dist ( wm.self().pos() ) > 30 // fasele check mishavad
            || teammate->pos().x < -35 ) // tooye mohavateye khatare ma bood
    {
        return false;
    }
    int ball_cycle = getBallCycle ( agent ,teammate->pos().dist ( wm.ball().pos() ) );
    if ( ball_cycle < 3 )
    {
        return false;
    }
    double x = getDashDist ( teammate, ball_cycle - 3 );
    rcsc::Vector2D target_pos = teammate->pos();
    target_pos.x += x;
    int receiver = teammate->unum();

    rcsc::Vector2D vector = target_pos - wm.ball().pos();
    rcsc::AngleDeg angle = vector.th();
    double length = target_pos.dist ( wm.ball().pos() );
    if ( length < 1 )
    {
        length = 1;
    }
    rcsc::Sector2D sector ( wm.ball().pos(),
                            0.1,
                            length,
                            angle - 10,
                            angle + 10 );
    if ( wm.existOpponentIn ( sector, 10, true ) )
    {
        return false;
    }


    rcsc::Vector2D top_left;
    rcsc::Vector2D bottom_right;
    if ( teammate->pos().x > wm.self().pos().x )
    {
        top_left.x = wm.self().pos().x;
        bottom_right.x = teammate->pos().x + 5;
    }
    else
    {
        top_left.x = teammate->pos().x - 5;
        bottom_right.x = wm.self().pos().x;
    }
    if ( teammate->pos().y < wm.self().pos().y )
    {
        top_left.y = teammate->pos().y - 5;
        bottom_right.y = wm.self().pos().y;
    }
    else
    {
        top_left.y = wm.self().pos().y;
        bottom_right.y = teammate->pos().y + 5;
    }

    rcsc::Rect2D rect ( top_left, bottom_right );
    std::vector< rcsc::PlayerObject* > opponents;
    rcsc::PlayerPtrCont::const_iterator end = wm.opponentsFromSelf().end();
    for ( rcsc::PlayerPtrCont::const_iterator it = wm.opponentsFromSelf().begin();
            it != end;
            ++it )
    {

        if ( rect.contains ( ( *it )->pos() ) && ( *it )->pos().dist ( teammate->pos() ) < 10.0 ) // magic number
        {
            opponents.push_back ( ( *it ) );
        }
    }
    int success = false;
    double ball_speed = rcsc::calc_first_term_geom_series ( teammate->pos().dist ( wm.ball().pos() ),
                        rcsc::ServerParam::i().ballDecay(),
                        ball_cycle );


    if ( opponents.empty() )
    {
        success = true;
    }
    else
    {
        for ( unsigned int i = 0; i < opponents.size(); i++ )
        {
            rcsc::Segment2D ball_to_target ( wm.ball().pos(), target_pos );
            int opp_cycle = 1;
            rcsc::Vector2D opp_pos = rcsc::inertia_n_step_point ( opponents.at ( i )->pos(),
                                     opponents.at ( i )->vel(),
                                     3,
                                     opponents.at ( i )->playerTypePtr()->playerDecay() );
            double opp_dist = ball_to_target.dist ( opp_pos );
            double opp_speed = 0;
            double sum = 0;
            while ( sum < opp_dist )
            {
                opp_speed += opponents.at ( i )->playerTypePtr()->dashPowerRate() * 100;
                if ( opp_speed > opponents.at ( i )->playerTypePtr()->playerSpeedMax() )
                    opp_speed = opponents.at ( i )->playerTypePtr()->playerSpeedMax();
                sum += opp_speed;
                opp_speed *= opponents.at ( i )->playerTypePtr()->playerDecay();
                opp_cycle++;
            }

            double tmp_speed = ball_speed;
            int ball_cycle2 = 0;
            sum = 0;
            rcsc::Vector2D via_pos = ball_to_target.nearestPoint ( opp_pos );
            double ball_dist = via_pos.dist ( wm.ball().pos() );
            while ( sum < ball_dist )
            {
                sum += tmp_speed;
                tmp_speed *= rcsc::ServerParam::i().ballDecay();
                ball_cycle2++;
                if ( ball_cycle2 > 25 )
                {
                    return false;
                }
            }

            if ( ball_cycle2 > opp_cycle )
            {
                return false;
            }
            else
            {
                success = true;
            }
        }
    }

      if( receiver == 1 ) success =false;

    if ( success )
    {
        if ( rcsc::Body_SmartKick ( target_pos, ball_speed, ball_speed * 0.94, 3 ).execute ( agent ) )
        {
            rcsc::KickTable::Sequence seq;
            rcsc::KickTable::instance().simulate ( wm,
                                                   target_pos,
                                                   ball_speed,
                                                   ball_speed * 0.94,
                                                   3,
                                                   seq );
            if ( seq.pos_list_.size() == 1 )
            {
                agent->addSayMessage ( new rcsc::PassMessage ( receiver, target_pos,
                                       agent->effector().queuedNextBallPos(),
                                       agent->effector().queuedNextBallVel() ) );
            }
            return true;
        }
    }
    return false;
}

///through pass

#if 0 
bool
Pass::pass_test_through ( rcsc::PlayerAgent * agent, rcsc::PlayerObject * teammate )
{
      	    const rcsc::WorldModel & wm = agent->world();
    bool success = false ;
    double Ddist;
    
    
    const rcsc::PlayerObject * nearest_tmm_self = wm.getTeammateNearestToSelf(3,false);
    int receiver = nearest_tmm_self->unum();
    Vector2D point = Vector2D(nearest_tmm_self->pos().x + 15 , nearest_tmm_self->pos().y) ; 
    Circle2D circle(point , 7.5);
    rcsc::Sector2D sector(wm.self().pos(), 2.0,5.0,wm.self().body() + 30 , wm.self().body() - 30);
    int reachcycle_first_opp = wm.interceptTable()->opponentReachCycle();
    int reachcycle_second_opp = wm.interceptTable()->secondOpponentReachCycle();
    int reach_cycle_tmm = wm.interceptTable()->teammateReachCycle();
    if(wm.ball().pos().dist(nearest_tmm_self->pos()) < 20 ) success =  true ; 
 
    if(wm.ball().pos().x < nearest_tmm_self ->pos().x) success =true;
 
    if(!wm.existOpponentIn<Circle2D>(circle,3,false)) success =true ;
 
    if(!wm.existOpponentIn<Sector2D>(sector,3,false)) success =true ;
 
 if(reach_cycle_tmm < reachcycle_first_opp && reach_cycle_tmm<reachcycle_second_opp ) success= true; 
 

    double ball_speed = getBestSpeed_test_pass(agent,point);
     cout << "speed  " <<ball_speed<<endl;
if ( success )
    {
        if ( rcsc::Body_SmartKick ( point, ball_speed, ball_speed * 0.94, 3 ).execute ( agent ) )
        {
            rcsc::KickTable::Sequence seq;
            rcsc::KickTable::instance().simulate ( wm,
                                                   nearest_tmm_self->pos(),
                                                   ball_speed,
                                                   ball_speed * 0.94,
                                                   3,
                                                   seq );
            if ( seq.pos_list_.size() == 1 )
            {
                agent->addSayMessage ( new rcsc::PassMessage ( receiver ,  nearest_tmm_self->pos(),
                                       agent->effector().queuedNextBallPos(),
                                       agent->effector().queuedNextBallVel() ) );
            }
            return true;
        }
    }
    return false;

}

#endif
#if 0
/// through pass
bool
Pass::pass_test_through ( rcsc::PlayerAgent * agent, rcsc::PlayerObject * teammate )
{
	    const rcsc::WorldModel & wm = agent->world();
	    double devi_y = (rcsc::ServerParam::i().pitchWidth() - 8) / 6;
		int safe = true;

    Vector2D point[10];

    point[0].assign(25,0);
    point[1].assign(25,12);
    point[2].assign(25,24);
    point[3].assign(25,-12);
    point[4].assign(25,-24);

    point[5].assign(45,24);
    point[6].assign(45,-24);
	for(int i;i<7;i++)
	{
		double dDist;
		
		//Line2D seg=Line2D (wm.self().pos(),point[i]);
		
//		Sector2D sector(wm.self().pos(),1.0,3.0,(wm.self().pos() - point[i]).th() + 20, (wm.self().pos() //-point[i]).th() - 20 );
		if(wm.existOpponentIn (sector,10,false)) safe = false;
		
		if(wm.self().pos().x > point[i].x) safe = false ;

		const rcsc::PlayerObject * opp = wm.getOpponentNearestTo( point[i],10,&dDist );

		//if(seg.dist(opp->pos())<7)safe = false;
		
       		 int cycle_to_reach_opp = opp->playerTypePtr()->cyclesToReachDistance(opp->pos().dist(point[i]));
	
	        const rcsc::PlayerObject * tmm = wm.getTeammateNearestTo( point[i],10,&dDist );
	
		//if(seg.dist(tmm->pos())>15)safe = false;
		
        	int cycle_to_reach_tmm = tmm->playerTypePtr()->cyclesToReachDistance(tmm->pos().dist(point[i]));
		
		if(cycle_to_reach_tmm < cycle_to_reach_opp) safe = false ;

		if(wm.self().pos().dist(point[i])>52) safe = false ;

		//if(wm.self().pos().x < 0 and target_pos.x < 0) safe = false ;

		else 
		safe = true ;

		if(safe)
		{
	           rcsc::Body_SmartKick(point[i],getBestSpeed_test_pass(agent,point[i]),getBestSpeed_test_pass(agent,point[i])*.95,2).execute(agent);
		   agent->setNeckAction ( new Neck_TurnToPoint ( point[i] ) );
            	   return true;
		}	
	
	} 
		
		
		

	}
#endif
#if 0
/// through pass
bool
Pass::pass_test_through ( rcsc::PlayerAgent * agent, rcsc::PlayerObject * teammate )
{

    const rcsc::WorldModel & wm = agent->world();
    double devi_y = (rcsc::ServerParam::i().pitchWidth() - 8) / 7;
 
    Vector2D point[100];

    point[0].assign(35,0);
    point[1].assign(35,devi_y);
    point[2].assign(35,devi_y * 2);
    point[3].assign(35,devi_y * 3);
    point[4].assign(35,devi_y * 4);
    point[5].assign(35,- devi_y);
    point[6].assign(35,- devi_y * 2);
    point[7].assign(35,- devi_y * 3);
    point[8].assign(35,- devi_y * 4);

    point[9].assign (45,0);
    point[10].assign(45,devi_y);
    point[11].assign(45,devi_y * 2);
    point[12].assign(45,devi_y * 3);
    point[13].assign(45,devi_y * 4);
    point[14].assign(45,- devi_y);
    point[15].assign(45,- devi_y * 2);
    point[16].assign(45,- devi_y * 3);
    point[17].assign(45,- devi_y * 4);

//     point[18].assign(21,0);
//     point[19].assign(21,devi_y);
//     point[20].assign(21,devi_y * 2);
//     point[21].assign(21,devi_y * 3);
//     point[22].assign(21,devi_y * 4);
//     point[23].assign(21,- devi_y);
//     point[24].assign(21,- devi_y * 2);
//     point[25].assign(21,- devi_y * 3);
//     point[26].assign(21,- devi_y * 4);
// 
//     point[27].assign(11,0);
//     point[28].assign(11,devi_y);
//     point[29].assign(11,devi_y * 2);
//     point[30].assign(11,devi_y * 3);
//     point[31].assign(11,devi_y * 4);
//     point[32].assign(11,- devi_y);
//     point[33].assign(11,- devi_y * 2);
//     point[34].assign(11,- devi_y * 3);
//     point[35].assign(11,- devi_y * 4);
// 


    bool safe /*= true*/;

    double dDist;
    for ( int i = 0; i < 17; i ++ )
    {

	//int cycle_to_reach_self = selfReachCycle(point[i]);
	
	 //int s = selfReachCycle(wm.self().pos().dist(int[i]));

	//int cycle_to_reach_self =  self_reach_cycle(point[i]);
 	if (wm.self().pos().x < 0 ) safe = false ;

        const rcsc::PlayerObject * opp = wm.getOpponentNearestTo( point[i],4,&dDist );

        int cycle_to_reach_opp = opp->playerTypePtr()->cyclesToReachDistance(opp->pos().dist(point[i]));

//	int cycle_to_reach_ball = Ball->playerTypePtr()->cyclesToReachDistance(Ball->pos().dist(point[i]));

        const rcsc::PlayerObject * tmm = wm.getTeammateNearestTo( point[i],10,&dDist );
        int cycle_to_reach_tmm = tmm->playerTypePtr()->cyclesToReachDistance(tmm->pos().dist(point[i]));
//         if ( !tmm ) return false;

        if ( wm.self().pos().dist(point[i]) > 25 ) safe = false;
        int tm_num = tmm->unum();

        if ( wm.self().pos().x /*+ 5*/ > point[i].x ) safe = false;

        if ( tm_num == wm.self().unum()) safe = false;

	if ( !wm.existTeammateIn<Circle2D>(Circle2D(point[i],15),10,false))  safe = false;
	
	
        if ( cycle_to_reach_tmm > 12 and cycle_to_reach_opp < cycle_to_reach_tmm ) safe = false;

//	if ( cycle_to_reach_self > cycle_to_reach_opp ) safe = false;
	
	//if ( cycle_to_reach_self > cycle_to_reach_tmm ) safe = false;	

        double devider = tmm->pos().dist(point[i])/4;
        Segment2D seg_opp (wm.self().pos(),point[i]);
        Circle2D circle[4];
        Vector2D intr[10];
        circle[0].assign(wm.self().pos(),devider);
        circle[1].assign(wm.self().pos(),devider*2);
        circle[2].assign(wm.self().pos(),devider*3);
        circle[3].assign(wm.self().pos(),devider*4);

        circle[0].intersection(seg_opp,&intr[1],&intr[0]);
        circle[1].intersection(seg_opp,&intr[2],&intr[0]);
        circle[2].intersection(seg_opp,&intr[3],&intr[0]);
        circle[3].intersection(seg_opp,&intr[4],&intr[0]);

  
	Line2D seg=Line2D (wm.self().pos(),point[i]);

//         int reach_cycle_ball = wm.ball.reachCycle();

//         int reach_cycle = wm.ball.reachCycle();

	
        double dDist_Opp[4];
	int cycle = 5;
	
// 	Circle2D s(point[i],8);
// 	if( !wm.existTeammateIn(s,10,false) )safe = false;


	double ball_cycle_1; 
	double dist_intr_1 = wm.self().pos().dist(intr[1]);
	double speed_ball_1 =getBestSpeed_test_pass(agent,intr[1]);
	ball_cycle_1 = speed_ball_1 / rcsc::ServerParam::i().ballDecay() ;
	
	ball_cycle_1 = 4;

        const rcsc::PlayerObject *opp_1 = wm.getOpponentNearestTo(intr[1],10,&dDist_Opp[0]);
	if(seg.dist(opp_1->pos())<5)safe = false;
        int opp_1_cycle = opp_1->playerTypePtr()->cyclesToReachDistance(opp_1->pos().dist(intr[1]));
        if ( opp_1_cycle < ball_cycle_1 ) safe = false;





	double ball_cycle_2; 
	double dist_intr_2 = wm.self().pos().dist(intr[2]);
	double speed_ball_2 =getBestSpeed_test_pass(agent,intr[2]);
	ball_cycle_2 = speed_ball_2/ rcsc::ServerParam::i().ballDecay() ;
	
	ball_cycle_2 = ball_cycle_1;
        const rcsc::PlayerObject *opp_2 = wm.getOpponentNearestTo(intr[2],10,&dDist_Opp[1]);
	if(seg.dist(opp_2->pos())<5)safe = false;
        int opp_2_cycle = opp_2->playerTypePtr()->cyclesToReachDistance(opp_1->pos().dist(intr[2]));
        if ( opp_2_cycle < ball_cycle_2 ) safe = false;



	double ball_cycle_3; 
	double dist_intr_3 = wm.self().pos().dist(intr[3]);
	double speed_ball_3 =getBestSpeed_test_pass(agent,intr[3]);
	ball_cycle_3 = speed_ball_3 / rcsc::ServerParam::i().ballDecay() ;
	


	ball_cycle_3 = ball_cycle_2;		
        const rcsc::PlayerObject *opp_3 = wm.getOpponentNearestTo(intr[3],10,&dDist_Opp[2]);
	if( seg.dist ( opp_3->pos()) < 5 )safe =false;
        int opp_3_cycle = opp_3->playerTypePtr()->cyclesToReachDistance(opp_1->pos().dist(intr[3]));
        if ( opp_3_cycle < ball_cycle_3 ) safe = false;





	double ball_cycle_4; 
	double dist_intr_4 = wm.self().pos().dist(intr[4]);
	double speed_ball_4 =getBestSpeed_test_pass(agent,intr[4]);
	ball_cycle_4 = speed_ball_4 / rcsc::ServerParam::i().ballDecay() ;
	

	ball_cycle_4 = ball_cycle_3;

        const rcsc::PlayerObject *opp_4 = wm.getOpponentNearestTo(intr[4],10,&dDist_Opp[3]);
	if(seg.dist(opp_4->pos())<5)safe = false;
        int opp_4_cycle = opp_4->playerTypePtr()->cyclesToReachDistance(opp_1->pos().dist(intr[4]));
        if ( opp_4_cycle < ball_cycle_4 ) safe = false;

  	Sector2D sector ( wm.self().pos(),1,4, 30, -30 );
	if(wm.existOpponentIn (sector,10,false)) safe = false;
	
	else
	safe = true ;
 
        if ( safe )
        {

		//cout<<"through !!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
            rcsc::Body_SmartKick(point[i],getBestSpeed_test_pass(agent,point[i]),getBestSpeed_test_pass(agent,point[i])*.95,2).execute(agent);
		         //agent->setNeckAction ( new Neck_TurnToPoint ( point[i] ) );
            return true;
        }
	else

        return false;
    }

}
#endif
/// leading pass
bool
Pass::pass_test_leading ( rcsc::PlayerAgent * agent, rcsc::PlayerObject * teammate )
{
    const rcsc::WorldModel & wm = agent->world();
    if ( teammate->pos().dist ( wm.self().pos() ) > 30 // fasele chck mishavad
            || teammate->pos().x < -35 ) // tooye mohavateye khatare ma bood
    {
        return false;
    }
    int ball_cycle = getBallCycle ( agent ,teammate->pos().dist ( wm.ball().pos() ) );
    if ( ball_cycle < 3 )
    {
        return false;
    }
    double x = getDashDist ( teammate, ball_cycle - 3 );
    rcsc::Vector2D target_pos  = teammate->pos() + Vector2D ( 8.0, 0.0 );
    target_pos.x += x;
    int receiver = teammate->unum();

    rcsc::Vector2D vector = target_pos - wm.ball().pos();
    rcsc::AngleDeg angle = vector.th();
    double length = target_pos.dist ( wm.ball().pos() );
    if ( length < 1 )
    {
        length = 1;
    }
    rcsc::Sector2D sector ( wm.ball().pos(),
                            0.1,
                            length,
                            angle - 10,
                            angle + 10 );
    if ( wm.existOpponentIn ( sector, 3, true ) )
    {
        return false;
    }


    rcsc::Vector2D top_left;
    rcsc::Vector2D bottom_right;
    if ( teammate->pos().x > wm.self().pos().x )
    {
        top_left.x = wm.self().pos().x;
        bottom_right.x = teammate->pos().x + 5;
    }
    else
    {
        top_left.x = teammate->pos().x - 5;
        bottom_right.x = wm.self().pos().x;
    }
    if ( teammate->pos().y < wm.self().pos().y )
    {
        top_left.y = teammate->pos().y - 5;
        bottom_right.y = wm.self().pos().y;
    }
    else
    {
        top_left.y = wm.self().pos().y;
        bottom_right.y = teammate->pos().y + 5;
    }

    rcsc::Rect2D rect ( top_left, bottom_right );
    std::vector< rcsc::PlayerObject* > opponents;
    rcsc::PlayerPtrCont::const_iterator end = wm.opponentsFromSelf().end();
    for ( rcsc::PlayerPtrCont::const_iterator it = wm.opponentsFromSelf().begin();
            it != end;
            ++it )
    {


        if ( rect.contains ( ( *it )->pos() ) && ( *it )->pos().dist ( teammate->pos() ) < 10.0 ) // magic number
        {
            opponents.push_back ( ( *it ) );
        }
    }
    int success = false;
    double ball_speed = rcsc::calc_first_term_geom_series ( teammate->pos().dist ( wm.ball().pos() ),
                        rcsc::ServerParam::i().ballDecay(),
                        ball_cycle );


    if ( opponents.empty() )
    {
        success = true;
    }
    else
    {
        for ( unsigned int i = 0; i < opponents.size(); i++ )
        {
            rcsc::Segment2D ball_to_target ( wm.ball().pos(), target_pos );
            int opp_cycle = 1;
            rcsc::Vector2D opp_pos = rcsc::inertia_n_step_point ( opponents.at ( i )->pos(),
                                     opponents.at ( i )->vel(),
                                     3,
                                     opponents.at ( i )->playerTypePtr()->playerDecay() );
            double opp_dist = ball_to_target.dist ( opp_pos );
            double opp_speed = 0;
            double sum = 0;
            while ( sum < opp_dist )
            {
                opp_speed += opponents.at ( i )->playerTypePtr()->dashPowerRate() * 100;
                if ( opp_speed > opponents.at ( i )->playerTypePtr()->playerSpeedMax() )
                    opp_speed = opponents.at ( i )->playerTypePtr()->playerSpeedMax();
                sum += opp_speed;
                opp_speed *= opponents.at ( i )->playerTypePtr()->playerDecay();
                opp_cycle++;
            }

            double tmp_speed = ball_speed;
            int ball_cycle2 = 0;
            sum = 0;
            rcsc::Vector2D via_pos = ball_to_target.nearestPoint ( opp_pos );
            double ball_dist = via_pos.dist ( wm.ball().pos() );
            while ( sum < ball_dist )
            {
                sum += tmp_speed;
                tmp_speed *= rcsc::ServerParam::i().ballDecay();
                ball_cycle2++;
                if ( ball_cycle2 > 35 )
                {
                    return false;
                }
            }

            if ( ball_cycle2 > opp_cycle )
            {
                return false;
            }
            else
            {
                success = true;
            }
        }
    }

    Circle2D cir_check ( target_pos, 6 );
    double distt;
    double dDist;
    const rcsc::PlayerObject * nearest_oppo = wm.getOpponentNearestTo(target_pos,3,&distt);
    double oppo_dist =  target_pos.dist( nearest_oppo->pos() );
    double tmm_dist =   target_pos.dist( teammate->pos() );
	if(oppo_dist < 10)success = false ;
	///check kardan fasele nesbat be khat 
//	Line2D seg=Line2D (wm.self().pos(),target_pos);
	//const rcsc::PlayerObject * s =wm.getOpponentNearestTo(target_pos,3,&distt);
	const rcsc::PlayerObject * opp = wm.getOpponentNearestTo(target_pos,10,&dDist );
//	if(seg.dist(opp->pos())<10)success = false ;
        

        //int cycle_to_reach_opp = opp->playerTypePtr()->cyclesToReachDistance(opp->pos().dist(target_pos));

        const rcsc::PlayerObject * tmm = wm.getTeammateNearestTo(target_pos,10,&dDist );
        //int cycle_to_reach_tmm = tmm->playerTypePtr()->cyclesToReachDistance(tmm->pos().dist(target_pos));
	
	Sector2D s ( wm.self().pos(),1,4, 20, -20 );
	if(wm.existOpponentIn (s,3,false)) success = false;


    if ( wm.existOpponentIn<Circle2D>(cir_check,3,false) ) success =false;
   if (opp and tmm and target_pos.x > 0 /*and cycle_to_reach_opp < cycle_to_reach_tmm */) success = false;
    if ( target_pos.x > 51.0 || target_pos.y >32.0 || target_pos.y < -32.0   ) success = false;

    ball_speed = getBestSpeed_test_pass( agent , target_pos ) ;
    cout << "speed _ leading  " <<ball_speed<<endl;

    if ( success )
    {
        if ( rcsc::Body_SmartKick ( target_pos, ball_speed, ball_speed * 0.94, 3 ).execute ( agent ) )
        {
            rcsc::KickTable::Sequence seq;
            rcsc::KickTable::instance().simulate ( wm,
                                                   target_pos,
                                                   ball_speed,
                                                   ball_speed * 0.94,
                                                   3,
                                                   seq );
            if ( seq.pos_list_.size() == 1 )
            {
                agent->addSayMessage ( new rcsc::PassMessage ( receiver, target_pos,
                                       agent->effector().queuedNextBallPos(),
                                       agent->effector().queuedNextBallVel() ) );
            }
            return true;
        }
    }
    return false;
}

///cross

bool
Pass::pass_cross ( rcsc::PlayerAgent * agent, rcsc::PlayerObject * teammate )
{
    const rcsc::WorldModel & wm = agent->world();
    if ( teammate->pos().dist ( wm.self().pos() ) > 30 // fasele check mishavad
            || teammate->pos().x < -35 ) // tooye mohavateye khatare ma bood
    {
        return false;
    }
    int ball_cycle = getBallCycle ( agent ,teammate->pos().dist ( wm.ball().pos() ) );
    if ( ball_cycle < 3 )
    {
        return false;
    }
    double x = getDashDist ( teammate, ball_cycle - 3 );
    rcsc::Vector2D target_pos = teammate->pos();
    target_pos.x += x;
    int receiver = teammate->unum();

    rcsc::Vector2D vector = target_pos - wm.ball().pos();
    rcsc::AngleDeg angle = vector.th();
    double length = target_pos.dist ( wm.ball().pos() );
    if ( length < 1 )
    {
        length = 1;
    }
    rcsc::Sector2D sector ( wm.ball().pos(),
                            0.1,
                            length,
                            angle - 10,
                            angle + 10 );
    if ( wm.existOpponentIn ( sector, 10, true ) )
    {
        return false;
    }


    rcsc::Vector2D top_left;
    rcsc::Vector2D bottom_right;
    if ( teammate->pos().x > wm.self().pos().x )
    {
        top_left.x = wm.self().pos().x;
        bottom_right.x = teammate->pos().x + 5;
    }
    else
    {
        top_left.x = teammate->pos().x - 5;
        bottom_right.x = wm.self().pos().x;
    }
    if ( teammate->pos().y < wm.self().pos().y )
    {
        top_left.y = teammate->pos().y - 5;
        bottom_right.y = wm.self().pos().y;
    }
    else
    {
        top_left.y = wm.self().pos().y;
        bottom_right.y = teammate->pos().y + 5;
    }

    rcsc::Rect2D rect ( top_left, bottom_right );
    std::vector< rcsc::PlayerObject* > opponents;
    rcsc::PlayerPtrCont::const_iterator end = wm.opponentsFromSelf().end();
    for ( rcsc::PlayerPtrCont::const_iterator it = wm.opponentsFromSelf().begin();
            it != end;
            ++it )
    {

        if ( rect.contains ( ( *it )->pos() ) && ( *it )->pos().dist ( teammate->pos() ) < 10.0 ) // magic number
        {
            opponents.push_back ( ( *it ) );
        }
    }
    int success = false;
    double ball_speed = rcsc::calc_first_term_geom_series ( teammate->pos().dist ( wm.ball().pos() ),
                        rcsc::ServerParam::i().ballDecay(),
                        ball_cycle );


    if ( opponents.empty() )
    {
        success = true;
    }
    else
    {
        for ( unsigned int i = 0; i < opponents.size(); i++ )
        {
            rcsc::Segment2D ball_to_target ( wm.ball().pos(), target_pos );
            int opp_cycle = 1;
            rcsc::Vector2D opp_pos = rcsc::inertia_n_step_point ( opponents.at ( i )->pos(),
                                     opponents.at ( i )->vel(),
                                     3,
                                     opponents.at ( i )->playerTypePtr()->playerDecay() );
            double opp_dist = ball_to_target.dist ( opp_pos );
            double opp_speed = 0;
            double sum = 0;
            while ( sum < opp_dist )
            {
                opp_speed += opponents.at ( i )->playerTypePtr()->dashPowerRate() * 100;
                if ( opp_speed > opponents.at ( i )->playerTypePtr()->playerSpeedMax() )
                    opp_speed = opponents.at ( i )->playerTypePtr()->playerSpeedMax();
                sum += opp_speed;
                opp_speed *= opponents.at ( i )->playerTypePtr()->playerDecay();
                opp_cycle++;
            }

            double tmp_speed = ball_speed;
            int ball_cycle2 = 0;
            sum = 0;
            rcsc::Vector2D via_pos = ball_to_target.nearestPoint ( opp_pos );
            double ball_dist = via_pos.dist ( wm.ball().pos() );
            while ( sum < ball_dist )
            {
                sum += tmp_speed;
                tmp_speed *= rcsc::ServerParam::i().ballDecay();
                ball_cycle2++;
                if ( ball_cycle2 > 25 )
                {
                    return false;
                }
            }

            if ( ball_cycle2 > opp_cycle )
            {
                return false;
            }
            else
            {
                success = true;
            }
        }
    }

    double dist;
    const rcsc::PlayerObject * nearest_tmm = wm.getTeammateNearestTo(target_pos,3, &dist );
    Vector2D B = Vector2D(nearest_tmm->pos().x+1 , nearest_tmm->pos().y);


    ball_speed = getBestSpeed_test_pass(agent ,target_pos);
//	 cout << "speed cross_pass "<< ball_speed << endl;
    if ( success )
    {
        if ( rcsc::Body_SmartKick ( target_pos, ball_speed, ball_speed * 0.94, 3 ).execute ( agent ) )
        {
            rcsc::KickTable::Sequence seq;
            rcsc::KickTable::instance().simulate ( wm,
                                                   target_pos,
                                                   ball_speed,
                                                   ball_speed * 0.94,
                                                   3,
                                                   seq );
            if ( seq.pos_list_.size() == 1 )
            {
                agent->addSayMessage ( new rcsc::PassMessage ( receiver, target_pos,
                                       agent->effector().queuedNextBallPos(),
                                       agent->effector().queuedNextBallVel() ) );
            }
            return true;
        }
    }
    return false;
}
/// get ball cycle
int
Pass::getBallCycle ( const rcsc::PlayerAgent * agent, double dist )
{

  double sum = 0;
  double speed = rcsc::ServerParam::i().ballSpeedMax();
  int cycle = 0;
  while ( cycle < 20 )
  {
    sum += speed;
    speed *= rcsc::ServerParam::i().ballDecay();
    cycle++;
    if ( sum >= dist )
    {
      return cycle;
    }
  }
  return 20;

}
///getDashDist
//tofmali

double
Pass::getDashDist ( const rcsc::PlayerObject * player, int dash_count )
{
    double effort = 1;
    double a = player->playerTypePtr()->playerSize();
    double b = player->playerTypePtr()->dashRate(effort);
    double c = player->playerTypePtr()->playerDecay();

    Circle2D cir ( player->pos(), a + b + c );

    Vector2D v1,v2;
    Rect2D f ( Vector2D ( -52.0, 34), Vector2D ( 52, -34 ) );
    Line2D one = Line2D ( Vector2D ( -52.0, 34), Vector2D ( 52.0,34 ) );
    Line2D one_ = Line2D ( Vector2D ( -52.0, -34), Vector2D ( 52.0,-34 ));
    Line2D one__ = Line2D ( Vector2D ( 52.0, 34), Vector2D ( 52.0,-34 ) );
    Line2D one___ = Line2D ( Vector2D ( 52.0, -34), Vector2D ( 52.0,34 ) );
    int num_c = cir.intersection(one,&v1,&v2);
    int num_c_ = cir.intersection(one_,&v1,&v2);
    int num_c__ = cir.intersection(one__,&v1,&v2);
    int num_c___ = cir.intersection(one___,&v1,&v2);

    if ( num_c == 0 and num_c___ == 0 and num_c__ == 0 and num_c_ == 0  ) {
        return a + b + c;
    }
    else {
#if 0
        dist_ = (player->playerTypePtr()->playerDecay()) * dash_count * dash_count;
        return dist_ ;
        cout<<"D1 -> "<< dist_ << endl;
#endif

        double dist = 0;
        double speed = 0;
        for ( int i = 0; i < dash_count; i++ )
        {
            speed += player->playerTypePtr()->dashPowerRate() * 100;
            dist += speed;
            speed *= player->playerTypePtr()->playerDecay();
        }
//    cout<<"D2 -> "<< dist << endl;
        return dist;
    }

}

/*
void
InterceptTable::predictTeammate()
{
    const PlayerPtrCont & teammates = M_world.teammatesFromBall();
    const PlayerPtrCont::const_iterator t_end = teammates.end();

    if ( M_world.existKickableTeammate() )
    {
        M_teammate_reach_cycle = 0;
    }

    int min_cycle = 1000;
    int second_min_cycle = 1000;

    PlayerIntercept predictor( M_world, M_ball_pos_cache );

    for ( PlayerPtrCont::const_iterator it = teammates.begin();
          it != t_end;
          ++it )
    {
        if ( (*it)->posCount() >= 10 )
        {
            continue;
        }

        const PlayerType * player_type = (*it)->playerTypePtr();
        if ( ! player_type )
        {
            dlog.addText( Logger::INTERCEPT,
                          "ERROR. Intercept. Failed to get teammate player type.",
                          " unum = %d",
                          (*it)->unum() );
            continue;
        }

        int cycle = predictor.predict( *(*it), *player_type,
                                       second_min_cycle );
         if ( cycle < second_min_cycle )
        {
            second_min_cycle = cycle;
            M_second_teammate = *it;

            if ( second_min_cycle < min_cycle )
            {
                std::swap( min_cycle, second_min_cycle );
                std::swap( M_fastest_teammate, M_second_teammate );
            }
        }
    }

    if ( M_second_teammate && second_min_cycle < 1000 )
    {
        M_second_teammate_reach_cycle = second_min_cycle;
    }

    if ( M_fastest_teammate && min_cycle < 1000 )
    {
        M_teammate_reach_cycle = min_cycle;
    }
}
*/

