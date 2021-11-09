//
//  HWCPipe.hpp
//  Test
//
//  Created by developer on 2021/11/9.
//

#ifndef HWCPipe_hpp
#define HWCPipe_hpp

#include <stdio.h>
#include <iostream>
#include "HWCPipeInfo.hpp"
#include "HWCNodeBase.hpp"
class HWCPipe{
public:
    HWCPipe();
    
    ~HWCPipe();
    
    std::shared_ptr<HWCNodeBase> head;
    std::shared_ptr<HWCNodeBase> tail;
    
    
private:
    std::shared_ptr<HWCPipe> createPipe(HWCPipeInfo& pipeInfo);
    
    void pipeTransportData(AVFrameData* data);
    
    
};

#endif /* HWCPipe_hpp */
