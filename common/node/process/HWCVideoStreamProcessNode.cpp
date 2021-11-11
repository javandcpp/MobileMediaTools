//
//  HWCVideoStreamProcessNode.cpp
//  Test
//
//  Created by developer on 2021/11/10.
//

#include "HWCVideoStreamProcessNode.hpp"
#include "Log.h"
#include "Define.hpp"

HWCVideoStreamProcessNode::HWCVideoStreamProcessNode():HWCNodeBase("videoprocessstream",VIDEO_STREAM_TYPE){
    
}

HWCVideoStreamProcessNode::~HWCVideoStreamProcessNode(){
    
}

void HWCVideoStreamProcessNode::inputData(AVFrameData *data){
    std::lock_guard<std::mutex> _lock(m_Mutex_in);
    LOGD("inputData streamType:%d",data->stream_type);
    this->outputData(data);
}

void HWCVideoStreamProcessNode::outputData(AVFrameData *data){
    std::lock_guard<std::mutex> _lock(m_Mutex_out);
    LOGD("outputData");
    if(source.lock()){
        source.lock()->inputData(data);
    }
}

void HWCVideoStreamProcessNode::onEvent(HWCEvent& event){
    LOGD("onEvent:%d isAsync:%d",event.eventType,event.isAsync);
}
