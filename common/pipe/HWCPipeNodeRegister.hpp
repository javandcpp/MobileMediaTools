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
    
    vector<std::shared_ptr<HWCNodeBase>>& getNodes();
    
    std::shared_ptr<HWCNodeBase>* findNode(std::string& name,int type);
    
private:
  
    HWCPipeNodeRegister();
    
    HWCPipeNodeRegister(const HWCPipeNodeRegister& hwcNodeRegister)=delete;
    
    HWCPipeNodeRegister(const HWCPipeNodeRegister&& hwcNodeRegister)=delete;
    
    HWCPipeNodeRegister& operator=(const HWCPipeNodeRegister&)=delete;
    
    HWCPipeNodeRegister& operator=(const HWCPipeNodeRegister&&)=delete;
    
    
    std::vector<std::shared_ptr<HWCNodeBase>> nodes;
    
    void avRegisterAllNode();
    
  
    
    
    
    
    
  
    
};


#endif /* HWCPipeNodeRegister_hpp */
