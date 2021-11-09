//
//  HWCPipeInfo.cpp
//  Test
//
//  Created by developer on 2021/11/9.
//

#include "HWCPipeInfo.hpp"

HWCPipeInfo::HWCPipeInfo(){
    
}

int HWCPipeInfo::parserFromJson(JSON& json,HWCPipeInfo& hwcPipeInfo){
    
    if(json.contains("stream")&&json["stream"].size()>0){
        
        auto streams=json["stream"];
        for (auto item:streams) {
            
//            std::make_shared<>(<#_Args &&__args...#>)
//            streams.push_back()
        }
            
            
        
    }
    
    
    return 0;
}
