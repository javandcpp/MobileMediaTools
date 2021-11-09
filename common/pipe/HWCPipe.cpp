//
//  HWCPipe.cpp
//  Test
//
//  Created by developer on 2021/11/9.
//

#include "HWCPipe.hpp"
HWCPipe::HWCPipe(){
    
}

HWCPipe::~HWCPipe(){
    
}

void HWCPipe::pipeTransportData(AVFrameData* data){
    HWCNodeBase* nodeHead=head.get();
    nodeHead->inputData(data);
}


std::shared_ptr<HWCPipe> HWCPipe::createPipe(HWCPipeInfo &pipeInfo){
    
    
    
    
    
    
    
    return std::make_shared<HWCPipe>();
}
