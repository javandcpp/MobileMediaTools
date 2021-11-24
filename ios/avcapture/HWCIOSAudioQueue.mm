//
//  HWCIOSAudioQueue.m
//  Test
//
//  Created by developer on 2021/11/23.
//

#import "HWCIOSAudioQueue.h"
#include <AVFoundation/AVFoundation.h>

static const int kNumberBuffers = 3;

typedef struct AQCallbackStruct
{
    AudioStreamBasicDescription mDataFormat;
    AudioQueueRef               queue;
    AudioQueueBufferRef         mBuffers[kNumberBuffers];
    AudioFileID                 outputFile;
    uint32_t                    bufferByteSize;
    uint32_t                    frameSize;
    long long                   recPtr;
    int                         run;
    
    
} AQCallbackStruct;

@interface HWCIOSAudioQueue(){
    AQCallbackStruct aqc;
    AudioFileTypeID fileFormat;
    long audioDataLength;
    Byte audioByte[999999];
    long audioDataIndex;
    BOOL                        isRecording;
    uint64_t audioTimeStamp;
    
    NSString *pcmPath;
    FILE *fp;
}
@end


@implementation HWCIOSAudioQueue

//typedef void (*AudioQueueInputCallback)(
//                                    void * __nullable               inUserData,
//                                    AudioQueueRef                   inAQ,
//                                    AudioQueueBufferRef             inBuffer,
//                                    const AudioTimeStamp *          inStartTime,
//                                    UInt32                          inNumberPacketDescriptions,
//                                    const AudioStreamPacketDescription * __nullable inPacketDescs);
static void AQInputCallback (void                   * inUserData,
                             AudioQueueRef          inAudioQueue,
                             AudioQueueBufferRef    inBuffer,
                             const AudioTimeStamp   * inStartTime,
                             UInt32          inNumPackets,
                             const AudioStreamPacketDescription * inPacketDesc)
{
    
    HWCIOSAudioQueue * engine = (__bridge HWCIOSAudioQueue *) inUserData;
    if (inNumPackets > 0)
    {
        [engine processAudioBuffer:inBuffer withQueue:inAudioQueue];
    }
    
    if (engine->aqc.run)
    {
        AudioQueueEnqueueBuffer(engine->aqc.queue, inBuffer, 0,NULL);
    }
}


void DeriveBufferSize (AudioQueueRef audioQueue,AudioStreamBasicDescription *ASBDescription, Float64 seconds,UInt32                       *outBufferSize) {
    static const int maxBufferSize = 0x50000;
    
    int maxPacketSize = (*ASBDescription).mBytesPerPacket;
    if (maxPacketSize == 0) {
        UInt32 maxVBRPacketSize = sizeof(maxPacketSize);
        AudioQueueGetProperty(audioQueue,kAudioQueueProperty_MaximumOutputPacketSize,&maxPacketSize,&maxVBRPacketSize);
    }
    
    Float64 numBytesForTime =
    (*ASBDescription).mSampleRate * maxPacketSize * seconds;
    *outBufferSize = numBytesForTime < maxBufferSize ? numBytesForTime : maxBufferSize;
}


#define kDefaultBufferDurationSeconds 0.027

-(instancetype)init{
    self=[super init];
    if(self){
        
        aqc.mDataFormat.mSampleRate = 44100;
        aqc.mDataFormat.mFormatID = kAudioFormatLinearPCM;
        aqc.mDataFormat.mFormatFlags = kLinearPCMFormatFlagIsSignedInteger |kLinearPCMFormatFlagIsPacked;
        aqc.mDataFormat.mFramesPerPacket = 1;
        aqc.mDataFormat.mChannelsPerFrame = 2;
        aqc.mDataFormat.mBitsPerChannel = 16;
        aqc.mDataFormat.mBytesPerPacket = aqc.mDataFormat.mChannelsPerFrame*sizeof(uint16_t);
        aqc.mDataFormat.mBytesPerFrame = aqc.mDataFormat.mChannelsPerFrame*sizeof(uint16_t);;
        
        
        
        //        DeriveBufferSize(aqc.queue, &aqc.mDataFormat, 1,  &aqc.bufferByteSize);
        //        aqc.frameSize = aqc.bufferByteSize;
        
        AudioQueueNewInput(&aqc.mDataFormat, AQInputCallback, (__bridge void *)(self),NULL, kCFRunLoopCommonModes,0, &aqc.queue);
        
        //计算估算的缓存区大小
        int frames = (int)ceil(kDefaultBufferDurationSeconds * aqc.mDataFormat.mSampleRate);//返回大于或者等于指定表达式的最小整数
        int bufferByteSize = frames * aqc.mDataFormat.mBytesPerFrame;
        
        
        for (int i=0;i<kNumberBuffers;i++)
        {
            AudioQueueAllocateBuffer(aqc.queue, bufferByteSize, &aqc.mBuffers[i]);
            AudioQueueEnqueueBuffer(aqc.queue, aqc.mBuffers[i], 0,NULL);
        }
        aqc.recPtr = 0;
        aqc.run = 1;
        
        audioDataIndex = 0;
        
        
        
        //create test file
        NSString *documentPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) lastObject];
        NSLog(@"document文件夹路径为%@",documentPath);
        
        NSFileManager *fileManager = [NSFileManager defaultManager];
        NSString *testPath = [documentPath stringByAppendingPathComponent:@"test"];
        BOOL isSuccess = [fileManager createDirectoryAtPath:testPath withIntermediateDirectories:YES attributes:nil error:nil];
        NSLog(@"成功创建文件夹了吗：%@",isSuccess?@"yes":@"no");
        
        pcmPath = [testPath stringByAppendingPathComponent:@"test.pcm"];
        BOOL isPcmSuccess = [fileManager createFileAtPath:pcmPath contents:nil attributes:nil];
        NSLog(@"成功创建文件了吗：%@",isPcmSuccess?@"yes":@"no");
//        fp=fopen([pcmPath UTF8String], "wb+");
        
        
    }
    return self;
}

- (void)dealloc
{
    AudioQueueStop(aqc.queue,true);
    aqc.run = 0;
    AudioQueueDispose(aqc.queue,true);
}

- (void)start
{
    NSError *error = nil;
    
    
    //设置audio session的category
    BOOL ret = [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryPlayAndRecord error:&error];//注意，这里选的是AVAudioSessionCategoryPlayAndRecord参数，如果只需要录音，就选择Record就可以了，如果需要录音和播放，则选择PlayAndRecord，这个很重要
    if (!ret) {
        NSLog(@"设置声音环境失败");
        return;
    }
    //启用audio session
    ret = [[AVAudioSession sharedInstance] setActive:YES error:&error];
    if (!ret)
    {
        NSLog(@"启动失败");
        return;
    }
    AudioQueueStart(aqc.queue,NULL);
    self->isRecording = YES;
}

- (void)stop
{
    if (self->isRecording)
    {
        self->isRecording = NO;
        
        //停止录音队列和移除缓冲区,以及关闭session，这里无需考虑成功与否
        AudioQueueStop(aqc.queue, true);
        AudioQueueDispose(aqc.queue, true);//移除缓冲区,true代表立即结束录制，false代表将缓冲区处理完再结束
        [[AVAudioSession sharedInstance] setActive:NO error:nil];
    }
//    if(fp){
//        fclose(fp);
//    }
}

- (void)pause
{
    AudioQueuePause(aqc.queue);
}


- (void) processAudioBuffer:(AudioQueueBufferRef) buffer withQueue:(AudioQueueRef) queue
{
    
    //处理data：忘记oc怎么copy内存了，于是采用的C++代码，记得把类后缀改为.mm。同Play
    //    memcpy(audioByte+audioDataIndex, buffer->mAudioData, buffer->mAudioDataByteSize);
    //    audioDataIndex +=buffer->mAudioDataByteSize;
    //    audioDataLength = audioDataIndex;
    uint64_t pts= audioTimeStamp++ *(buffer->mAudioDataByteSize * 1000 / aqc.mDataFormat.mSampleRate);
    NSLog(@"audio pts:%llu  dataSize:%d", pts,buffer->mAudioDataByteSize);
    
//    NSData* data=[NSData dataWithBytes:buffer->mAudioData length:buffer->mAudioDataByteSize];
//    [data writeToFile:pcmPath atomically:YES];
//    fwrite(buffer->mAudioData, 1, buffer->mAudioDataByteSize, fp);


}


@end
