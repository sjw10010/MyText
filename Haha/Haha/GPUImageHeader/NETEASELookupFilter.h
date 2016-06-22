#import "GPUImageFilterGroup.h"

@class GPUImagePicture;

@interface NETEASELookupFilter : GPUImageFilterGroup
{
    GPUImagePicture *lookupImageSource;
    NSString* lutFilePath;
    float ratio;
}



/**
 *  使用滤镜
 *
 *  @param 滤镜图片       滤镜图片
 *  @param setR          滤镜强度（0-1）
 *  @param setTextureIdx 默认传1
 *
 *  @return
 */
- (id)initWithFilterImage:(UIImage *)filterImage
                    ratio:(float)setR
               textureIdx:(int)setTextureIdx;

@end
