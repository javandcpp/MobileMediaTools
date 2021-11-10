//
//  HWCPipeInfo.cpp
//  Test
//
//  Created by developer on 2021/11/9.
//

#include "HWCPipeInfo.hpp"
#include "HWCPipeNodeRegister.hpp"
#include "Log.h"


HWCPipeInfo::HWCPipeInfo(){
    
}

int HWCPipeInfo::parserFromJson(JSON& json,HWCPipeInfo& hwcPipeInfo){
    
    if(json.contains("pipe")){
        auto &arrays=json["pipe"];
        
        for(auto item:arrays){
            if(item.contains("streams")){
                
                auto streams=item["streams"];
                for (auto item:streams) {
        //            std::shared_ptr<HWCNodeBase> node=std::make_shared<HWCNodeBase>();
                   
        //            item["name"];
        //            item["type"].get_to(node.mStreamType);
                    std::string name;
                    int type;
                    item["name"].get_to(name);
                    item["type"].get_to(type);
                    {
                        std::shared_ptr<HWCNodeBase> ptr=HWCPipeNodeRegister::getInstance().findNode(name,type);
                        
                        LOGD("ptr usecount:%ld",ptr.use_count());
                        if(ptr){
                            HWCNodeBase *node=ptr.get();
                            node->inputData(nullptr);
                            LOGD("%s\n",node->getNodeName().c_str());
                        }
                    }
                }
            }
        }
        
      
        
    }
    
    
    return 0;
}
