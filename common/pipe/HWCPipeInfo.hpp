//
//  HWCPipeInfo.hpp
//  Test
//
//  Created by developer on 2021/11/9.
//

#ifndef HWCPipeInfo_hpp
#define HWCPipeInfo_hpp

#include <stdio.h>
#include "../include/json_header.h"
#include "HWCNodeBase.hpp"

class HWCPipeInfo{
    
private:
    std::vector<std::shared_ptr<HWCNodeBase>> pipeNodes;
    
public:
    std::vector<std::shared_ptr<HWCNodeBase>>& getPipeNodes();
    HWCPipeInfo();
    void parserFromJson(JSON& json);
    std::mutex m_Mutex;
    
};

#endif /* HWCPipeInfo_hpp */
