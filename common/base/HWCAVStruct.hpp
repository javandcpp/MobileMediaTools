//
//  AVFrameData.hpp
//  Test
//
//  Created by developer on 2021/11/9.
//

#ifndef AVFrameData_hpp
#define AVFrameData_hpp

#include <stdio.h>
#include <iostream>

struct AVFrameData{
    uint8_t data[8];
    uint16_t data_length;
    
    uint64_t pts;
    uint64_t dts;
    uint16_t stream_type;//video audio
    
};

#endif /* AVFrameData_hpp */
