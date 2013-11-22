#include "ThreeDirectionController.h"

bool ThreeDirectionController::init()
{
    this->iXSpeed = 0;
    this->iYSpeed = 0;

    /* 设置允许触屏 */
    this->setTouchEnabled(true);

    this->scheduleUpdate();
    return true;
}

void ThreeDirectionController::update( float dt )
{
    if(mControllerListener == NULL) {
        return;
    }

    CCPoint curPos = mControllerListener->getCurPosition();

    curPos.x += iXSpeed;
    curPos.y += iYSpeed;

    mControllerListener->setSimplePosition(curPos.x + iXSpeed, curPos.y + iYSpeed);
}

void ThreeDirectionController::setiXSpeed( int iSpeed )
{
    this->iXSpeed = iSpeed;
}

void ThreeDirectionController::setiYSpeed( int iSpeed )
{
    this->iYSpeed = iSpeed;
}

bool ThreeDirectionController::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
    return true;
}

void ThreeDirectionController::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
    /* 获取点击的坐标 */
    CCPoint touchLocation = pTouch->getLocationInView();
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);

    /* 被控制对象的坐标 */
    CCPoint pos = mControllerListener->getCurPosition();

    /* 判断是向上移动还是向下移动 */
    int iSpeed = 0;
    if(touchLocation.y > pos.y) {
        iSpeed = 1;
    }
    else {
        iSpeed = -1;
    }

    setiYSpeed(iSpeed);
}

void ThreeDirectionController::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
    /* 停止Y坐标上的移动 */
    setiYSpeed(0);
}

void ThreeDirectionController::registerWithTouchDispatcher()
{
    /* 注册触屏事件 */
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}
