//
//  HWCMp4MuxerNode.hpp
//  Test
//
//  Created by developer on 2021/11/9.
//

#ifndef HWCMp4MuxerNode_hpp
#define HWCMp4MuxerNode_hpp

#include <stdio.h>
#include "HWCNodeBase.hpp"

class HWCMp4MuxerNode:public HWCNodeBase{
    
public:
    ~HWCMp4MuxerNode();
    
    void inputData(AVFrameData* data)override;
    void outputData(AVFrameData* data)override;
};
#endif /* HWCMp4MuxerNode_hpp */
