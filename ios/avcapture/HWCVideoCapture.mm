//
//  HWCVideoCapture.m
//  Test
//
//  Created by developer on 2021/11/9.
//

#import "HWCVideoCapture.h"

@implementation HWCVideoCapture{
    NSLock *m_lock;
    AVCaptureDevice* videoDevice;
    AVCaptureDeviceInput* videoInput;
    AVCaptureVideoDataOutput* videoOutput;
    NSString *yuvPath;

    
}

-(instancetype)init{
    self=[super init];
    if(self){
        //input
        //获取视频设备管理对象 （由于分为前置摄像头 和 后置摄像头 所以返回的是数组）
        videoDevice=nil;
        //        NSArray *videoDevices=[[NSArray alloc] init];
        //        AVCaptureDeviceDiscoverySession *captureDeviceDiscoverySession = [AVCaptureDeviceDiscoverySession discoverySessionWithDeviceTypes:@[AVCaptureDeviceTypeBuiltInWideAngleCamera]
        //                                              mediaType:AVMediaTypeVideo
        //                                               position: AVCaptureDevicePositionUnspecified]; // here you pass AVCaptureDevicePositionUnspecified to find all capture devices
        //
        //        NSArray *captureDevices = [captureDeviceDiscoverySession devices];
        //
        //      //  [AVCaptureDevice devicesWithMediaType:AVMediaTypeVideo];
        //        for (AVCaptureDevice *device in captureDevices) {
        //            ///默认先开启前置摄像头
        //            if (device.position == AVCaptureDevicePositionFront) {//AVCaptureDevicePositionBack 后置
        //                videoDevice = device;
        //            }
        //        }
        //        //如果前置没有，取后置
        //        if(videoDevice==nil){
        //            for (AVCaptureDevice *device in captureDevices) {
        //                ///默认先开启前置摄像头
        //                if (device.position == AVCaptureDevicePositionBack) {//AVCaptureDevicePositionBack 后置
        //                    videoDevice = device;
        //                }
        //            }
        //        }
        
        //根据视频设备来初始化视频输入对象
        if (@available (iOS 10, *)) {
            videoDevice = [AVCaptureDevice defaultDeviceWithDeviceType:AVCaptureDeviceTypeBuiltInWideAngleCamera mediaType:AVMediaTypeVideo position:AVCaptureDevicePositionFront];
            
        } else {
            videoDevice = [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo];
        }
        
        //设置帧率
        NSError *error;
        
        CMTime frameDuration = CMTimeMake(1, 30);

           BOOL frameRateSupported = NO;
           
           for (AVFrameRateRange *range in [videoDevice.activeFormat videoSupportedFrameRateRanges]) {
               if (CMTIME_COMPARE_INLINE(frameDuration, >=, range.minFrameDuration) &&
                   CMTIME_COMPARE_INLINE(frameDuration, <=, range.maxFrameDuration)) {
                   CMTimeShow(range.maxFrameDuration);
                   CMTimeShow(range.minFrameDuration);
                   
                   frameRateSupported = YES;
               }
           }
           
           if (frameRateSupported && [videoDevice lockForConfiguration:&error]) {
               [videoDevice setActiveVideoMaxFrameDuration:frameDuration];
               [videoDevice setActiveVideoMinFrameDuration:frameDuration];
               [videoDevice unlockForConfiguration];
           }

        
        
        videoInput = [[AVCaptureDeviceInput alloc] initWithDevice:videoDevice error:&error];
        if (error) {
            NSLog(@"摄像头错误");
            return self;
        }
        
        
        //        self.activeDeviceInput = videoInput;
        
        // 2.AVCaptureSession 添加视频输入设备
        //           if ([self.captureSession canAddInput:videoInput]) {
        //               [self.captureSession addInput:videoInput];
        //           }
        
        // 3. 创建视频输出设备
        videoOutput = [[AVCaptureVideoDataOutput alloc] init];
        // 4. 设置视频输出格式 YUV420
        videoOutput.videoSettings = [NSDictionary dictionaryWithObject:[NSNumber numberWithInt:kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange] forKey:(id)kCVPixelBufferPixelFormatTypeKey];
        
        // 5. 是否丢弃延时帧
        [videoOutput setAlwaysDiscardsLateVideoFrames:YES];
        
        // 6. 设置视频输出代理和队列
        //        dispatch_queue_t videoQueue = dispatch_queue_create("video output queue", DISPATCH_QUEUE_SERIAL);
        
        //        [videoOutput setSampleBufferDelegate:self queue:videoQueue];
        
        //        // 将输入对象添加到管理者 AVCaptureSession 中
        //        // 需要先判断是否能够添加输入对象
        //        if ([self.session canAddInput:self.videoInput]) {
        //            [self.session addInput:self.videoInput];
        //        }
        
        //output
        //视频输出对象
        //        videoOutput = [[AVCaptureVideoDataOutput alloc] init];
        //是否允许卡顿时丢帧
        //        videoOutput.alwaysDiscardsLateVideoFrames = NO;
        
        //        if ([self supportsFastTextureUpload]) {
        // 是否支持全频色彩编码 YUV 一种色彩编码方式, 即YCbCr, 现在视频一般采用该颜色空间, 可以分离亮度跟色彩, 在不影响清晰度的情况下来压缩视频
        //        BOOL supportFullYUVRange = NO;
        //
        //        // 获取输出对象所支持的像素格式
        //        NSArray *supportedPixelFormats = videoOutput.availableVideoCVPixelFormatTypes;
        //        for (NSNumber *currentPixelFormat in supportedPixelFormats) {
        //            if ([currentPixelFormat integerValue] == kCVPixelFormatType_420YpCbCr8BiPlanarFullRange) {
        //                supportFullYUVRange = YES;
        //            }
        //        }
        //
        //        // 根据是否支持全频色彩编码 YUV 来设置输出对象的视频像素压缩格式
        //        if (supportFullYUVRange) {
        //            [videoOutput setVideoSettings:[NSDictionary dictionaryWithObject:[NSNumber numberWithInt:kCVPixelFormatType_420YpCbCr8BiPlanarFullRange] forKey:(id)kCVPixelBufferPixelFormatTypeKey]];
        //        } else {
        //            [videoOutput setVideoSettings:[NSDictionary dictionaryWithObject:[NSNumber numberWithInt:kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange] forKey:(id)kCVPixelBufferPixelFormatTypeKey]];
        //        }
        //        }
        //        else {//BGRA
        //            [videoOutput setVideoSettings:[NSDictionary dictionaryWithObject:[NSNumber numberWithInt:kCVPixelFormatType_32BGRA] forKey:(id)kCVPixelBufferPixelFormatTypeKey]];
        //        }
        
        // 创建设置代理是所需要的线程队列 优先级设为高
        //        dispatch_queue_t videoQueue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0);
        //        // 设置代理
        //        [videoOutput setSampleBufferDelegate:self queue:videoQueue];
        
      
        
    }
    return self;
}
-(AVCaptureDeviceInput*)getCaputureVideoDeviceInput{
    return videoInput;
}
-(AVCaptureVideoDataOutput*)getCaptureVideoDataOutput{
    return videoOutput;
}


@end
