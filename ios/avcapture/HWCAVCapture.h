//
//  HWCAVCapture.h
//  Test
//
//  Created by developer on 2021/11/9.
//

#import <Foundation/Foundation.h>
#import "Define.hpp"
#import "HWCAudioCapture.h"
#import "HWCVideoCapture.h"
#import <AVFoundation/AVFoundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef enum{
    MEDIA_VIDEO=0,MEDIA_AUDIO
}MediaType;

@interface HWCAVCapture : NSObject <AVCaptureVideoDataOutputSampleBufferDelegate,AVCaptureAudioDataOutputSampleBufferDelegate>

@property(nonatomic,strong)AVCaptureVideoPreviewLayer* previewLayer;

-(void)startCapture:(MediaType)type;

-(void)stopCapture;

- (AVCaptureVideoPreviewLayer*)setupPreviewLayer:(CGRect)frame;

@end

NS_ASSUME_NONNULL_END
