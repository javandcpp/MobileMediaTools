//
//  HWCAVCapture.m
//  Test
//
//  Created by developer on 2021/11/9.
//

#import "HWCAVCapture.h"
#include "HWCPipe.hpp"
#include "HWCPipeParser.hpp"
#include "HWCPipeNodeRegister.hpp"


@implementation HWCAVCapture

-(instancetype)init{
    self =[super init];
    if(self){
       
    }
    return self;
}

-(void)startCapture:(MediaType)type{
    HWCPipeNodeRegister::getInstance().avRegisterAllNode();
    HWCPipeNodeRegister::getInstance().avRegisterAllNode();
    HWCPipeNodeRegister::getInstance().avRegisterAllNode();
    NSString *path=[[NSBundle mainBundle] pathForResource:@"mediaconfig" ofType:@"json"];
    NSError *error;
    NSString *contents=[NSString stringWithContentsOfFile:path encoding:NSUTF8StringEncoding error:&error];
    if (contents!=nil) {
        HWCPipeInfo hwcPipeInfo;
        HWCPipeParser::parser([contents UTF8String],hwcPipeInfo);
    }
}

@end
