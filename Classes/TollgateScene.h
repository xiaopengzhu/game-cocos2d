// TollgateScene.h

#ifndef __TOLLGATE_SCENE_H__
#define __TOLLGATE_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class TollgateScene : public CCLayer {
public:
    CREATE_FUNC(TollgateScene);

    virtual bool init();
    static CCScene* scene();

};

#endif
