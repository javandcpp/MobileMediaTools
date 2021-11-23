//
//  HWCIOSAudioQueue.h
//  Test
//
//  Created by developer on 2021/11/23.
//

#import "HWCAVCaptureBase.h"
#import <AudioToolbox/AudioToolbox.h>
#import <CoreAudio/CoreAudioTypes.h>

NS_ASSUME_NONNULL_BEGIN

@interface HWCIOSAudioQueue : HWCAVCaptureBase

-(void)start;

-(void)stop;
@end

NS_ASSUME_NONNULL_END
