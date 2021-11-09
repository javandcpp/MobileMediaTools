//
//  HWCAVCapture.h
//  Test
//
//  Created by developer on 2021/11/9.
//

#import <Foundation/Foundation.h>
#import "Define.h"


NS_ASSUME_NONNULL_BEGIN



@interface HWCAVCaptureBase : NSObject


-(void)createPipe;

-(void)startCapture:(CaptureType)captureType;

-(void)stopCapture;

-(void)releasePipe;

@end

NS_ASSUME_NONNULL_END
