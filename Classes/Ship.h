//
//  Ship.h
//  Asteroids
//
//  Created by Clawoo on 9/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef __SHIP_H__
#define __SHIP_H__

#include "cocos2d.h"

class Ship : public cocos2d::CCSprite
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool initWithTexture(cocos2d::CCTexture2D *pTexture, cocos2d::CCRect rect);  
    virtual void update(cocos2d::ccTime dt);
	
    CC_SYNTHESIZE(cocos2d::CCPoint, velocity_, Velocity);
	// implement the "static node()" method manually
	LAYER_NODE_FUNC(Ship);
};

#endif // __SHIP_H__