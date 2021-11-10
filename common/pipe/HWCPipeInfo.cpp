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

std::vector<std::shared_ptr<HWCNodeBase>>& HWCPipeInfo::getPipeNodes(){
    return pipeNodes;
}

void HWCPipeInfo::parserFromJson(JSON& json){
    std::lock_guard<std::mutex> lock(m_Mutex);
    if(json.contains("pipe")){
        auto &arrays=json["pipe"];
       
        int type;
        
        for(auto item:arrays){
            if(item.contains("streams")){
                
                auto streams=item["streams"];
                for (auto item:streams) {
                    std::string name;
                    std::string source;
                    item["name"].get_to(name);
                    item["type"].get_to(type);
                    if(item.contains("source")){
                        item["source"].get_to(source);
                    }
                    
                    std::shared_ptr<HWCNodeBase> spStream=HWCPipeNodeRegister::getInstance().findNode(name);
                    if(spStream){
                        spStream.get()->setSource(source);
                        std::shared_ptr<HWCNodeBase> spSource=HWCPipeNodeRegister::getInstance().findNode(source);
                        if(spSource){
                            spStream.get()->source=spSource;
                            if(!spSource.get()->sink.lock()){
                                spSource.get()->sink=spStream;
                            }else if(!spSource.get()->sink_2.lock()){
                                spSource.get()->sink_2=spStream;
                            }
                            
                        }
                        this->pipeNodes.push_back(spStream);
                    }
                    
                }
            }else if(item.contains("encoders")){
                auto encoders=item["encoders"];
                for (auto item:encoders) {
                    std::string name;
                    std::string source;
                    item["name"].get_to(name);
                    item["type"].get_to(type);
                    if(item.contains("source")){
                        item["source"].get_to(source);
                    }
                    std::shared_ptr<HWCNodeBase> spEncoder=HWCPipeNodeRegister::getInstance().findNode(name);
                    if(spEncoder){
                        spEncoder.get()->setSource(source);
                        std::shared_ptr<HWCNodeBase> spSource=HWCPipeNodeRegister::getInstance().findNode(source);
                        if(spSource){
                            spEncoder.get()->source=spSource;
                            if(!spSource.get()->sink.lock()){
                                spSource.get()->sink=spEncoder;
                            }else if(!spSource.get()->sink_2.lock()){
                                spSource.get()->sink_2=spEncoder;
                            }
                        }
                        this->pipeNodes.push_back(spEncoder);
                    }
                    
                }
            }else if(item.contains("muxers")){
                auto muxers=item["muxers"];
                for (auto item:muxers) {
                    std::string name;
                    std::string source;
                    item["name"].get_to(name);
                    item["type"].get_to(type);
                    if(item.contains("source")){
                        item["source"].get_to(source);
                    }
                    std::shared_ptr<HWCNodeBase> spMuxer=HWCPipeNodeRegister::getInstance().findNode(name);
                    if(spMuxer){
                        spMuxer.get()->setSource(source);
                        std::shared_ptr<HWCNodeBase> spSource=HWCPipeNodeRegister::getInstance().findNode(source);
                        if(spSource){
                            spMuxer.get()->source=spSource;
                            if(!spSource.get()->sink.lock()){
                                spSource.get()->sink=spMuxer;
                            }else if(!spSource.get()->sink_2.lock()){
                                spSource.get()->sink=spMuxer;
                            }
                        }
                        this->pipeNodes.push_back(spMuxer);
                    }
                    
                }
            }
        }
    }
}
