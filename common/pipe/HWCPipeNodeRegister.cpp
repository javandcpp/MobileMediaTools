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



#endif /* HWCPipeNodeRegister_hpp */
class HWCPipeNodeRegister{
public:
    static HWCPipeNodeRegister& getInstance();
private:
    HWCPipeNodeRegister(){
        
    }
    
    HWCPipeNodeRegister(const HWCPipeNodeRegister& hwcNodeRegister)=delete;
    
    HWCPipeNodeRegister(const HWCPipeNodeRegister&& hwcNodeRegister)=delete;
    
    HWCPipeNodeRegister& operator=(const HWCPipeNodeRegister&)=delete;
    
    HWCPipeNodeRegister& operator=(const HWCPipeNodeRegister&&)=delete;
    
    
    static vector<shared_ptr<HWCNodeBase>> nodes;
    
  
    
    
    void avRegisterAllNode(HWCNodeBase& node);
    
    
  
    
};
