#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import <Foundation/Foundation.h>
#import "GPUImageContext.h"

#import "nMedialiveStreamingAPI.h"



@interface GPUImageVideoEncode : NSObject <GPUImageInput> {
    CGSize imageSize;
    GPUImageRotationMode inputRotation;
    BOOL _isBGRA;

    BOOL _isFirstVideoFrame;
    bool _isFirstEncodedFrame;
    BOOL _isLiving;
    BOOL _isLivingSwitch;
    BOOL _isToFinishLive;
    
}

@property(nonatomic,copy)void(^captureImageBlock)(UIImage* image);
@property(readonly) GLubyte *rawBytesForImage;

@property(nonatomic) BOOL enabled;


- (id)initWithDefaultVideoParaCtx;
- (id)initWithlsVideoParaCtx:(LSVideoParaCtx)videoParaCtx resultsInBGRAFormat:(BOOL)resultsInBGRAFormat;

- (NSUInteger)bytesPerRowInOutput;

- (void)setImageSize:(CGSize)newImageSize;

- (void)lockFramebufferForReading;
- (void)unlockFramebufferAfterReading;

/*
 * 滤镜直播推流相关：打开，关闭，暂停，恢复
 */
- (void)startVideoStream:(IMediaLiveStream*) pStream;
- (BOOL)stopVideoStream;
- (void)pauseVideoStream;
- (void)continueVideoStream;

/*
 * 设置直播推流编码帧率
 */
- (void)setFramerate:(int)framerate;
/*
 * 设置直播推流编码码率
 */
- (void)setBitrate:(int)bitrate;
/*
 * 设置直播推流编码分辨率，
 */
- (void)setEncodedVideoQuality:(LSVideoStreamingQuality)videoQuality;
/*
 * 直播推流最近一frame的截图
 */
- (void)setCaptureImage;
- (void)setCaptureImageBlock:(void (^)(UIImage *))captureImageBlock;

/*
 * 滤镜camera的方向，以及前后传递到这里，为了截图的方向
 */
+ (void)setDevicePosition:(AVCaptureDevicePosition)position;

+ (void)setInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation;

/*
 * 添加直播推流的水印
 */
- (void)addWaterMark: (UIImage*) image
                 rect: (CGRect) rect
             location: (LSWaterMarkLocation) location;

- (void)setLogLevel:(LSMediaLog)level;

@end
