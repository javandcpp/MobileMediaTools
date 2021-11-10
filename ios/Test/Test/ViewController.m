//
//  ViewController.m
//  Test
//
//  Created by developer on 2021/11/9.
//

#import "ViewController.h"
#import "HWCAVCapture.h"
#import "HomeViewController.h"

@interface ViewController (){
    UIButton* _btnAudioPlayer;
    HomeViewController* vc;
}

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    _btnAudioPlayer=[[UIButton alloc] initWithFrame:CGRectMake(100, 100, 100, 80)];
    [_btnAudioPlayer setBackgroundColor:[UIColor blackColor]];
    [_btnAudioPlayer setTitle:@"start" forState:UIControlStateNormal];

    [self.view addSubview:_btnAudioPlayer];
    
    [_btnAudioPlayer addTarget:self action:@selector(video:) forControlEvents:UIControlEventTouchUpInside];
//    [[[HWCAVCapture alloc] init] startCapture:MEDIA_AUDIO];
    // Do any additional setup after loading the view.
}
-(void)video:(UIButton*)btn{
    vc=nil;
    vc=[[HomeViewController alloc] init];
    [self.navigationController pushViewController:vc animated:YES];
}

@end
