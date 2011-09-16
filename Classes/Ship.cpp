//
//  Ship.cpp
//  Asteroids
//
//  Created by Clawoo on 9/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Ship.h"

USING_NS_CC;

bool Ship::initWithTexture(CCTexture2D *pTexture, CCRect rect)
{
    if (!CCSprite::initWithTexture(pTexture, rect))
    {
        return false;
    }
    this->scheduleUpdate();
    return true;
}

void Ship::update(cocos2d::ccTime dt)
{
    this->setPosition(ccp(this->getPosition().x + velocity_.x, this->getPosition().y + velocity_.y));
    
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
    
    if (this->getPosition().x < 0)
    {
        this->setPosition(ccp(windowSize.width, this->getPosition().y));
    }
    else if (this->getPosition().x > windowSize.width)
    {
        this->setPosition(ccp(0, this->getPosition().y));
    }
    
    if (this->getPosition().y < 0)
    {
        this->setPosition(ccp(this->getPosition().x, windowSize.height));
    }
    else if (this->getPosition().x > windowSize.height)
    {
        this->setPosition(ccp(this->getPosition().x, 0));
    }
}