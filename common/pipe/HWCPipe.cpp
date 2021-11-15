//
//  HWCPipe.cpp
//  Test
//
//  Created by developer on 2021/11/9.
//

#include "HWCPipe.hpp"
#include "Define.hpp"
HWCPipe::HWCPipe(){
    
}

HWCPipe::~HWCPipe(){
    
}

void HWCPipe::pipeTransportData(AVFrameData* data){
    std::lock_guard<std::mutex> lock(m_Mutex);
    if(data->stream_type==AUDIO_STREAM_TYPE){
        if(audioSinkHead){
            audioSinkHead->inputData(data);
        }
    }else if(data->stream_type==VIDEO_STREAM_TYPE){
        if(videoSinkHead){
            videoSinkHead->inputData(data);
        }
    }
}
void HWCPipe::registerEventBus(HWCPipeInfo *pipeInfo){
    std::lock_guard<std::mutex> lock(m_Mutex);
    auto& nodes=pipeInfo->getPipeNodes();
    auto start=nodes.begin();
    while (start!=nodes.end()) {
        
		auto &nodePtr = *start;
        SingleInstance<HWCEventBus>::getInstance().registerEvent(nodePtr);
        ++start;
    }
}


void HWCPipe::unRegisterEventBus(){
    std::lock_guard<std::mutex> lock(m_Mutex);
    SingleInstance<HWCEventBus>::getInstance().unregisterEvent();
}

void HWCPipe::postSyncEvent(HWCEvent &event){
    std::lock_guard<std::mutex> lock(m_Mutex);
    SingleInstance<HWCEventBus>::getInstance().postSyncEvent(event);
}

void HWCPipe::postAsyncEvent(HWCEvent& event){
    std::lock_guard<std::mutex> lock(m_Mutex);
    SingleInstance<HWCEventBus>::getInstance().postAsyncEvent(event);
}


void HWCPipe::createPipe(HWCPipeInfo *pipeInfo){
    std::lock_guard<std::mutex> lock(m_Mutex);
    if(pipeInfo){
//        std::vector<std::shared_ptr<HWCNodeBase>> &nodes=
        auto& nodes=pipeInfo->getPipeNodes();
        
        auto start=nodes.begin();
        while (start!=nodes.end()) {
            HWCNodeBase* node= start->get();
            if(node->sink.lock()&&node->getStreamType()==VIDEO_STREAM_TYPE){
                videoSinkHead=node->sink.lock();
            }else if(node->sink_2.lock()&&node->getStreamType()==VIDEO_STREAM_TYPE){
                videoSinkHead=node->sink_2.lock();
            }else if(node->sink.lock()&&node->getStreamType()==AUDIO_STREAM_TYPE){
                audioSinkHead=node->sink.lock();
            }else if(node->sink_2.lock()&&node->getStreamType()==AUDIO_STREAM_TYPE){
                audioSinkHead=node->sink_2.lock();
            }
            
            
           
            
            ++start;
        }
        
//        auto start=
//        while (start!=end) {
//            std::shared_ptr<HWCNodeBase> *pipeNode=start.base();
//
//
//            ++start;
//        }
    }
    

    
}
