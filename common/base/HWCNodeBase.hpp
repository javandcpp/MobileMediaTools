//
//  EncoderNodeBase.hpp
//  Test
//{
//    "streams":[
//    {"name":"process_audio","stream":"audiodenoise"},
//    {"name":"process_video","stream":"videobeauty"}
//    ]
//},
//{
//    "encoders":[
//    {"name":"encoder","stream":"audio","type":"mp3"},
//    {"name":"encoder","stream":"video","type":"h264"}
//    ]
//
//},
//{
//    "muxers":[
//    {"name":"muxer","stream":"audio-video","type":"mp4"}
//    ]
//}
//
//  Created by developer on 2021/11/9.
//

#ifndef EncoderNodeBase_hpp
#define EncoderNodeBase_hpp

#include <stdio.h>
#include "HWCAVStruct.hpp"


class HWCNodeBase{
    
public:
    virtual ~HWCNodeBase(){};
    
    virtual void inputData(AVFrameData* data){};
    virtual void outputData(AVFrameData* data){};
    
    std::shared_ptr<HWCNodeBase> sink;//输入节点
    std::shared_ptr<HWCNodeBase> source;//输出节点，下游分发数据
    
    std::mutex m_Mutex_in;
    std::mutex m_Mutex_out;
    
    std::string name;
    int mStreamType;
    int mEncoderType;
    
};


#endif /* EncoderNodeBase_hpp */
