//
//  HWCAVCapture.h
//  Test
//
//  Created by developer on 2021/11/9.
//

#import <Foundation/Foundation.h>
#import "Define.hpp"

NS_ASSUME_NONNULL_BEGIN

typedef enum{
    MEDIA_VIDEO=0,MEDIA_AUDIO
}MediaType;

@interface HWCAVCapture : NSObject

-(void)startCapture:(MediaType)type;

-(void)stopCapture;
@end

NS_ASSUME_NONNULL_END
