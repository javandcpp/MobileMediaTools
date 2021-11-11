//
//  HWCEvent.hpp
//  Test
//
//  Created by developer on 2021/11/11.
//

#ifndef HWCEvent_hpp
#define HWCEvent_hpp

#include <stdio.h>

typedef enum {
    EVENT_START=1,
    EVENT_PAUSE,
    EVENT_STOP,
    EVENT_RELEASE
}EventType;

class HWCEvent{
public:
    HWCEvent(){};
    
    EventType eventType;
    bool isAsync;
    
    bool operator==(const HWCEvent& event){
        return this->eventType==event.eventType;
    }
    
    
};

#endif /* HWCEvent_hpp */
