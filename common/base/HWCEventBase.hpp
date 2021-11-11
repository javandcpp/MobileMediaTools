//
//  HWCEventBase.hpp
//  Test
//
//  Created by developer on 2021/11/11.
//

#ifndef HWCEventBase_hpp
#define HWCEventBase_hpp

#include <stdio.h>
#include "HWCEventBase.hpp"
#include "Define.hpp"
#include "HWCEvent.hpp"
class HWCEventBase{
public:
    virtual void onEvent(HWCEvent& event)=0;
};

#endif /* HWCEventBase_hpp */
