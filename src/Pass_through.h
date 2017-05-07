#ifndef PASSTHROUGH_H
#define PASSTHROUGH_H

#include <rcsc/player/soccer_action.h>
#include <rcsc/player/player_object.h>

class PassThrough
 {

public:

  PassThrough()
{}
		bool 
		execute ( rcsc::PlayerAgent * agent, rcsc::PlayerObject * teammate );
};
#endif