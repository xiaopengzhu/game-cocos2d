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

    return CCPoint::CCPoint(0, 0);
}
