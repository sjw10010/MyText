//
//  LCImageLookupFilter.h
//  LOFTERCam
//
//  Created by Dikey on 11/30/15.
//  Copyright © 2015 Netease. All rights reserved.
//

#import "GPUImageLookupFilter.h"

@interface LCImageLookupFilter : GPUImageLookupFilter{
    GLfloat _fRatio;
    GLint _glRatioLocation;
}

- (id)initWithRatio:(float)setR
         textureIdx:(int)textureIdx;


@end
