//
//  HWCAduioCapture.m
//  Test
//
//  Created by developer on 2021/11/9.
//

#import "HWCAudioCapture.h"


@implementation HWCAudioCapture{
    NSLock *m_lock;
    AVCaptureDevice* audioDevice;
    AVCaptureDeviceInput* audioInput;
    AVCaptureAudioDataOutput* audioOutput;
    
    
}
-(instancetype)init{
    self=[super init];
    if(self){
        // 1. 创建视频输入设备 AVCaptureDevice -> AVCaptureDeviceInput
            audioDevice = nil;
           if (@available (iOS 10, *)) {
               audioDevice = [AVCaptureDevice defaultDeviceWithDeviceType:AVCaptureDeviceTypeBuiltInMicrophone mediaType:AVMediaTypeAudio position:AVCaptureDevicePositionUnspecified];
           } else {
               audioDevice = [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeAudio];
           }
           
           // 创建音频输入AVCaptureDeviceInput
           NSError * error = nil;
           audioInput = [[AVCaptureDeviceInput alloc] initWithDevice:audioDevice error:&error];
           if (error != nil) {
               NSLog(@"init AVCaptureDeviceInput failed");
           }
           
//
           // 3. 创建音频输出设备
           audioOutput = [[AVCaptureAudioDataOutput alloc] init];
        
          
    }
    return self;
}


-(AVCaptureDeviceInput*)getCaputureAudioDeviceInput{
    return audioInput;
}
-(AVCaptureAudioDataOutput*)getCaptureAduioDataOutput{
    return audioOutput;
}

@end
