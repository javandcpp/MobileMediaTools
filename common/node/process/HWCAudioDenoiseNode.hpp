//
//  AudioStreamNode.hpp
//  Test
//
//  Created by developer on 2021/11/9.
//

#ifndef AudioStreamNode_hpp
#define AudioStreamNode_hpp

#include <stdio.h>
#include "HWCNodeBase.hpp"
class HWCAudioDenoiseNode:public HWCNodeBase{
    
public:
    HWCAudioDenoiseNode();
    ~HWCAudioDenoiseNode();
    void inputData(AVFrameData* data)override;
    void outputData(AVFrameData* data)override;
};
#endif /* AudioStreamNode_hpp */
