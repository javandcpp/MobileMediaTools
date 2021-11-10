//
//  HWCH264EncoderNode.hpp
//  Test
//
//  Created by developer on 2021/11/10.
//

#ifndef HWCH264EncoderNode_hpp
#define HWCH264EncoderNode_hpp

#include <stdio.h>
#include "HWCNodeBase.hpp"
class HWCH264EncoderNode:public HWCNodeBase{
  
public:
    HWCH264EncoderNode();
    ~HWCH264EncoderNode();
    
    void inputData(AVFrameData* data)override;
    void outputData(AVFrameData* data)override;
    
};

#endif /* HWCH264EncoderNode_hpp */
