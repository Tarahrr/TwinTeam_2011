#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "Block.h"

#include <rcsc/action/body_advance_ball.h>
#include <rcsc/action/body_dribble.h>
#include <rcsc/action/body_hold_ball.h>
#include <rcsc/action/body_pass.h>
#include <bhv_basic_tackle.h>
#include <rcsc/action/neck_scan_field.h>
#include <rcsc/action/neck_turn_to_low_conf_teammate.h>
#include <rcsc/action/neck_turn_to_ball_and_player.h>
#include <rcsc/action/neck_turn_to_ball.h>

#include <rcsc/player/player_agent.h>
#include <rcsc/player/debug_client.h>

#include <rcsc/common/logger.h>
#include <rcsc/common/server_param.h>
#include <rcsc/geom/sector_2d.h>
#include <rcsc/geom.h>

#include <rcsc/action/body_intercept.h>
#include <math.h>
#include <rcsc/player/intercept_table.h>
#include <rcsc/action/body_go_to_point.h>
#include <rcsc/action/body_turn_to_ball.h>

#include <strategy.h>

using namespace rcsc;
using namespace std;

bool
Block::execute( rcsc::PlayerAgent * agent )
{

    const WorldModel & wm = agent->world();

    /*--------------------------------------------------------*/
    // chase ball
    const int self_min = wm.interceptTable()->selfReachCycle();
    const int mate_min = wm.interceptTable()->teammateReachCycle();
    const int opp_min = wm.interceptTable()->opponentReachCycle();

    
        if ( wm.self().goalie())
    {      
      
    if ( Bhv_BasicTackle( .3, 80 ).execute(agent) ) return true;      
    if ( Bhv_BasicTackle( .8, 60 ).execute(agent) ) return true;
    //do Intercept
//    if ( self_min  < mate_min + 3 and wm.ball().pos().dist( Vector2D ( -52, 0) ) < 15 ) return Body_Intercept().execute(agent);
//     if ( wm.self().stamina() < 2000 /*and wm.ball().pos().x > -36*/ ) return false;  
//     if ( wm.self().unum() > 9 ) return false;
//     if ( wm.self().pos().x >  0 ) return false;
    

    int blockTime;
    Vector2D blockPos;
    float block_x, block_y;
    Vector2D players[4];
    Vector2D posBall = wm.ball().pos();
    float ballSpeed = 0.8;

    if ( posBall.x < -33 && fabs(posBall.y) < 20 )
        ballSpeed = 0.4;

    players[0] = wm.self().pos();
    Vector2D ball = wm.ball().pos();
    Vector2D me = wm.self().pos();
    const rcsc::PlayerObject * opp_tome = wm.getOpponentNearestToSelf(10,false);
    double dash_power;

    if ( !opp_tome ) Body_Intercept().execute(agent);

    if ( opp_tome )
        Vector2D oppPos = opp_tome->pos();

    doBlock(agent, wm.ball().pos(), ballSpeed,1, players, blockTime, block_x, block_y);
    int cycle = wm.self().playerType().cyclesToReachDistance(wm.self().pos().dist(Vector2D(block_x,block_y)));

    if ( cycle < 3 ) return Body_Intercept().execute(agent);

    if ( Body_GoToPoint(Vector2D(block_x,block_y),.3, get_block_dash_power(agent,Vector2D(block_x,block_y))).execute(agent) )
    {
        agent->setNeckAction(new Neck_TurnToBallAndPlayer(wm.getOpponentNearestToBall(5,false)));
        return true;
    }
    if ( !Body_GoToPoint(Vector2D(block_x,block_y),.3, get_block_dash_power(agent,Vector2D(block_x,block_y))).execute(agent) )
    {
        agent->setNeckAction(new Neck_TurnToBall());
        Body_TurnToBall().execute(agent);
        return true;
    }

    return true;
    }

    
    if ( !wm.self().goalie())
    {      
    if ( Bhv_BasicTackle( .8, 60 ).execute(agent) ) return true;
    //do Intercept
//    if ( self_min  < mate_min + 3 and wm.ball().pos().dist( Vector2D ( -52, 0) ) < 15 ) return Body_Intercept().execute(agent);
    if ( wm.self().stamina() < 2000 /*and wm.ball().pos().x > -36*/ ) return false;  
//     if ( wm.self().unum() > 9 ) return false;
//     if ( wm.self().pos().x >  0 ) return false;
    

    int blockTime;
    Vector2D blockPos;
    float block_x, block_y;
    Vector2D players[4];
    Vector2D posBall = wm.ball().pos();
    float ballSpeed = 0.8;

    if ( posBall.x < -33 && fabs(posBall.y) < 20 )
        ballSpeed = 0.4;

    players[0] = wm.self().pos();
    Vector2D ball = wm.ball().pos();
    Vector2D me = wm.self().pos();
    const rcsc::PlayerObject * opp_tome = wm.getOpponentNearestToSelf(5,false);
    double dash_power;


    if ( opp_tome )
        Vector2D oppPos = opp_tome->pos();

    doBlock(agent, wm.ball().pos(), ballSpeed,1, players, blockTime, block_x, block_y);
    int cycle = wm.self().playerType().cyclesToReachDistance(wm.self().pos().dist(Vector2D(block_x,block_y)));

    if ( cycle < 3 ) return Body_Intercept().execute(agent);

    if ( Body_GoToPoint(Vector2D(block_x,block_y),.3, get_block_dash_power(agent,Vector2D(block_x,block_y))).execute(agent) )
    {
        agent->setNeckAction(new Neck_TurnToBallAndPlayer(wm.getOpponentNearestToBall(2,false)));
        return true;
    }
    if ( !Body_GoToPoint(Vector2D(block_x,block_y),.3, get_block_dash_power(agent,Vector2D(block_x,block_y))).execute(agent) )
    {
        agent->setNeckAction(new Neck_TurnToBall());
        Body_TurnToBall().execute(agent);
        return true;
    }

    return false;
    }

}

bool
Block::doBlock( rcsc::PlayerAgent * agent,Vector2D ballPos, float ballSpeed, int playerNums,
                Vector2D *predictPlayers, int &finish_cycle, float &block_x, float &block_y )
{


    const rcsc::WorldModel & wm = agent->world();
    float r1 = 0;
    float pspeed1 = wm.self().speed();
    float r2 = 0;
    float pspeed2 = 0;
    bool found = false;
    float vx, vy;
    Vector2D currentBall = ballPos;
    int time = 0;

    float dashRate =  wm.self().dashRate();
    float playerDecay = wm.self().playerType().playerDecay();

    while (!found)
    {
        Vector2D meToBall = currentBall - wm.self().pos();
        float delAngle = meToBall.dir().degree() - wm.self().body().degree();
        delAngle = fabs(delAngle);

        if (delAngle < 20 && r1 > meToBall.r())
        {

            found = true;
            break;
        }
        if (r2 > meToBall.r())
        {

            found = true;
            break;
        }
        vx = -ballSpeed;
        vy = 0;
        if (currentBall.x < -36)
        {

            Vector2D dribbleVel = Vector2D(-52, 0) - ballPos;
            dribbleVel.setLength(ballSpeed);
            vx = dribbleVel.x;
            vy = dribbleVel.y;
        }
        currentBall += Vector2D(vx, vy);
        time++;
        if (time > 1)

            pspeed2 = pspeed2 * playerDecay + dashRate * 100;

        pspeed1 = pspeed1 * playerDecay + dashRate * 100;
        r1 += pspeed1;
        r2 += pspeed2;

    }

    finish_cycle = time;
    block_x = currentBall.x;
    block_y = currentBall.y;

    Vector2D v1 = Vector2D(block_x, block_y) - ballPos;
    Vector2D v2 = wm.self().pos() - ballPos;
    float angle = v1.dir().degree() - v2.dir().degree();
    angle = rcsc::AngleDeg::normalize_angle(angle);
    angle = fabs(angle);

    Vector2D oppPoint;
    oppPoint = ballPos;
    const rcsc::PlayerObject * opp = wm.getOpponentNearestToBall(5,false);

    Vector2D tempPos;
    if (opp )

        tempPos =  opp->pos();
    if (opp && tempPos.dist(ballPos) < 1.5)
        oppPoint = tempPos;

    Vector2D ball = wm.ball().pos() ;
    Vector2D me = wm.self().pos() ;
    Vector2D bestPos = me + Vector2D::polar2vector( 1.3, wm.self().body() );
    if ( ball.dist( bestPos ) < 0.4 && wm.ball().posCount() < 3)
        return true;

    return false;

}

double
Block::get_block_dash_power( rcsc::PlayerAgent * agent, Vector2D target )
{
    const rcsc::WorldModel & wm = agent->world();
    const rcsc::PlayerObject * opp = wm.getOpponentNearestToBall(5,false );
    
    double dash_power ;
    double opp_speed = opp->vel().r();
    double agent_speed = wm.self().speed();
    double dist_to_target = wm.self().pos().dist(target);
    double dist_target_to_opp = target.dist(opp->pos());
    double dist_opp_to_goal = opp->pos().dist(Vector2D( -52,0 ));

    switch ( Strategy::get_ball_area(target) )
    {
    case Strategy::BA_Danger :
    case Strategy::BA_CrossBlock :
    case Strategy::BA_Stopper :
        dash_power = rcsc::ServerParam::i().maxDashPower();
        break;
    case Strategy::BA_DribbleBlock :
        dash_power = rcsc::ServerParam::i().maxDashPower() * 0.9; //0.95  
        break;
    case Strategy::BA_DefMidField  :
        dash_power = rcsc::ServerParam::i().maxDashPower() * 0.8; //0.85 ;
	break;
    default:
        dash_power = rcsc::ServerParam::i().maxDashPower() * 0.75;  //0.80 ;
	break;
    }

    return dash_power;

}
