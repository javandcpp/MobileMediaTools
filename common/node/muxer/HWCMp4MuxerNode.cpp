//
//  HWCMp4MuxerNode.cpp
//  Test
//
//  Created by developer on 2021/11/9.
//

#include "HWCMp4MuxerNode.hpp"
#include "Define.hpp"
#include "Log.h"
HWCMp4MuxerNode::HWCMp4MuxerNode():HWCNodeBase("mp4muxer",AUDIO_VIDEO_STREAM_TYPE){
    
}

HWCMp4MuxerNode::~HWCMp4MuxerNode(){
    
}

void HWCMp4MuxerNode::inputData(AVFrameData *data){
    std::lock_guard<std::mutex> _lock(m_Mutex_in);
    LOGD("inputData streamType:%d pts:%llu",data->stream_type,data->pts);
    this->outputData(data);
}

void HWCMp4MuxerNode::outputData(AVFrameData *data){
    std::lock_guard<std::mutex> _lock(m_Mutex_out);
    LOGD("outputData");
    if(source.lock()){
        source.lock()->inputData(data);
    }
}

