#include "Entity.h"

void Entity::setSprite( CCSprite* mSprite )
{
    this->mSprite = mSprite;
}

void Entity::setController( Controller* controller )
{
    this->mController = controller;
    controller->setControllerListener(this);
}

void Entity::setSimplePosition( int x, int y )
{
    if(mSprite) {
        mSprite->setPosition(ccp(x, y));
    }
}

cocos2d::CCPoint Entity::getCurPosition()
{
    if(mSprite) {
        return mSprite->getPosition();
    }

    return CCPoint(0, 0);
}

CCPoint Entity::tileCoordForPosition( CCPoint pos)
{
	CCSize mapTileNum = map->getMapSize();
	CCSize tiledSize = map->getTileSize();

	float x = pos.x / tiledSize.width;
	float y = pos.y / tiledSize.height;

	return ccp(x, y);
}