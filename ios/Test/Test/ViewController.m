//
//  ViewController.m
//  Test
//
//  Created by developer on 2021/11/9.
//

#import "ViewController.h"
#import "HWCAVCapture.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [[[HWCAVCapture alloc] init] startCapture:MEDIA_AUDIO];
    // Do any additional setup after loading the view.
}


@end
