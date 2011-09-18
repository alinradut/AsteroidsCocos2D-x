//
//  TitleLayer.cpp
//  Asteroids
//
//  Created by Clawoo on 9/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "TitleLayer.h"
#include "GameLayer.h"
#include "ScoresLayer.h"
#include "ControlsLayer.h"

USING_NS_CC;

CCScene* TitleLayer::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();
	
	// 'layer' is an autorelease object
	TitleLayer *layer = TitleLayer::node();
    
	// add layer as a child to scene
	scene->addChild(layer);
    
	// return the scene
	return scene;
}

bool TitleLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
    
    // Get window size
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
    
    // Create text label for title of game - "@stroids" - don't sue me Atari!
    CCLabelTTF *title = CCLabelTTF::labelWithString("@stroids", "Courier", 64.0);
    
    // Position title at center of screen
    title->setPosition(ccp(windowSize.width / 2, windowSize.height/2));
    
    // Add to layer
    this->addChild(title, 1);
    
    // Set the default CCMenuItemFont font
    CCMenuItemFont::setFontName("Courier");
    
    // Create "play," "scores," and "controls" buttons - when tapped, they call methods we define: playButtonAction and scoresButtonAction
    CCMenuItemFont *playButton = CCMenuItemFont::itemFromString("play", this, menu_selector(TitleLayer::playButtonAction));
    CCMenuItemFont *scoresButton = CCMenuItemFont::itemFromString("scores", this, menu_selector(TitleLayer::scoresButtonAction));
    CCMenuItemFont *controlsButton = CCMenuItemFont::itemFromString("controls", this, menu_selector(TitleLayer::controlsButtonAction));
    
    // Create menu that contains our buttons
    CCMenu *menu = CCMenu::menuWithItems(playButton, scoresButton, controlsButton, NULL);

    // Align buttons horizontally
    menu->alignItemsHorizontallyWithPadding(20);
    
    // Set position of menu to be below the title text
    menu->setPosition(ccp(windowSize.width / 2, title->getPosition().y - title->getContentSize().height / 1.5));

    // Add menu to layer
    this->addChild(menu, 2);
        
	return true;
}

void TitleLayer::playButtonAction(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(GameLayer::scene());
}

void TitleLayer::scoresButtonAction(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(ScoresLayer::scene());
}

void TitleLayer::controlsButtonAction(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(ControlsLayer::scene());
}