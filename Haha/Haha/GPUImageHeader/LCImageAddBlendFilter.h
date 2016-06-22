//
//  LCImageAddBlendFilter.h
//  LOFTERCam
//
//  Created by Dikey on 11/30/15.
//  Copyright © 2015 Netease. All rights reserved.
//

#import "GPUImageTwoInputFilter.h"


@interface LCImageAddBlendFilter : GPUImageTwoInputFilter{
    GLfloat _fRatio;
    GLint _glRatioLocation;
}

- (id)initWithRatio:(float)setR;




@end
