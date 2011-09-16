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
    
    setIsTouchEnabled(true);
    
    // Get window size
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
    
    // Create ship object, position it, then add to layer
    ship_ = (Ship *)Ship::spriteWithFile("ship.png");
    ship_->setPosition(ccp(windowSize.width / 2, windowSize.height / 2));
    this->addChild(ship_);
    
	return true;
}

CCMutableArray<CCTouch *>* GameLayer::allTouchesFromSet(CCSet *touches)
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
    // We need to convert it to an array first
    CCMutableArray<CCTouch *> *allTouches = this->allTouchesFromSet(touches);
    CCTouch* fingerOne = (CCTouch *)allTouches->getObjectAtIndex(0);
    
    // Convert each UITouch object to a CGPoint, which has x/y coordinates we can actually use
    CCPoint pointOne = fingerOne->locationInView(fingerOne->view());
    
    // The touch points are always in "portrait" coordinates - convert to landscape
    pointOne = CCDirector::sharedDirector()->convertToGL(pointOne);
    
    // We store the starting point of the touch so we can determine whether the touch is a swipe or tap.
    // A tap shouldn't move, so we compare the distance of the starting/ending touches, and if the distance is
    // small enough (we account for a bit of movement, just in case), the input is considered a tap
    startTouchPoint_ = pointOne;
    if (allTouches->count() > 1)
    {
        CCTouch *fingerTwo = allTouches->getObjectAtIndex(1);
        
        // Convert each UITouch object to a CGPoint, which has x/y coordinates we can actually use
        CCPoint pointTwo = fingerTwo->locationInView(fingerTwo->view());
        
        // The touch points are always in "portrait" coordinates - convert to landscape
        pointTwo = CCDirector::sharedDirector()->convertToGL(pointTwo);
        
        // Initialize the variables used to store the angle of rotation derived from the user's fingers
        currentTouchAngle_ = previousTouchAngle_ = CC_RADIANS_TO_DEGREES(atan2(pointOne.x - pointTwo.x, pointOne.y - pointTwo.y));
    }
}

void GameLayer::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
    // This method is passed an NSSet of touches called (of course) "touches"
    // We need to convert it to an array first
    CCMutableArray<CCTouch *> *allTouches = this->allTouchesFromSet(touches);

    // Only run the following code if there is more than one touch
    if (allTouches->count() > 1)
    {
        // We're going to track the first two touches (i.e. first two fingers)
        // Create "UITouch" objects representing each touch
        CCTouch *fingerOne = allTouches->getObjectAtIndex(0);
        CCTouch *fingerTwo = allTouches->getObjectAtIndex(1);
        
        // Convert each UITouch object to a CGPoint, which has x/y coordinates we can actually use
        CCPoint pointOne = fingerOne->locationInView(fingerOne->view());
        CCPoint pointTwo = fingerTwo->locationInView(fingerTwo->view());
        
        // The touch points are always in "portrait" coordinates - you will need to convert them if in landscape (which we are)
        pointOne = CCDirector::sharedDirector()->convertToGL(pointOne);
        pointTwo = CCDirector::sharedDirector()->convertToGL(pointTwo);
        
        // Get the angle that's created by the user's two fingers
        currentTouchAngle_ = CC_RADIANS_TO_DEGREES(atan2(pointOne.x - pointTwo.x, pointOne.y - pointTwo.y));
        
        // Compare with the previous angle, to decide whether the change is positive or negative.
        float difference = currentTouchAngle_ - previousTouchAngle_;
        
        // The ship is then rotated by that difference
        ship_->setRotation(ship_->getRotation() + difference);
        
        // Store the current angle variable to be used again on the next loop iteration
        previousTouchAngle_ = currentTouchAngle_;
    }
}

void GameLayer::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    // This method is passed an NSSet of touches called (of course) "touches"
    // We need to convert it to an array first
    CCMutableArray<CCTouch *> *allTouches = this->allTouchesFromSet(touches);
    
    if (allTouches->count() == 1)
    {
        CCTouch* fingerOne = (CCTouch *)allTouches->getObjectAtIndex(0);
        
        // Convert each UITouch object to a CGPoint, which has x/y coordinates we can actually use
        CCPoint pointOne = fingerOne->locationInView(fingerOne->view());
        
        // The touch points are always in "portrait" coordinates - convert to landscape
        pointOne = CCDirector::sharedDirector()->convertToGL(pointOne);
        
        // Set the variable that stores the ending touch point
        endTouchPoint_ = pointOne;

        // Get the distance that the user's finger moved during this touch
        float distance = sqrt(pow(endTouchPoint_.x - startTouchPoint_.x, 2) + pow(endTouchPoint_.y - startTouchPoint_.y, 2));
        
        // If the distance moved (in pixels) is small enough, consider the gesture a tap
        if (distance < 5)
        {
            CCLog("Shoot!");
        }
        // Otherwise, it's a swipe
        else
        {
            // Use distance of swipe as a multiplier for the ship velocity (longer swipe, go faster)
            ship_->setVelocity(ccp(cos(CC_DEGREES_TO_RADIANS(ship_->getRotation())) * distance / 100, 
                                   -sin(CC_DEGREES_TO_RADIANS(ship_->getRotation())) * distance / 100));
        }
    }
}