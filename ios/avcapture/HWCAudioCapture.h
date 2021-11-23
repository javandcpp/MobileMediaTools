//
//  HWCAduioCapture.h
//  Test
//
//  Created by developer on 2021/11/9.
//

#import "HWCAVCaptureBase.h"
#import <AVFoundation/AVFoundation.h>
NS_ASSUME_NONNULL_BEGIN

@interface HWCAudioCapture : HWCAVCaptureBase


//AVCaptureDeviceInput* audioInput;
//AVCaptureAudioDataOutput* audioOutput;
-(AVCaptureDeviceInput*)getCaputureAudioDeviceInput;
-(AVCaptureAudioDataOutput*)getCaptureAduioDataOutput;

@end

NS_ASSUME_NONNULL_END
