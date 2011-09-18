//
//  Bullet.cpp
//  Asteroids
//
//  Created by Clawoo on 9/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Bullet.h"

USING_NS_CC;

Bullet* Bullet::spriteWithFile(const char *pszFileName)
{
    Bullet *pobSprite = new Bullet();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->scheduleUpdate();
        pobSprite->setDistanceMoved(0);
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
	return NULL;
}

void Bullet::update(cocos2d::ccTime dt)
{
    this->setPosition(ccp(this->getPosition().x + velocity_.x, this->getPosition().y + velocity_.y));
    
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
    
    // Increment the distance moved by the velocity vector
    distanceMoved_ += sqrt(pow(velocity_.x, 2) + pow(velocity_.y, 2));
     
    // Determine if bullet is expired -- check to see if its gone at least half the width of the screen
    if (distanceMoved_ > windowSize.width / 2)
    {
        expired_ = true;
    }
    
    // If object moves off the bounds of the screen, make it appear on the other side
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
    else if (this->getPosition().y > windowSize.height)
    {
        this->setPosition(ccp(this->getPosition().x, 0));
    }
}