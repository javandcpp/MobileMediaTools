//
//  HWCMP3EncoderNode.cpp
//  Test
//
//  Created by developer on 2021/11/9.
//

#include "HWCMP3EncoderNode.hpp"
#include "Define.h"
#include "Log.h"


HWCMP3EncoderNode::HWCMP3EncoderNode():HWCNodeBase("mp3encoder",AUDIO_STREAM_TYPE,AUDIO_STREAM_TYPE){
    LOG(HWCMP3EncoderNode);
}

HWCMP3EncoderNode::~HWCMP3EncoderNode(){
}

void HWCMP3EncoderNode::inputData(AVFrameData *data){
  
}

void HWCMP3EncoderNode::outputData(AVFrameData *data){
    
}
