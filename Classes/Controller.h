#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "cocos2d.h"
#include "ControllerListener.h"

using namespace cocos2d;

class Controller : public CCLayer {
public:
    /* …Ë÷√º‡Ã˝∂‘œÛ */
    void setControllerListener(ControllerListener* mControllerListener);

protected:
    ControllerListener* mControllerListener;
};

#endif
