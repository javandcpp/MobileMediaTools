//
//  HWCAVCapture.h
//  Test
//
//  Created by developer on 2021/11/9.
//

#import <Foundation/Foundation.h>
#import "Define.h"

NS_ASSUME_NONNULL_BEGIN

@interface HWCAVCapture : NSObject

-(void)startCapture:(CaptureType)type;

-(void)stopCapture;
@end

NS_ASSUME_NONNULL_END
