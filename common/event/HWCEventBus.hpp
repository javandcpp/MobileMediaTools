//
//  HWCEventBus.hpp
//  Test
//
//  Created by developer on 2021/11/11.
//

#ifndef HWCEventBus_hpp
#define HWCEventBus_hpp
#include "Define.hpp"
#include <stdio.h>
#include <unordered_map>
#include "HWCTemplate.hpp"
#include "HWCNodeBase.hpp"
#include "HWCEvent.hpp"
#include <vector>
using namespace std;




class HWCEventBus{
public:
    friend class SingleInstance<HWCEventBus>;
    
    void registerEvent(shared_ptr<HWCNodeBase> ptr);
    void unregisterEvent();
    void postAsyncEvent(HWCEvent event);
    void postSyncEvent(HWCEvent& event);
    
   
    
private:
    HWCEventBus()=default;
    HWCEventBus(const HWCEventBus& h)=delete;
    HWCEventBus operator=(const HWCEventBus& h)=delete;
    HWCEventBus(const HWCEventBus&& h)=delete;
    HWCEventBus operator=(const HWCEventBus&& h)=delete;
    
//    struct hash_name{
//        size_t operator()(const HWCEvent & p) const{
//            return hash<EventType>()(p.eventType);
//        }
//    };
//
//    unordered_map<HWCEvent, shared_ptr<HWCNodeBase>,hash_name> map;

    std::vector<std::weak_ptr<HWCNodeBase>> nodes;
    std::mutex m_Mutex;
    
    
};

#endif /* HWCEventBus_hpp */
