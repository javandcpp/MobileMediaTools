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


using namespace std;
@implementation HWCAVCapture{
    std::shared_ptr<HWCPipeInfo> pipeInfo;
    std::shared_ptr<HWCPipe> pipe;
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

@end
