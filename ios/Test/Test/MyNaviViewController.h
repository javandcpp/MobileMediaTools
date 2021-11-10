//
//  MyNaviViewController.h
//  IOSIjkMediaplayer
//
//  Created by developer on 2020/7/6.
//  Copyright © 2020 developer. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN
@protocol NavigationControllerDelegate <NSObject>
@optional
- (BOOL) shouldPopOnBackButtonPress;
@end

@interface MyNaviViewController : UINavigationController

@end

NS_ASSUME_NONNULL_END
