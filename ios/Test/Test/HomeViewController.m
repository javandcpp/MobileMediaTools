//
//  HomeViewController.m
//  IOSIjkMediaplayer
//
//  Created by developer on 2020/9/24.
//  Copyright © 2020 developer. All rights reserved.
//

#import "HomeViewController.h"
#import "ViewController.h"
//#import "RoundTextView.h"
#import "HWCAVCapture.h"

#define BUTTON_WIDTH    100
#define BUTTON_HEIGHT   50

#define SCREEN_WIDTH ([[UIScreen mainScreen] bounds].size.width)
#define SCREEN_HEIGHT ([[UIScreen mainScreen] bounds].size.height)
@interface HomeViewController (){
 

    CGFloat _windowWidth;
    CGFloat _windowHeight;
    ViewController *vc;
    
    HWCAVCapture *capture;
}

@end

@implementation HomeViewController

-(void)dealloc{
    if(capture){
        capture=nil;
    }
}

- (void)viewDidLoad {
    [super viewDidLoad];

    capture=[[HWCAVCapture alloc] init];
    [capture startCapture:2];

    
//    [self.view setBackgroundColor:[UIColor redColor]];
//
//
//    _btnAudioPlayer=[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 200, 100)];
//    [_btnAudioPlayer setBackgroundColor:[UIColor redColor]];
//    [_btnAudioPlayer setTitle:@"Skip" forState:UIControlStateNormal];
//    [self.view addSubview:_btnVideoPlayer];
    
    
//    [_btnAudioPlayer mas_makeConstraints:^(MASConstraintMaker *make) {
//        make.centerY.equalTo(self.view);
//        make.left.equalTo(self.view).mas_offset(10);
//        make.right.equalTo(self.btnVideoPlayer.mas_left).mas_offset(-10);
//        make.height.mas_equalTo(BUTTON_HEIGHT);
//    }];

    
//    [_btnAudioPlayer addTarget:self action:@selector(audio:) forControlEvents:UIControlEventTouchUpInside];
  

    
    
    
    
}

-(void)audio:(UIButton*)btn{
//    [audiovc removeFromParentViewController];
//    audiovc=[[PlayerViewController alloc] init];
//    [self.navigationController pushViewController:audiovc animated:YES];
}

-(void)video:(UIButton*)btn{
  
    vc=[[ViewController alloc] init];
    [self.navigationController pushViewController:vc animated:YES];
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
