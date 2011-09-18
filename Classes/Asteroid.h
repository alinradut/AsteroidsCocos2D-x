//
//  Asteroid.h
//  Asteroids
//
//  Created by Clawoo on 9/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include "cocos2d.h"

class Asteroid : public cocos2d::CCSprite
{
public:
    virtual void update(cocos2d::ccTime dt);
	static Asteroid* spriteWithFile(const char *pszFileName);
    CC_SYNTHESIZE(cocos2d::CCPoint, velocity_, Velocity);
	// implement the "static node()" method manually
	LAYER_NODE_FUNC(Asteroid);
};

#endif // __ASTEROID_H__