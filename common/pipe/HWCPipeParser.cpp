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
int HWCPipeParser::parser(std::string json_str,HWCPipeInfo& hwcPipeInfo){
    lock_guard<std::mutex> _lock(HWCPipeParser::mutex);
    try {
      if (json_str.empty()) {
        LOGD("json_str==empty()");
        return -1;
      }

      JSON result = JSON::parse(json_str.begin(), json_str.end());
      return HWCPipeInfo::parserFromJson(result, hwcPipeInfo);
       
    } catch (std::exception &e) {
      LOGD("%s", e.what());
      return -1;
    }
    return 0;
}
