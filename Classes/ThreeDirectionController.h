//ThreeDirectionController.h文件

#ifndef __THREE_DIRECTION_CONTROLLER_H__
#define __THREE_DIRECTION_CONTROLLER_H__

#include "Controller.h"
#include "cocos2d.h"

using namespace cocos2d;

class ThreeDirectionController : public Controller {
public:
    CREATE_FUNC(ThreeDirectionController);
    virtual bool init();
    virtual void update(float dt);

    /* 触屏事件 */
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

    /* 设置X方向的移动速度 */
    void setiXSpeed(int iSpeed);

    /* 设置Y方向的移动速度*/
    void setiYSpeed(int iSpeed);

private:
    int iXSpeed;
    int iYSpeed;

};

#endif
