//
//  MyNaviViewController.m
//  IOSIjkMediaplayer
//
//  Created by developer on 2020/7/6.
//  Copyright © 2020 developer. All rights reserved.
//

#import "MyNaviViewController.h"

@interface MyNaviViewController ()<UINavigationBarDelegate>

@end

@implementation MyNaviViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.navigationBar.alpha=0.300f;
    self.navigationBar.translucent =YES;
//    [self setNavigationBarHidden:YES animated:YES];
    // Do any additional setup after loading the view.
}

//支持旋转
//-(BOOL)shouldAutorotate{
//    return [self.topViewController shouldAutorotate];
//}

//支持的方向
- (UIInterfaceOrientationMask)supportedInterfaceOrientations {
    return [self.topViewController supportedInterfaceOrientations];
}


/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

- (BOOL) navigationBar:(UINavigationBar *)navigationBar shouldPopItem:(UINavigationItem *)item{
    BOOL shouldPop = YES;

    // 已修改（标记1）
    NSUInteger count = self.viewControllers.count;
    NSUInteger itemsCount = navigationBar.items.count;
    if(count < itemsCount){
        return shouldPop;
    }

   // 通过点击返回键和直接调用popViewController，得到的topViewController不同
    UIViewController *vc = self.topViewController;
    if([vc respondsToSelector:@selector(shouldPopOnBackButtonPress)]){
        shouldPop = [vc performSelector:@selector(shouldPopOnBackButtonPress)];
    }
    if(shouldPop == NO){
      // 返回NO后，返回按钮中的 < 会置灰（文字恢复为黑色）通过设置NavigationBarHidden属性使它恢复
        [self setNavigationBarHidden:YES];
        [self setNavigationBarHidden:NO];
    }else{
        // 不能直接调用pop,如果是通过popViewController调起,会造成循环调用此方法
        // 如果是通过调用[navigationController popViewControllerAnimated:]导致的shouldPop delegate被调用,
        // 此时已经完成了viewController的pop, viewControllers.count 会比 navigationBar.items.count小1
        // 这种情况就不必再次调用popViewController，否则会导致循环
        if(count >= itemsCount){
            dispatch_async(dispatch_get_main_queue(), ^{
                [self popViewControllerAnimated: YES];
              
        
            });
        }
        
        
    }

    return shouldPop;
}

@end
