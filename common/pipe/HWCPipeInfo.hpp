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
    
    
    std::vector<std::shared_ptr<HWCNodeBase>> streams;
    std::vector<std::shared_ptr<HWCNodeBase>> encoders;
    std::vector<std::shared_ptr<HWCNodeBase>> muxers;
    
public:
    HWCPipeInfo();
    static int parserFromJson(JSON& json,HWCPipeInfo& hwcPipeInfo);
    
};

#endif /* HWCPipeInfo_hpp */
