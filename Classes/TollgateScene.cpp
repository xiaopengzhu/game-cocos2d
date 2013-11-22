#include "TollgateScene.h"
#include "Player.h"
#include "ThreeDirectionController.h"

CCScene* TollgateScene::scene()
{
    /* create ����Ϊ���÷��������Զ�����init���г�ʼ����release�����ڴ����� */
	CCScene* mScene = CCScene::create();

    TollgateScene* mLayer = TollgateScene::create();

    mScene->addChild(mLayer);

    return mScene;
}

bool TollgateScene::init()
{
    /* ���ص�ͼ */
    CCTMXTiledMap* map = CCTMXTiledMap::create("map/level01.tmx");
    this->addChild(map); 

    /* ������� */
    Player* mPlayer = Player::createWithTiledMap(map);

	/* �����ƶ������� */
    ThreeDirectionController* mSMoveControll = ThreeDirectionController::create();
    mSMoveControll->setiXSpeed(1);
	mSMoveControll->setiYSpeed(0);

    /* ������Ҫ��ӵ������в��ܻ��update�¼� */
    this->addChild(mSMoveControll);

    mPlayer->setController(mSMoveControll);

	mPlayer->run();
    return true;
}
