#include "TollgateScene.h"
#include "Player.h"
#include "ThreeDirectionController.h"

CCScene* TollgateScene::scene()
{
    /* create 方法为内置方法，会自动调用init进行初始化和release进行内存销毁 */
	CCScene* mScene = CCScene::create();

    TollgateScene* mLayer = TollgateScene::create();

    mScene->addChild(mLayer);

    return mScene;
}

bool TollgateScene::init()
{
    /* 加载地图 */
    CCTMXTiledMap* map = CCTMXTiledMap::create("map/level01.tmx");
    this->addChild(map); 

    /* 创建玩家 */
    Player* mPlayer = Player::createWithTiledMap(map);

	/* 创建移动控制器 */
    ThreeDirectionController* mSMoveControll = ThreeDirectionController::create();
    mSMoveControll->setiXSpeed(1);
	mSMoveControll->setiYSpeed(0);

    /* 控制器要添加到场景中才能获得update事件 */
    this->addChild(mSMoveControll);

    mPlayer->setController(mSMoveControll);

	mPlayer->run();
    return true;
}
