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
#include "HWCEventBase.hpp"

#define LOG(x)   LOGD("create:"#x);

class HWCNodeBase:public HWCEventBase{
public:
    virtual void inputData(AVFrameData* data){};
    virtual void outputData(AVFrameData* data){};
    
    std::weak_ptr<HWCNodeBase> sink;//输入节点
    std::weak_ptr<HWCNodeBase> sink_2;//输入节点
    std::weak_ptr<HWCNodeBase> sink_3;//输入节点
    std::weak_ptr<HWCNodeBase> source;//输出节点，下游分发数据
    
    void setNodeName(std::string& str){
        this->mNodeName=str;
    }
    
    std::string& getNodeName(){
        return this->mNodeName;
    }
    
    int getStreamType(){
        return this->mStreamType;
    }
    void setStreamType(int type){
        this->mStreamType=type;
    }
    
    void setSource(std::string& source){
        this->mSource=source;
    }
    
    std::string& getSource(){
        return this->mSource;
    }
    
protected:
    virtual ~HWCNodeBase(){};
    
    HWCNodeBase(){};
    
    HWCNodeBase(std::string name,int streamType=-1){
        this->mNodeName=name;
        this->mStreamType=streamType;
//        this->mEncoderType=encoderType;
    }
   
    
    std::mutex m_Mutex_in;
    std::mutex m_Mutex_out;
    
    std::string mNodeName;
    std::string mSource;
    int mStreamType;
//    int mEncoderType;
    
};


#endif /* EncoderNodeBase_hpp */
