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
	if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(TollgateScene::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

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

void TollgateScene::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}