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
    
    std::shared_ptr<HWCNodeBase> audioSinkHead;
    std::shared_ptr<HWCNodeBase> videoSinkHead;
    
    void createPipe(HWCPipeInfo* pipeInfo);
    
    void pipeTransportData(AVFrameData* data);
    
private:
   
    
   
    
    std::mutex m_Mutex;
    
    
};

#endif /* HWCPipe_hpp */
