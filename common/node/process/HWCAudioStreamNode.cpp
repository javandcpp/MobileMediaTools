//
//  AudioStreamNode.cpp
//  Test
//
//  Created by developer on 2021/11/9.
//

#include "HWCAudioStreamNode.hpp"
#include "Log.h"

HWCAudioStreamNode::~HWCAudioStreamNode(){
    
}

void HWCAudioStreamNode::inputData(AVFrameData *data){
    std::lock_guard<std::mutex> _lock(m_Mutex_in);
   
    
    this->outputData(data);
}

void HWCAudioStreamNode::outputData(AVFrameData *data){
    std::lock_guard<std::mutex> _lock(m_Mutex_out);
    
    
    LOGD("inputData");
    HWCNodeBase* node=source.get();
    if(node){
        node->inputData(data);
    }
}
