#include "HWCPipeNodeRegister.hpp"
#include "HWCMP3EncoderNode.hpp"
#include "HWCMp4MuxerNode.hpp"
#include "HWCAudioDenoiseNode.hpp"
#include "HWCH264EncoderNode.hpp"
#include "HWCVideoStreamProcessNode.hpp"
#include "Define.hpp"
#include "Log.h"

#define AV_REGISTER_ENCODER_NODE(x) encoderNodes.push_back(make_shared<x>());
#define AV_REGISTER_STREAM_NODE(x)  streamNodes.push_back(make_shared<x>());
#define AV_REGISTER_MUXER_NODE(x)   muxerNodes.push_back(make_shared<x>());

//std::vector<std::shared_ptr<HWCNodeBase>> HWCPipeNodeRegister::nodes;
std::once_flag HWCPipeNodeRegister::flag;

HWCPipeNodeRegister::HWCPipeNodeRegister(){
    
}


HWCPipeNodeRegister& HWCPipeNodeRegister::getInstance(){
    static HWCPipeNodeRegister mPipeNoderegister;
    return mPipeNoderegister;
}

//register all node
void HWCPipeNodeRegister::avRegisterAllNode(){
    std::call_once(flag,[&]{
        AV_REGISTER_STREAM_NODE(HWCAudioDenoiseNode);
        AV_REGISTER_STREAM_NODE(HWCVideoStreamProcessNode);
        
        AV_REGISTER_ENCODER_NODE(HWCMP3EncoderNode);
        AV_REGISTER_ENCODER_NODE(HWCH264EncoderNode);
        
        AV_REGISTER_MUXER_NODE(HWCMp4MuxerNode);
    });
}

std::vector<std::shared_ptr<HWCNodeBase>>& HWCPipeNodeRegister::getStreamNodes(){
    return HWCPipeNodeRegister::streamNodes;
}
std::vector<std::shared_ptr<HWCNodeBase>>& HWCPipeNodeRegister::getEncoderNodes(){
    return HWCPipeNodeRegister::encoderNodes;
}
std::vector<std::shared_ptr<HWCNodeBase>>& HWCPipeNodeRegister::getMuxerNodes(){
    return HWCPipeNodeRegister::muxerNodes;
}

std::shared_ptr<HWCNodeBase> HWCPipeNodeRegister::findNode(std::string& name){
    if(name.begin()!=name.end()){
        transform(name.begin(), name.end(), name.begin(), ::tolower);
    }else{
        return nullptr;
    }
    
    
    if(name.find("stream")!=string::npos){
        
        auto nodes_begin=getStreamNodes().begin();
        auto nodes_end=getStreamNodes().end();
        while (nodes_begin!=nodes_end) {
            if(nodes_begin.base()){
                HWCNodeBase* node=nodes_begin.base()->get();
                if(node->getNodeName()==name){
                    return static_cast<std::shared_ptr<HWCNodeBase>>(*nodes_begin.base());
                }
            }
            ++nodes_begin;
        }
    }else if(name.find("encoder")!=string::npos){
        
        auto nodes_begin=getEncoderNodes().begin();
        auto nodes_end=getEncoderNodes().end();
        while (nodes_begin!=nodes_end) {
            if(nodes_begin.base()){
                HWCNodeBase* node=nodes_begin.base()->get();
                if(node->getNodeName()==name){
                    return static_cast<std::shared_ptr<HWCNodeBase>>(*nodes_begin.base());
                }
            }
            ++nodes_begin;
        }
    }else if(name.find("muxer")!=string::npos){
        
        auto nodes_begin=getMuxerNodes().begin();
        auto nodes_end=getMuxerNodes().end();
        while (nodes_begin!=nodes_end) {
            if(nodes_begin.base()){
                HWCNodeBase* node=nodes_begin.base()->get();
                if(node->getNodeName()==name){
                    return static_cast<std::shared_ptr<HWCNodeBase>>(*nodes_begin.base());
                }
            }
            ++nodes_begin;
        }
    }
    
    
    
    return nullptr;
}
