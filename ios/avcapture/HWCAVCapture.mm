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
#import <AVFoundation/AVFoundation.h>
#import "HWCVideoCapture.h"
#import "HWCAudioCapture.h"





using namespace std;
@implementation HWCAVCapture{
    std::shared_ptr<HWCPipeInfo> pipeInfo;
    std::shared_ptr<HWCPipe> pipe;
    AVCaptureSession* captureSession;
    dispatch_queue_t  captureSessionQueue;
    HWCVideoCapture* videoCapture;
    HWCAudioCapture* audioCapture;
    AVCaptureConnection *videoConnection;
    AVCaptureConnection *audioConnection;
}
-(void)setupSession{
    captureSession = [[AVCaptureSession alloc] init];
    // 2.设置分辨率 分辨率与编码时候的宽和高有关系
    if ([captureSession canSetSessionPreset:AVCaptureSessionPresetHigh]) {
        captureSession.sessionPreset = AVCaptureSessionPresetHigh;
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

-(instancetype)init{
    self =[super init];
    if(self){
        auto start = std::chrono::steady_clock::now();
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
            
            
            //            session = [[AVCaptureSession alloc] init];
            
            // 设置分辨率
            //           [session canSetSessionPreset:[self supportSessionPreset]];
            //
            //            /**
            //             注意: 配置AVCaptureSession 的时候, 必须先开始配置, beginConfiguration, 配置完成, 必须提交配置 commitConfiguration, 否则配置无效
            //             **/
            //
            //            //开始配置
            //            [self.session beginConfiguration];
            //
            //            // 设置视频 I/O 对象 并添加到session
            //            [self videoInputAndOutput];
            //
            //            // 设置音频 I/O 对象 并添加到session
            //            [self audioInputAndOutput];
            //
            //            // 提交配置
            //            [self.session commitConfiguration];
            
        }
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

static void task(void* obj){
    
    
    HWCAVCapture* capture=(__bridge HWCAVCapture*)obj;
    
    
    
    for (int i=0; i<50; i++) {
        LOGD("send data");
        AVFrameData* dataAudio=new AVFrameData();
        dataAudio->stream_type=AUDIO_STREAM_TYPE;
        
        AVFrameData* dataVideo=new AVFrameData();
        dataVideo->stream_type=VIDEO_STREAM_TYPE;
        
        dataAudio->pts=i;
        capture->pipe->pipeTransportData(dataAudio);
        dataVideo->pts=i;
        capture->pipe->pipeTransportData(dataVideo);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        
        
        delete dataAudio;
        delete dataVideo;
    }
}

-(void)startCapture:(MediaType)type{
    
    HWCEvent event;
    event.eventType=EVENT_START;
    pipe->postSyncEvent(event);
    
    void* obj=(__bridge void*)self;
    //    std::thread t1(task,obj);
    //    t1.detach();
}

- (void)captureOutput:(AVCaptureOutput *)output didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection{
    
    
}
@end
