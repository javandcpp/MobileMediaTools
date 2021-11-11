//
//  HWCMP3EncoderNode.hpp
//  Test
//
//  Created by developer on 2021/11/9.
//

#ifndef HWCMP3EncoderNode_hpp
#define HWCMP3EncoderNode_hpp

#include <stdio.h>
#include "HWCNodeBase.hpp"
class HWCMP3EncoderNode:public HWCNodeBase{
public:
    HWCMP3EncoderNode();
    ~HWCMP3EncoderNode();
    
    void inputData(AVFrameData* data)override;
    void outputData(AVFrameData* data)override;
    void onEvent(HWCEvent& event)override;
    
    
};

#endif /* HWCMP3EncoderNode_hpp */
