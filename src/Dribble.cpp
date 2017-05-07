#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "Dribble.h"

#include <rcsc/action/body_smart_kick.h>
#include <rcsc/action/body_advance_ball.h>
#include <rcsc/action/body_dribble.h>
#include <rcsc/action/body_hold_ball.h>
#include <rcsc/action/body_pass.h>
#include <rcsc/action/neck_scan_field.h>
#include <rcsc/action/neck_turn_to_low_conf_teammate.h>

#include <rcsc/player/player_agent.h>
#include <rcsc/player/debug_client.h>

#include <rcsc/common/logger.h>
#include <rcsc/common/server_param.h>
#include <rcsc/geom/sector_2d.h>
#include <vector>
#include <rcsc/action/body_intercept.h>
#include <rcsc/geom/polygon_2d.h>
#include <rcsc/geom.h>
#include <Dribble_fast.h>
#include "srp.h"
using namespace rcsc;
using namespace std;
/*-------------------------------------------------------------------*/
/*!

 */
bool
Dribble::execute( rcsc::PlayerAgent * agent )
{
    const rcsc::WorldModel & wm = agent ->world();
    Vector2D pos_agent=wm.self().pos();
    Vector2D drib_target = get_target_point( agent );
    const int max_dash_step
    = wm.self().playerType()
      .cyclesToReachDistance( wm.self().pos().dist( drib_target ) );

    if ( SRPdribble().execute(agent))
    {
//         Body_Intercept().execute(agent);
// 	    std::cout<<" SRP  ->   "<<   wm.time().cycle()   <<  std::endl;
        return true;
    }

    rcsc::Body_Dribble( drib_target,
                        1.0,
                        rcsc::ServerParam::i().maxDashPower(),
                        std::min( 3, max_dash_step )
                        ,false).execute( agent );


    agent ->setNeckAction(new Neck_ScanField());
    return true;


}

DRIBBLE_REGION
Dribble::get_dribble_region(PlayerAgent * agent)
{
    const rcsc::WorldModel & wm = agent ->world();
    Vector2D pos_agent=wm.self().pos();
    if (pos_agent.x < 52.5 and pos_agent.x >36.5 and pos_agent.y < 17 and pos_agent.y >-17)

        return Region_11;

    if (pos_agent.x < 52.5 and pos_agent.x >36.5 and pos_agent.y < -17 and pos_agent.y >-34)

        return Region_10;

    if (pos_agent.x < 52.5 and pos_agent.x >36.5 and pos_agent.y < 34 and pos_agent.y >17)

        return Region_13;

    if (pos_agent.x < 36.5 and pos_agent.x >0 and pos_agent.y < -15 and pos_agent.y >-34)

        return Region_9;

    if (pos_agent.x < 36.5 and pos_agent.x >0 and pos_agent.y < 34 and pos_agent.y > 15)

        return Region_12;

    if (pos_agent.x < 36.5 and pos_agent.x > 0 and pos_agent.y < 15 and pos_agent.y >-15)

        return Region_1;
    else return Region_illegal;

}

rcsc::Vector2D
Dribble::get_target_point(PlayerAgent * agent)
{
    const WorldModel & wm = agent ->world();
    Vector2D target_point;
    Vector2D pos_agent=wm.self().pos();
    if (get_dribble_region( agent) == Region_11)
    {
        Vector2D target_point(52.5 , 0.0);
        return target_point;
    }
    if (get_dribble_region( agent) == Region_10)
    {
        Vector2D target_point(49.0 , -10.0);
        return target_point;
    }
    if (get_dribble_region( agent) == Region_13)
    {
        Vector2D target_point(49.0 , 10.0);
        return target_point;
    }
    if (get_dribble_region( agent) == Region_9)
    {
        Vector2D target_point(45.5 , -25.0);
        return target_point;
    }
    if (get_dribble_region( agent) == Region_12)
    {
        Vector2D target_point(45.5 , 25.0);
        return target_point;
    }
    if (get_dribble_region( agent) == Region_1)
    {
        Vector2D target_point((pos_agent.x+10.0),pos_agent.y);
        return target_point;
    }
    if (get_dribble_region( agent) == Region_illegal)
    {
        Vector2D target_point((pos_agent.x+10.0),pos_agent.y);
        return target_point;
    }

}


// bool
// Dribble::fast_dribble( rcsc::PlayerAgent * agent )
// {
//     const rcsc::WorldModel & wm = agent->world();
//     double fast_speed = .7;
//     if (wm.self().pos().x > 36) fast_speed = .5;
// 
//     Circle2D circle[2];
//     Vector2D intr[16];
// 
// 
//     Segment2D seg_dribble_0( wm.self().pos(),8,0);
//     Segment2D seg_dribble1_15( wm.self().pos(),8,15);
//     Segment2D seg_dribble2_15( wm.self().pos(),8,-15);
//     Segment2D seg_dribble1_30( wm.self().pos(),8,30);
//     Segment2D seg_dribble2_30( wm.self().pos(),8,-30);
//     Segment2D seg_dribble1_60( wm.self().pos(),8,60);
//     Segment2D seg_dribble2_60( wm.self().pos(),8,-60);
//     Segment2D seg_dribble1_45( wm.self().pos(),8,45);
//     Segment2D seg_dribble2_45( wm.self().pos(),8,-45);
// 
//     circle[0].assign(wm.self().pos(),8);
//     circle[1].assign(wm.self().pos(),4);
// 
//     //noghat barkhord khat ba dayere
//     circle[0].intersection(seg_dribble_0, &intr[6],&intr[16]);
// 
//     circle[0].intersection(seg_dribble1_15, &intr[1],&intr[16]);
// 
//     circle[0].intersection(seg_dribble2_15, &intr[2],&intr[16]);
// 
//     circle[0].intersection(seg_dribble1_30,&intr[5],&intr[16]);
// 
//     circle[0].intersection(seg_dribble2_30,&intr[7],&intr[16]);
// 
//     circle[0].intersection(seg_dribble1_45,&intr[0],&intr[16]);
// 
//     circle[0].intersection(seg_dribble2_45,&intr[3],&intr[16]);
// 
//     circle[0].intersection(seg_dribble1_60,&intr[4],&intr[16]);
// 
//     circle[0].intersection(seg_dribble2_60,&intr[8],&intr[16]);
// 
// 
// 
//     circle[1].intersection(seg_dribble_0,&intr[12],&intr[16]);
// 
//     circle[1].intersection(seg_dribble1_15, &intr[11],&intr[16]);
// 
//     circle[1].intersection(seg_dribble2_15, &intr[13],&intr[16]);
// 
//     circle[1].intersection(seg_dribble1_30,&intr[10],&intr[16]);
// 
//     circle[1].intersection(seg_dribble2_30,&intr[14],&intr[16]);
// 
//     circle[1].intersection(seg_dribble1_45,&intr[9],&intr[16]);
// 
//     circle[1].intersection(seg_dribble2_45,&intr[15],&intr[16]);
// 
//     vector < rcsc::Vector2D > shekl_0;
// 
//     Vector2D shekl0_1(intr[0]);
//     Vector2D shekl0_2(intr[4]);
//     Vector2D shekl0_3(intr[5]);
//     Vector2D shekl0_4(intr[11]);
//     Vector2D shekl0_5(wm.self().pos());
//     Vector2D shekl0_6(intr[9]);
//     shekl_0.push_back(shekl0_1);
//     shekl_0.push_back(shekl0_2);
//     shekl_0.push_back(shekl0_3);
//     shekl_0.push_back(shekl0_4);
//     shekl_0.push_back(shekl0_5);
//     shekl_0.push_back(shekl0_6);
//     const rcsc::Polygon2D shekl0 (shekl_0);
// 
//     vector < rcsc::Vector2D > shekl_1;
// 
//     Vector2D shekl1_1(intr[5]);
//     Vector2D shekl1_2(intr[1]);
//     Vector2D shekl1_3(intr[6]);
//     Vector2D shekl1_4(intr[11]);
//     Vector2D shekl1_5(wm.self().pos());
//     shekl_1.push_back(shekl1_1);
//     shekl_1.push_back(shekl1_2);
//     shekl_1.push_back(shekl1_3);
//     shekl_1.push_back(shekl1_4);
//     shekl_1.push_back(shekl1_5);
//     const rcsc::Polygon2D shekl1 (shekl_1);
// 
//     vector < rcsc::Vector2D > shekl_2;
// 
//     Vector2D shekl2_1(intr[7]);
//     Vector2D shekl2_2(intr[6]);
//     Vector2D shekl2_3(intr[2]);
//     Vector2D shekl2_4(intr[13]);
//     Vector2D shekl2_5(wm.self().pos());
//     shekl_2.push_back(shekl2_1);
//     shekl_2.push_back(shekl2_2);
//     shekl_2.push_back(shekl2_3);
//     shekl_2.push_back(shekl2_4);
//     shekl_2.push_back(shekl2_5);
//     const rcsc::Polygon2D shekl2 (shekl_2);
// 
//     vector < rcsc::Vector2D > shekl_3;
// 
//     Vector2D shekl3_1(intr[7]);
//     Vector2D shekl3_2(intr[8]);
//     Vector2D shekl3_3(intr[15]);
//     Vector2D shekl3_4(intr[3]);
//     Vector2D shekl3_5(intr[13]);
//     Vector2D shekl3_6(wm.self().pos());
//     shekl_3.push_back(shekl3_1);
//     shekl_3.push_back(shekl3_2);
//     shekl_3.push_back(shekl3_3);
//     shekl_3.push_back(shekl3_4);
//     shekl_3.push_back(shekl3_5);
//     shekl_3.push_back(shekl3_6);
//     const rcsc::Polygon2D shekl3 (shekl_3);
// 
// // ina fasele ha hastan
//     double dist_to_goal[3];
//     dist_to_goal[0] = intr[0].dist(Vector2D (ServerParam::i().pitchLength() / 2,0.0));
//     dist_to_goal[1] = intr[1].dist(Vector2D (ServerParam::i().pitchLength() / 2,0.0));
//     dist_to_goal[2] = intr[2].dist(Vector2D (ServerParam::i().pitchLength() / 2,0.0));
//     dist_to_goal[3] = intr[3].dist(Vector2D (ServerParam::i().pitchLength() / 2,0.0));
// // dist_to_goal[4] = targets[4].dist(Vector2D (PITCH_LENGTH / 2,0.0));
// // dist_to_goal[5] = targets[5].dist(Vector2D (PITCH_LENGTH / 2,0.0));
// // dist_to_goal[6] = targets[6].dist(Vector2D (PITCH_LENGTH / 2,0.0));
// // dist_to_goal[7] = targets[7].dist(Vector2D (PITCH_LENGTH / 2,0.0));
// // dist_to_goal[8] = targets[8].dist(Vector2D (PITCH_LENGTH / 2,0.0));
// // dist_to_goal[9] = targets[9].dist(Vector2D (PITCH_LENGTH / 2,0.0));
// 
//     int index[4] = {0,1,2,3};
// // sort
//     int i, j, min, minat;
//     for (i = 0; i <= 4; i++)
//     {
//         minat= i;
//         min= dist_to_goal[i];
//         for (j = i+1;j <= 4; j++)
//         {
//             if (min > dist_to_goal[j])
//             {
//                 minat = j;
//                 min = dist_to_goal[j];
//             }
//         }
//         double temp = dist_to_goal[i];
//         dist_to_goal[i] = dist_to_goal[minat];
//         dist_to_goal[minat]=temp;
//         temp = index[i];
//         index[i] = index[minat];
//         index[minat]=temp;
//     }
// // chizi ke biroon miad faseleye sort shode be hamrahe index esh hast, yani inke vaghte masalan  dist_to_goal[3] kamtaririn bashe, index e 3 ro barmigardoone
// 
//     for (int z =0 ; z < 4 ; z++)
//     {
//         bool is_safe ;
// //   double dist = dist_to_goal[z];
//         int num = index[z];
//         if (num == 0)
//         {
//             if (!wm.existOpponentIn<Polygon2D>(shekl0,3,false ))
//                 is_safe = true ;
//             if (is_safe)
//             {
//                 std::cout<<"SRP ->  shekl0 "<<std::endl;
//                 Body_SmartKick(Vector2D ( intr[5] ),fast_speed,fast_speed * .94,1).execute(agent);
//                 agent ->setNeckAction( new Neck_TurnToLowConfTeammate());
//                 return true;
//             }
// 
//         }
//         if (num == 1)
//         {
//             if (!wm.existOpponentIn<Polygon2D>(shekl1,3,false ))
//                 is_safe = true ;
//             if (is_safe)
//             {
//                 std::cout<<"SRP ->  shekl1 "<<std::endl;
//                 Body_SmartKick(Vector2D ( intr[1] ),fast_speed,fast_speed * .94,1).execute(agent);
//                 agent ->setNeckAction( new Neck_TurnToLowConfTeammate());
//                 return true;
//             }
// 
//         }
//         if (num == 2)
//         {
//             if ( ! wm.existOpponentIn<Polygon2D>(shekl2,3,false ))
//                 is_safe = true;
//             if (is_safe)
//             {
//                 std::cout<<"SRP ->  shekl2 "<<std::endl;
//                 Body_SmartKick(Vector2D ( intr[6] ),fast_speed,fast_speed * .94,1).execute(agent);
//                 agent ->setNeckAction( new Neck_TurnToLowConfTeammate());
//                 return true;
//             }
// 
//         }
//         if (num == 3)
//         {
//             if (!wm.existOpponentIn<Polygon2D>(shekl3,3,false ))
//                 is_safe = true;
//             if (is_safe)
//             {
//                 std::cout<<"SRP -> shekl3  "<<std::endl;
//                 Body_SmartKick(Vector2D ( intr[7] ),fast_speed,fast_speed * .94,1).execute(agent);
//                 agent ->setNeckAction( new Neck_TurnToLowConfTeammate());
//                 return true;
// 
//             }
//         }
//     }
//     return false;
// }
