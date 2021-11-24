//
//  HWCAVCapture.m
//  Test
//
//  Created by developer on 2021/11/9.
//

#import "HWCAVCapture.h"
#include "HWCPipe.hpp"
#include "HWCPipeParser.hpp"
#include "HWCPipeNodeRegister.hpp"
#include "Log.h"
#include <thread>
#include <chrono>
#import "HWCVideoCapture.h"
#import "HWCAudioCapture.h"
#import "HWCIOSAudioQueue.h"





using namespace std;
@implementation HWCAVCapture{
    NSLock* _lock;
    std::shared_ptr<HWCPipeInfo> pipeInfo;
    std::shared_ptr<HWCPipe> pipe;
    AVCaptureSession* captureSession;
    dispatch_queue_t  captureSessionQueue;
    HWCVideoCapture* videoCapture;
    HWCAudioCapture* audioCapture;
    AVCaptureConnection *videoConnection;
    AVCaptureConnection *audioConnection;
    HWCIOSAudioQueue*    audioQueue;
    MediaType mediaType;
    uint64_t videoPts;
    NSString *yuvPath;
    FILE    *fp;
}
-(void)setupSession{
    captureSession = [[AVCaptureSession alloc] init];
    // 2.设置分辨率 分辨率与编码时候的宽和高有关系
    if ([captureSession canSetSessionPreset:AVCaptureSessionPreset1280x720]) {
        captureSession.sessionPreset=AVCaptureSessionPreset1280x720;
    }else{
        captureSession.sessionPreset=AVCaptureSessionPresetMedium;
    }
    // 3. 创建Session队列
    captureSessionQueue = dispatch_queue_create("captureSession queue", DISPATCH_QUEUE_SERIAL);
}

-(void)initVideoCapture{
    videoCapture=[[HWCVideoCapture alloc] init];
    //添加视频输入设备
    AVCaptureDeviceInput* videoInput=[videoCapture getCaputureVideoDeviceInput];
    
    
    if ([captureSession canAddInput:videoInput]) {
        [captureSession addInput:videoInput];
    }
    
    AVCaptureVideoDataOutput* videoOutput=[videoCapture getCaptureVideoDataOutput];
    //设置视频输出代理和队列
    dispatch_queue_t videoQueue = dispatch_queue_create("video output queue", DISPATCH_QUEUE_SERIAL);
    [videoOutput setSampleBufferDelegate:self queue:videoQueue];
    
    //添加视频输出设备
    if ([captureSession canAddOutput:videoOutput]) {
        [captureSession addOutput:videoOutput];
    }
    
    //    设置视频输出连接AVCaptureConnection
    videoConnection = [videoOutput connectionWithMediaType:AVMediaTypeVideo];
    
    //设置视频输出方向
    [videoConnection setVideoOrientation:AVCaptureVideoOrientationPortrait];
    
    //判断是否支撑视频稳定 可以显著提高视频的质量 只会在录制视频文件涉及到
    if ([videoConnection isVideoStabilizationSupported]) {
        videoConnection.preferredVideoStabilizationMode = AVCaptureVideoStabilizationModeAuto;
    }
}
-(void)initAudioQueue{
    audioQueue=[[HWCIOSAudioQueue alloc] init];
}
-(void)initAudioCapture{
    audioCapture=[[HWCAudioCapture alloc] init];
    
    AVCaptureDeviceInput *audioInput=[audioCapture getCaputureAudioDeviceInput];
    // 2.添加音频输入设备
    if ([captureSession canAddInput:audioInput]) {
        [captureSession addInput:audioInput];
    }
    
    AVCaptureAudioDataOutput* audioOutput=[audioCapture getCaptureAduioDataOutput];
    // 4. 设置音频代理和队列
    dispatch_queue_t audioQueue = dispatch_queue_create("audio output queue", DISPATCH_QUEUE_SERIAL);
    [audioOutput setSampleBufferDelegate:self queue:audioQueue];
    
    // 5. 添加音频输出设备
    if ([captureSession canAddOutput:audioOutput]) {
        [captureSession addOutput:audioOutput];
        
    }
    
    
    // 6.设置音频输出连接
    audioConnection = [audioOutput connectionWithMediaType:AVMediaTypeAudio];
    
}

- (AVCaptureVideoPreviewLayer*)setupPreviewLayer:(CGRect)frame {
    self.previewLayer = [[AVCaptureVideoPreviewLayer alloc] initWithSession:captureSession];
    self.previewLayer.frame = frame;
    self.previewLayer.videoGravity = AVLayerVideoGravityResizeAspectFill;
    return self.previewLayer;
}

-(instancetype)init{
    self =[super init];
    if(self){
        auto start = std::chrono::steady_clock::now();
        _lock=[[NSLock alloc] init];
        
        self->captureSession=nil;
        self->captureSessionQueue=nil;
        
        [self setupSession];
        [self initVideoCapture];
        
        //AudioCapture & AudioQueue
        //        [self initAudioCapture];
        
        [self initAudioQueue];
        
        
        
        HWCPipeNodeRegister::getInstance().avRegisterAllNode();
        NSString *path=[[NSBundle mainBundle] pathForResource:@"mediaconfig" ofType:@"json"];
        NSError *error;
        NSString *contents=[NSString stringWithContentsOfFile:path encoding:NSUTF8StringEncoding error:&error];
        if (contents!=nil) {
            
            pipeInfo=HWCPipeParser::parser([contents UTF8String]);
            pipe=std::make_shared<HWCPipe>();
            pipe->createPipe(pipeInfo.get());
            pipe->registerEventBus(pipeInfo.get());
            //            auto end = std::chrono::steady_clock::now();
            //            std::chrono::duration<double, std::milli> elapsed = end - start; // std::micro 表示以微秒为时间单位
            //            std::cout<< "time: "  << elapsed.count() << "ms" << std::endl;
            
            
        }
        
        
        NSString *documentPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) lastObject];
        NSLog(@"document文件夹路径为%@",documentPath);
        
        NSFileManager *fileManager = [NSFileManager defaultManager];
        NSString *testPath = [documentPath stringByAppendingPathComponent:@"test"];
        BOOL isSuccess = [fileManager createDirectoryAtPath:testPath withIntermediateDirectories:YES attributes:nil error:nil];
        NSLog(@"成功创建文件夹了吗：%@",isSuccess?@"yes":@"no");
        
        yuvPath = [testPath stringByAppendingPathComponent:@"test.yuv"];
        BOOL isPcmSuccess = [fileManager createFileAtPath:yuvPath contents:nil attributes:nil];
        NSLog(@"成功创建文件了吗：%@",isPcmSuccess?@"yes":@"no");
//        fp=fopen([yuvPath UTF8String], "wb+");
    }
    return self;
}

-(void)dealloc{
    if(pipe){
        pipe->unRegisterEventBus();
        pipe.reset();
    }
    if(pipeInfo){
        pipeInfo.reset();
    }
    
}

-(void)startCapture:(MediaType)type{
    if(self->captureSession&&self->captureSessionQueue){
        
        [self->audioQueue start];
        mediaType=type;
        dispatch_async(captureSessionQueue, ^{
            [self->_lock lock];
            if (![self->captureSession isRunning]) {
                [self->captureSession startRunning];
            }
            [self->_lock unlock];
        });
    }
}

-(void)stopCapture{
    if(self->captureSession&&self->captureSessionQueue){
        dispatch_async(captureSessionQueue, ^{
            [self->_lock lock];
            if ([self->captureSession isRunning]) {
                [self->captureSession stopRunning];
            }
            [self->_lock unlock];
        });
    }
    
    [audioQueue stop];
    
}

- (uint8_t *)convertAudioSmapleBufferToPcmData:(CMSampleBufferRef) audioSampleBuffer{
    size_t size=CMSampleBufferGetTotalSampleSize(audioSampleBuffer);
    uint8_t* audio_data=(uint8_t*)malloc(size);
    memset(audio_data, 0, size);
    CMBlockBufferRef blockBuffer=CMSampleBufferGetDataBuffer(audioSampleBuffer);
    CMBlockBufferCopyDataBytes(blockBuffer, 0, size, audio_data);
    return audio_data;
}

-(uint8_t*)convertVideoSampleBufferNV12ToYUVI420Data:(CMSampleBufferRef)sampleBuffer{
    CVImageBufferRef imageBuffer =CMSampleBufferGetImageBuffer(sampleBuffer);
    CVPixelBufferLockBaseAddress(imageBuffer,0);
    CMTime pts =CMSampleBufferGetPresentationTimeStamp(sampleBuffer);
    CMTime duration =CMSampleBufferGetDuration(sampleBuffer);
    void *imageAddress = CVPixelBufferGetBaseAddressOfPlane(imageBuffer,0);//YYYYYYYY
    size_t row0=CVPixelBufferGetBytesPerRowOfPlane(imageBuffer,0);
    
    void *imageAddress1=CVPixelBufferGetBaseAddressOfPlane(imageBuffer,1);//UVUVUVUV
    
    size_t row1=CVPixelBufferGetBytesPerRowOfPlane(imageBuffer,1);
    size_t width =CVPixelBufferGetWidth(imageBuffer);
    size_t height =CVPixelBufferGetHeight(imageBuffer);
    
    
    
    CVPixelBufferUnlockBaseAddress(imageBuffer,0);
    
    size_t a=width*height;
    
    //开始将NV12转换成YUV420
    
    uint8_t *yuv420Data=(uint8_t*)malloc(a*1.5);
    
    for (int i=0; i<height; ++i) {
        
        memcpy(yuv420Data+i*width, ((uint8_t*)imageAddress)+i*row0, width);
        
    }
    
    uint8_t *UV=(uint8_t*)imageAddress1;
    
    uint8_t *U=yuv420Data+a;
    
    uint8_t *V=U+a/4;
    
    for (int i=0; i<0.5*height; i++) {
        
        for (int j=0; j<0.5*width; j++) {
            
            *(U++)=UV[j<<1];
            
            *(V++)=UV[(j<<1)+1];
            
        }
        
        UV+=row1;
        
    }
  //  fwrite(yuv420Data, 1, a*1.5, fp);
    return yuv420Data;
}

- (uint8_t *)convertVideoSmapleBufferToYuvData:(CMSampleBufferRef) videoSample{
    CVImageBufferRef pixelBuffer = CMSampleBufferGetImageBuffer(videoSample);
    CVPixelBufferLockBaseAddress(pixelBuffer, 0);
    size_t pixelWidth = CVPixelBufferGetWidth(pixelBuffer);
    size_t pixelHeight = CVPixelBufferGetHeight(pixelBuffer);
    size_t y_size = pixelWidth * pixelHeight;
    size_t uv_size = y_size / 2;
    
    uint8_t *yuv_frame = (uint8_t*)malloc(uv_size + y_size);
    memset(yuv_frame, 0, uv_size+y_size);
    //获取CVImageBufferRef中的y数据
    uint8_t *y_frame = (uint8_t*)CVPixelBufferGetBaseAddressOfPlane(pixelBuffer, 0);
    memcpy(yuv_frame, y_frame, y_size);
    //获取CMVImageBufferRef中的uv数据
    uint8_t *uv_frame = (uint8_t*)CVPixelBufferGetBaseAddressOfPlane(pixelBuffer, 1);
    
    memcpy(yuv_frame + y_size, uv_frame, uv_size);
    
    CVPixelBufferUnlockBaseAddress(pixelBuffer, 0);
    
    return yuv_frame;
    
    //返回数据
    
    //    return [NSData dataWithBytesNoCopy:yuv_frame length:y_size + uv_size];
    
}


- (void)captureOutput:(AVCaptureOutput *)output didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection{
    
    // 判断音频还是视频
    // 视频
    if ([connection isEqual:videoConnection]) {
        
        uint64_t pts = videoPts++ *(1000/30);
        NSLog(@"video pts:%llu", pts);
        uint8_t* yuv=[self convertVideoSampleBufferNV12ToYUVI420Data:sampleBuffer];
        //        free(yuv);

        
        std::shared_ptr<AVFrameData> dataSharedPtr=std::make_shared<AVFrameData>();
        dataSharedPtr->data=yuv;
        dataSharedPtr->stream_type=VIDEO_STREAM_TYPE;
    }
    
    // 音频
    if ([connection isEqual:audioConnection]) {
        NSLog(@"audio sampleBuffer%@", sampleBuffer);
        uint8_t* pcm=[self convertAudioSmapleBufferToPcmData:sampleBuffer];
        std::shared_ptr<AVFrameData> dataSharedPtr=std::make_shared<AVFrameData>();
        dataSharedPtr->data=pcm;
        dataSharedPtr->stream_type=AUDIO_STREAM_TYPE;
        //        free(pcm);
    }
    
    //        // 视频
    //        if ([output isEqual:self.videoDataOutput]) {
    //
    //        }
    //
    //        // 音频
    //        if ([output isEqual:self.audioDataOutput]) {
    //
    //        }
}


- (void)captureOutput:(AVCaptureFileOutput *)captureOutput didFinishRecordingToOutputFileAtURL:(NSURL *)outputFileURL fromConnections:(NSArray *)connections error:(NSError *)error
{
    NSLog(@"---- 录制结束 ----");
//    if(fp){
//        fclose(fp);
//    }
}
@end
