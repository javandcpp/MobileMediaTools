//
//  AudioStreamNode.cpp
//  Test
//
//  Created by developer on 2021/11/9.
//

#include "HWCAudioDenoiseNode.hpp"
#include "Log.h"
#include "HWCNodeBase.hpp"

HWCAudioDenoiseNode::HWCAudioDenoiseNode():HWCNodeBase("audiodenoisestream",0,0){
    
}

HWCAudioDenoiseNode::~HWCAudioDenoiseNode(){
    
}

void HWCAudioDenoiseNode::inputData(AVFrameData *data){
    std::lock_guard<std::mutex> _lock(m_Mutex_in);
   
    
    this->outputData(data);
}

void HWCAudioDenoiseNode::outputData(AVFrameData *data){
    std::lock_guard<std::mutex> _lock(m_Mutex_out);
    
    
    LOGD("inputData");
    HWCNodeBase* node=source.get();
    if(node){
        node->inputData(data);
    }
}
