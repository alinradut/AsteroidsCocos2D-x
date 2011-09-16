//
//  AppController.h
//  Asteroids
//
//  Created by Clawoo on 9/16/11.
//  Copyright __MyCompanyName__ 2011. All rights reserved.
//

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController	*viewController;
}

@end

