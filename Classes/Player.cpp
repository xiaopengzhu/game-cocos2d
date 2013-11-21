#include "Player.h"

Player* Player::createWithTiledMap( CCTMXTiledMap* map )
{
    Player* mPlayer = new Player();

    if(mPlayer && mPlayer->initWithTiledMap(map)) {
    }
    else {
        CC_SAFE_DELETE(mPlayer);
    }

    return mPlayer;
}

bool Player::initWithTiledMap( CCTMXTiledMap* map )
{
    /* 加载对象层 */
    CCTMXObjectGroup* objGroup = map->objectGroupNamed("objects");

    /* 加载玩家坐标对象 */
    CCDictionary* playerPointDic = objGroup->objectNamed("PlayerPoint");
    float playerX = playerPointDic->valueForKey("x")->floatValue();
    float playerY = playerPointDic->valueForKey("y")->floatValue();

    /* -------------- 加载玩家 --------------- */
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCSprite* playerSprite = CCSprite::create("sprite/player1.png");
    playerSprite->setPosition(ccp(playerX, playerY));

    /* 精灵添加到地图 */
    map->addChild(playerSprite);

    /* 绑定精灵对象 */
    setSprite(playerSprite);
    return true;
}

void Player::run()
{
    CCArray* framesList = CCArray::create();

    framesList->addObject(CCSpriteFrame::create("sprite/player1.png", CCRectMake(0, 0, 77, 134)));
    framesList->addObject(CCSpriteFrame::create("sprite/player2.png", CCRectMake(0, 0, 66, 129)));
    framesList->addObject(CCSpriteFrame::create("sprite/player3.png", CCRectMake(0, 0, 99, 132)));
    framesList->addObject(CCSpriteFrame::create("sprite/player4.png", CCRectMake(0, 0, 111, 135)));
    framesList->addObject(CCSpriteFrame::create("sprite/player5.png", CCRectMake(0, 0, 94, 132)));
    framesList->addObject(CCSpriteFrame::create("sprite/player6.png", CCRectMake(0, 0, 64, 128)));
    framesList->addObject(CCSpriteFrame::create("sprite/player7.png", CCRectMake(0, 0, 96, 133)));
    framesList->addObject(CCSpriteFrame::create("sprite/player8.png", CCRectMake(0, 0, 103, 138)));

    CCAnimation* animation = CCAnimation::createWithSpriteFrames(framesList, 0.2f);
    animation->setLoops(-1);

    mSprite->runAction(CCAnimate::create(animation));
}

