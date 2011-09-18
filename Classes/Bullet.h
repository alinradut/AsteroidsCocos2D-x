//
//  Bullet.h
//  Asteroids
//
//  Created by Clawoo on 9/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"

class Bullet : public cocos2d::CCSprite
{
public:    
    virtual void update(cocos2d::ccTime dt);
	static Bullet* spriteWithFile(const char *pszFileName);

    CC_SYNTHESIZE(float, distanceMoved_, DistanceMoved);
    CC_SYNTHESIZE(cocos2d::CCPoint, velocity_, Velocity);
    CC_SYNTHESIZE(bool, expired_, Expired);

	// implement the "static node()" method manually
	LAYER_NODE_FUNC(Bullet);
};

#endif // __BULLET_H__