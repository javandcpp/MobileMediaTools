//
//  HWCVideoStreamProcessNode.hpp
//  Test
//
//  Created by developer on 2021/11/10.
//

#ifndef HWCVideoStreamProcessNode_hpp
#define HWCVideoStreamProcessNode_hpp

#include <stdio.h>
#include "HWCNodeBase.hpp"

class HWCVideoStreamProcessNode:public HWCNodeBase{
    
public:
    HWCVideoStreamProcessNode();
    ~HWCVideoStreamProcessNode();
    void inputData(AVFrameData* data)override;
    void outputData(AVFrameData* data)override;
};

#endif /* HWCVideoStreamProcessNode_hpp */
