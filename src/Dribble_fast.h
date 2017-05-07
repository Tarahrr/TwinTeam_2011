#ifndef DRIBBLEFAST_H
#define DRIBBLEFAST_H

#include <rcsc/geom/vector_2d.h>
#include <rcsc/player/soccer_action.h>
#include <rcsc/player/player_agent.h>

class DribbleFast    : public rcsc::SoccerBehavior
 {
private:

public:

  DribbleFast()
{}
    bool execute(  rcsc::PlayerAgent * agent );
};
#endif