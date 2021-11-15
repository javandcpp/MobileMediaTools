//
//  HWCEventBus.cpp
//  Test
//
//  Created by developer on 2021/11/11.
//

#include "HWCEventBus.hpp"
#include "Log.h"
#include <thread>

void HWCEventBus::registerEvent(shared_ptr<HWCNodeBase>& ptr){
    std::lock_guard<std::mutex> lock(m_Mutex);
    nodes.push_back(ptr);
    
}

void HWCEventBus::unregisterEvent(){
    std::lock_guard<std::mutex> lock(m_Mutex);
    nodes.clear();
}

void HWCEventBus::postSyncEvent(HWCEvent& event){
    std::lock_guard<std::mutex> lock(m_Mutex);
    for_each(nodes.begin(), nodes.end(), [&](std::weak_ptr<HWCNodeBase> ptr){
        shared_ptr<HWCNodeBase> sp=ptr.lock();
        if(sp){
            sp->onEvent(event);
        }
    });
}

void HWCEventBus::postAsyncEvent(HWCEvent event){
    std::lock_guard<std::mutex> lock(m_Mutex);
    std::function<void(shared_ptr<HWCNodeBase>,shared_ptr<HWCEvent>)> func=[](shared_ptr<HWCNodeBase> ptr,shared_ptr<HWCEvent> eventPtr){
        if(ptr&&eventPtr){
            eventPtr->isAsync=true;
            ptr->onEvent(*eventPtr);
        }
    };
    for_each(nodes.begin(), nodes.end(), [&](std::weak_ptr<HWCNodeBase> ptr){
        shared_ptr<HWCNodeBase> sp=ptr.lock();
        if(sp){
            shared_ptr<HWCEvent> ptr=std::make_shared<HWCEvent>();
            ptr->eventType=event.eventType;
            std::thread t1(func,sp,ptr);
            t1.detach();
        }
    });
    
}
