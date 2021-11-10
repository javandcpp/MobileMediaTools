//
//  HomeViewController.h
//  IOSIjkMediaplayer
//
//  Created by developer on 2020/9/24.
//  Copyright © 2020 developer. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface HomeViewController : UIViewController

@property(nonatomic,strong)UIButton *btnAudioPlayer;
@property(nonatomic,strong)UIButton *btnVideoPlayer;
@property(nonatomic,strong)UIButton *btnFFmpeg;
@end

NS_ASSUME_NONNULL_END
