//
//  HWCPipeNodeRegister.hpp
//  Test
//
//  Created by developer on 2021/11/9.
//

#ifndef HWCPipeNodeRegister_hpp
#define HWCPipeNodeRegister_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include "HWCNodeBase.hpp"
using namespace std;




class HWCPipeNodeRegister{
public:
    static HWCPipeNodeRegister& getInstance();
    
    vector<std::shared_ptr<HWCNodeBase>>& getStreamNodes();
    vector<std::shared_ptr<HWCNodeBase>>& getEncoderNodes();
    vector<std::shared_ptr<HWCNodeBase>>& getMuxerNodes();
    
    std::shared_ptr<HWCNodeBase> findNode(std::string& name,int type);
    
    void avRegisterAllNode();
private:
  
    HWCPipeNodeRegister();
    
    HWCPipeNodeRegister(const HWCPipeNodeRegister& hwcNodeRegister)=delete;
    
    HWCPipeNodeRegister(const HWCPipeNodeRegister&& hwcNodeRegister)=delete;
    
    HWCPipeNodeRegister& operator=(const HWCPipeNodeRegister&)=delete;
    
    HWCPipeNodeRegister& operator=(const HWCPipeNodeRegister&&)=delete;
    
    
    std::vector<std::shared_ptr<HWCNodeBase>> streamNodes;
    std::vector<std::shared_ptr<HWCNodeBase>> encoderNodes;
    std::vector<std::shared_ptr<HWCNodeBase>> muxerNodes;
    
    static std::once_flag flag;

    
  
    
    
    
    
    
  
    
};


#endif /* HWCPipeNodeRegister_hpp */
