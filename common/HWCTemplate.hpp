//
//  HWCTemplate.hpp
//  Test
//
//  Created by developer on 2021/11/11.
//

#ifndef HWCTemplate_hpp
#define HWCTemplate_hpp

#include <stdio.h>
template<typename _Tp>
class SingleInstance{
public:
    static _Tp& getInstance(){
        static _Tp tp;
        return tp;
    }
private:
    SingleInstance(){}
    SingleInstance(const SingleInstance& instance)=delete;
    SingleInstance operator=(const SingleInstance& instance)=delete;
    
    SingleInstance(const SingleInstance&& instance)=delete;
    SingleInstance operator=(const SingleInstance&& instance)=delete;
    
};

#endif /* HWCTemplate_hpp */
