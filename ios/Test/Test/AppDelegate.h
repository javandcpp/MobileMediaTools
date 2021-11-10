//
//  AppDelegate.h
//  Test
//
//  Created by developer on 2021/11/9.
//

#import <UIKit/UIKit.h>
#import <CoreData/CoreData.h>

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (readonly, strong) NSPersistentContainer *persistentContainer;
@property (nonatomic, strong) UIWindow * window;
- (void)saveContext;


@end

