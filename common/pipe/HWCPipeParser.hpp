//
//  PipeParser.hpp
//  Test
//
//  Created by developer on 2021/11/9.
//

#ifndef PipeParser_hpp
#define PipeParser_hpp

#include <stdio.h>
#include "../include/json_header.h"
#include "HWCPipeInfo.hpp"


class HWCPipeParser{
    
    
    
public:
    static std::shared_ptr<HWCPipeInfo> parser(std::string json_str);
    
    static std::mutex mutex;
};

#endif /* PipeParser_hpp */
