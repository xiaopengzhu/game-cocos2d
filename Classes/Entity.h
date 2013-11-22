//Entity.h文件
#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "cocos2d.h"
#include "Controller.h"
#include "ControllerListener.h"

using namespace cocos2d;

class Entity : public CCNode, public ControllerListener {
public:
    void setSprite(CCSprite* mSprite);
    void setController(Controller* controller);

    /* 实现SimpleMoveListener接口的方法 */
    virtual void setSimplePosition(int x, int y);
    virtual CCPoint getCurPosition();
protected:
    CCSprite* mSprite;
    Controller* mController;
	CCTMXTiledMap* map;
	CCTMXLayer* meta;
	CCTMXLayer* barrier;

	CCPoint tileCoordForPosition(CCPoint pos);
};

#endif