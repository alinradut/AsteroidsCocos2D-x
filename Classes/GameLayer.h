//
//  GameLayer.h
//  Asteroids
//
//  Created by Clawoo on 9/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "cocos2d.h"
#include "Ship.h"

class GameLayer : public cocos2d::CCLayer
{
public:
    ~GameLayer();
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
    void update(cocos2d::ccTime dt);
    
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
    
	// implement the "static node()" method manually
	LAYER_NODE_FUNC(GameLayer);
    
    cocos2d::CCMutableArray<cocos2d::CCTouch *>* allTouchesFromSet(cocos2d::CCSet *touches);
    virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);

    void createAsteroidAt(cocos2d::CCPoint position , int size);
    void createBullet();
    void startLevel();
    void resetShip();
    void gameOver();
    void backButtonAction(CCObject* pSender);

private:
    Ship *ship_;
	// To determine rotation
	float previousTouchAngle_, currentTouchAngle_;
    
	// To determine movement/shooting
    cocos2d::CCPoint startTouchPoint_, endTouchPoint_;
    
    // Arrays used to keep track of all visible asteroids/bullets
    cocos2d::CCMutableArray<cocos2d::CCSprite *> *asteroids_;
    cocos2d::CCMutableArray<cocos2d::CCSprite *> *bullets_;
    
    // Used to determine the number of asteroids that appear
    int currentLevel_;
};

#endif // __GAMELAYER_H__
