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

#include "Log.h"

struct AVFrameData{
    uint64_t pts;
    uint64_t dts;
    uint16_t data_length;
    uint8_t *data;
    uint8_t stream_type;
    
    AVFrameData(){
        
    }
    
    ~AVFrameData(){
        if (this->data) {
            free(this->data);
            this->data=nullptr;
        }
    }
    
    AVFrameData(const AVFrameData& data){
        LOGD("AVFormatData copy\n");
    }
    
    AVFrameData(AVFrameData&& data){
        LOGD("AVFormatData move copy\n");
        this->pts=data.pts;
        this->dts=data.dts;
        this->data_length=data.data_length;
        this->stream_type=data.stream_type;
        this->data=data.data;
        if(data.data){
            data.data=nullptr;
        }
    }
};

#endif /* AVFrameData_hpp */
