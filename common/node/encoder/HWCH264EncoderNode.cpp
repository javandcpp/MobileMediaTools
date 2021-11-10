//
//  HWCH264EncoderNode.cpp
//  Test
//
//  Created by developer on 2021/11/10.
//

#include "HWCH264EncoderNode.hpp"
#include "Define.hpp"
#include "Log.h"


HWCH264EncoderNode::HWCH264EncoderNode():HWCNodeBase("h264encoder",VIDEO_STREAM_TYPE){
    LOG(HWCH264EncoderNode);
}

HWCH264EncoderNode::~HWCH264EncoderNode(){
}

void HWCH264EncoderNode::inputData(AVFrameData *data){
    std::lock_guard<std::mutex> _lock(m_Mutex_in);
    LOGD("inputData streamType:%d",data->stream_type);
    this->outputData(data);
}

void HWCH264EncoderNode::outputData(AVFrameData *data){
    std::lock_guard<std::mutex> _lock(m_Mutex_out);
    LOGD("outputData");
    if(source.lock()){
        source.lock()->inputData(data);
    }
}
