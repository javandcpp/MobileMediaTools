//
//  HWCVideoCapture.h
//  Test
//
//  Created by developer on 2021/11/9.
//

#import "HWCAVCaptureBase.h"
#import <AVFoundation/AVFoundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface HWCVideoCapture : HWCAVCaptureBase
-(AVCaptureDeviceInput*)getCaputureVideoDeviceInput;
-(AVCaptureVideoDataOutput*)getCaptureVideoDataOutput;
@end

NS_ASSUME_NONNULL_END
