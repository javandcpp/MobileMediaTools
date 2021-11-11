//
//  AudioStreamNode.cpp
//  Test
//
//  Created by developer on 2021/11/9.
//

#include "HWCAudioDenoiseNode.hpp"
#include "Log.h"
#include "HWCNodeBase.hpp"
#include "Define.hpp"

HWCAudioDenoiseNode::HWCAudioDenoiseNode():HWCNodeBase("audiodenoisestream",AUDIO_STREAM_TYPE){
    
}

HWCAudioDenoiseNode::~HWCAudioDenoiseNode(){
    
}

void HWCAudioDenoiseNode::inputData(AVFrameData *data){
    std::lock_guard<std::mutex> _lock(m_Mutex_in);
    LOGD("inputData streamType:%d",data->stream_type);
    this->outputData(data);
}

void HWCAudioDenoiseNode::outputData(AVFrameData *data){
    std::lock_guard<std::mutex> _lock(m_Mutex_out);
    LOGD("outputData");
    if(source.lock()){
        source.lock()->inputData(data);
    }
}

void HWCAudioDenoiseNode::onEvent(HWCEvent& event){
    LOGD("onEvent:%d isAsync:%d",event.eventType,event.isAsync);
}
