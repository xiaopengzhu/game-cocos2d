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
	this->map = map;
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
    map->addChild(playerSprite, 20);

    /* 绑定精灵对象 */
    setSprite(playerSprite);

	/* 加载 meta 层 */
	meta = map->layerNamed("meta");
	meta->setVisible(false);

	barrier = map->layerNamed("barrier");

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

void Player::setViewPointByPlayer()
{
    if(mSprite == NULL) {
        return;
    }
    CCLayer* parent = (CCLayer* )mSprite->getParent();

	/* 地图方块数量 */
	CCSize mapTiledNum = map->getMapSize();

    /* 地图单个格子大小 */
    CCSize tiledSize = map->getTileSize();

	/* 地图大小 */
    CCSize mapSize = CCSize(
		mapTiledNum.width * tiledSize.width,
		mapTiledNum.height * tiledSize.height
		);

    /* 屏幕大小 */
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    /* 精灵的坐标 */
    CCPoint spritePos = mSprite->getPosition();

    /* 如果精灵坐标小于屏幕的一半，则取屏幕中点坐标，否则取精灵的坐标 */
    float x = spritePos.x < (visibleSize.width / 2) ? (visibleSize.width / 2) : spritePos.x;
	float y = spritePos.y < (visibleSize.height / 2) ? (visibleSize.height / 2) : spritePos.y;

    /* 如果x、y的坐标大于右上角的极限值，则取极限值的坐标（极限值是指不让地图超出屏幕造成出现黑边的极限坐标） */
    x = x < (mapSize.width - visibleSize.width / 2) ? x : (mapSize.width - visibleSize.width / 2);
    y = y < (mapSize.height - visibleSize.height / 2) ? y : (mapSize.height - visibleSize.height / 2);

    CCPoint destPos = CCPoint(x, y);
    CCPoint centerPos = CCPoint(visibleSize.width / 2, visibleSize.height / 2);

    /* 计算屏幕中点和所要移动的目的点之间的距离 */
    CCPoint viewPos = ccpSub(centerPos, destPos);

    parent->setPosition(viewPos);
}

void Player::setSimplePosition(int x, int y)
{
	/* 获得当前主角在地图中的格子位置 */
	CCPoint tiledPos = tileCoordForPosition(ccp(x, y));

    /* 获取地图格子的唯一标识 */
    int tiledGid = meta->tileGIDAt(tiledPos);

    /* 不为0，代表存在这个格子 */
    if(tiledGid != 0) {
        /*
            获取该地图格子的所有属性，目前我们只有一个Collidable属性,
            格子是属于meta层的，但同时也是属于整个地图的，所以在获取格子的所有属性时，
            通过格子唯一标识在地图中取得。
        */
		CCDictionary* propertiesDict = map->propertiesForGID(tiledGid);

        /* 取得格子的Collidable属性值 */
        const CCString* prop = propertiesDict->valueForKey("Collidable");

        /* 判断Collidable属性是否为true,是的话，不让玩家移动 */
		if(prop->m_sString.compare("true") == 0) {
            if(x > 0) {
                    x -= 1;
                }
                else {
                    x += 1;
                }

                if(y > 0) {
                    y -= 1;
                }
                else {
                    y += 1;
                }
        }

		prop = propertiesDict->valueForKey("star");
		if (prop->length() > 0 && prop->m_sString.compare("true") == 0 ) {
			/* 从障碍物层清除当前格子 */
			barrier->removeTileAt(tiledPos);
		}

    }

	/* 地图方块数量 */
	CCSize mapTiledNum = map->getMapSize();

    /* 地图单个格子大小 */
    CCSize tiledSize = map->getTileSize();

	/* 地图大小 */
    CCSize mapSize = CCSize(
		mapTiledNum.width * tiledSize.width,
		mapTiledNum.height * tiledSize.height
		);
	x = x < (mapSize.width - 38) ? x : (mapSize.width - 38);
    y = y < (mapSize.height - 38) ? y : (mapSize.height - 38);
	if (x < 32) x = 32;
	if (y < 32) y= 32;

	Entity::setSimplePosition(x, y);
	
	//调试日志
	CCLOG ("%4.2f %4.3f \n", mapSize.width, mapSize.height);

	setViewPointByPlayer();
}