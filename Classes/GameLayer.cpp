//
//  GameLayer.cpp
//  Asteroids
//
//  Created by Clawoo on 9/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "GameLayer.h"

USING_NS_CC;

CCScene* GameLayer::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();
	
	// 'layer' is an autorelease object
	GameLayer *layer = GameLayer::node();
    
	// add layer as a child to scene
	scene->addChild(layer);
    
	// return the scene
	return scene;
}

bool GameLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
    
    // Get window size
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
    
    // Create ship object, position it, then add to layer
    ship_ = (Ship *)Ship::spriteWithFile("ship.png");
    ship_->setPosition(ccp(windowSize.width / 2, windowSize.height / 2));
    this->addChild(ship_);
    
	return true;
}

CCMutableArray<CCTouch *>* allTouches(CCSet *touches)
{
    CCMutableArray<CCTouch *> *arr = new CCMutableArray<CCTouch *>();
    
    CCSetIterator it;
    
	for( it = touches->begin(); it != touches->end(); it++) 
    {
        arr->addObject((CCTouch *)*it);
    }
    return arr;
}

void GameLayer::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    // This method is passed an NSSet of touches called (of course) "touches"
	// CCSet does not have the allObjects method so we cannot get an array out of it, 
    // therefore we need to manually iterate and improvise
    
    CCSetIterator it;
	CCTouch* fingerOne;
    CCPoint pointOne;
    
    int i = 0;
	for( it = touches->begin(); it != touches->end(); it++) 
    {
        switch (i) {
            case 0: {
                fingerOne = (CCTouch *) *it;
                
                // Convert each UITouch object to a CGPoint, which has x/y coordinates we can actually use
                pointOne = fingerOne->locationInView(fingerOne->view());
                
                // The touch points are always in "portrait" coordinates - convert to landscape
                pointOne = CCDirector::sharedDirector()->convertToGL(pointOne);
                
                // We store the starting point of the touch so we can determine whether the touch is a swipe or tap.
                // A tap shouldn't move, so we compare the distance of the starting/ending touches, and if the distance is
                // small enough (we account for a bit of movement, just in case), the input is considered a tap
                startTouchPoint_ = pointOne;
                break;
            }
                
            case 1: {
                CCTouch *fingerTwo = (CCTouch *) *it;
                
                // Convert each UITouch object to a CGPoint, which has x/y coordinates we can actually use
                CCPoint pointTwo = fingerTwo->locationInView(fingerTwo->view());
                
                // The touch points are always in "portrait" coordinates - convert to landscape
                pointTwo = CCDirector::sharedDirector()->convertToGL(pointTwo);
                
                // Initialize the variables used to store the angle of rotation derived from the user's fingers
                currentTouchAngle_ = previousTouchAngle_ = CC_RADIANS_TO_DEGREES(atan2(pointOne.x - pointTwo.x, pointOne.y - pointTwo.y));
                break;
            }
                
            default:
                break;
        }
        i++;
    }
}

void GameLayer::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
}

void GameLayer::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
}