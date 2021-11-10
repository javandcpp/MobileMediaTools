//
//  PipeParser.cpp
//  Test
//
//  Created by developer on 2021/11/9.
//

#include "HWCPipeParser.hpp"
#include "Log.h"
#include "HWCPipeInfo.hpp"
using namespace std;
std::mutex HWCPipeParser::mutex;
std::shared_ptr<HWCPipeInfo> HWCPipeParser::parser(std::string json_str){
    lock_guard<std::mutex> _lock(HWCPipeParser::mutex);
    try {
        if (json_str.empty()) {
            LOGD("json_str==empty()");
            return nullptr;
        }
        
        JSON result = JSON::parse(json_str.begin(), json_str.end());
        std::shared_ptr<HWCPipeInfo> sp=std::make_shared<HWCPipeInfo>();
        sp->parserFromJson(result);
        return sp;
        
    } catch (std::exception &e) {
        LOGD("%s", e.what());
    }
    return nullptr;
}
