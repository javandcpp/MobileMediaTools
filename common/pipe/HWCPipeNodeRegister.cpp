#include "HWCPipeNodeRegister.hpp"
#include "HWCMP3EncoderNode.hpp"
#include "HWCMp4MuxerNode.hpp"
#define AV_REGISTER_NODE(x) nodes.push_back(make_shared<x>());

//std::vector<std::shared_ptr<HWCNodeBase>> HWCPipeNodeRegister::nodes;

HWCPipeNodeRegister::HWCPipeNodeRegister(){
    avRegisterAllNode();
}

HWCPipeNodeRegister& HWCPipeNodeRegister::getInstance(){
    static HWCPipeNodeRegister mPipeNoderegister;
    return mPipeNoderegister;
}

void HWCPipeNodeRegister::avRegisterAllNode(){
    AV_REGISTER_NODE(HWCMP3EncoderNode);
    AV_REGISTER_NODE(HWCMp4MuxerNode);
//    AV_REGISTER_NODE(HWCMP3EncoderNode);
    
}

std::vector<std::shared_ptr<HWCNodeBase>>& HWCPipeNodeRegister::getNodes(){
    return HWCPipeNodeRegister::nodes;
}

std::shared_ptr<HWCNodeBase>* HWCPipeNodeRegister::findNode(std::string& name,int type){
    auto nodes_begin=getNodes().begin();
    auto nodes_end=getNodes().end();
    while (nodes_begin!=nodes_end) {
        if(nodes_begin.base()){
            HWCNodeBase* node=nodes_begin.base()->get();
            if(node->getNodeName()==name&&node->getStreamType()==type){
                return static_cast<std::shared_ptr<HWCNodeBase>*>(nodes_begin.base());
            }
        }
        ++nodes_begin;
    }
   
    return nullptr;
}
