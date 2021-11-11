//
//  HWCMP3EncoderNode.cpp
//  Test
//
//  Created by developer on 2021/11/9.
//

#include "HWCMP3EncoderNode.hpp"
#include "Define.hpp"
#include "Log.h"


HWCMP3EncoderNode::HWCMP3EncoderNode():HWCNodeBase("mp3encoder",AUDIO_STREAM_TYPE){
    LOG(HWCMP3EncoderNode);
}

HWCMP3EncoderNode::~HWCMP3EncoderNode(){
}

void HWCMP3EncoderNode::inputData(AVFrameData *data){
    std::lock_guard<std::mutex> _lock(m_Mutex_in);
    LOGD("inputData streamType:%d",data->stream_type);
    this->outputData(data);
}

void HWCMP3EncoderNode::outputData(AVFrameData *data){
    std::lock_guard<std::mutex> _lock(m_Mutex_out);
    LOGD("outputData");
    if(source.lock()){
        std::shared_ptr<HWCNodeBase> sp=source.lock();

        source.lock()->inputData(data);
    }
}

void HWCMP3EncoderNode::onEvent(HWCEvent& event){
    LOGD("onEvent:%d isAsync:%d",event.eventType,event.isAsync);
}
