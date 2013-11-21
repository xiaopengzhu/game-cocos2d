#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"

class Player : public Entity {
public:
    bool initWithTiledMap(CCTMXTiledMap* map);

    static Player* createWithTiledMap(CCTMXTiledMap* map);

	void run();

};

#endif
