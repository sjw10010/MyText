//
//  nMedialiveStreamingAPI.h
//  livestream
//
//  Created by zhuling on 15/7/10.
//  Copyright (c) 2015年 NetEase. All rights reserved.
//

#ifndef MEDIA_LIVE_STREAMING_API_H
#define MEDIA_LIVE_STREAMING_API_H

#include <stdint.h>
#include "nMediaLiveStreamingDefs.h"
#if defined(_WIN32) || defined(__cdecl)
#define EXTAPI __cdecl
#else
#define EXTAPI
#endif

#ifdef __ANDROID__
#include "jni.h"
#endif

typedef struct QosControlMessage
{
    unsigned int qos_type;
    unsigned int qos_adjust_interval;
    unsigned int qos_adjust_threshold1;
    unsigned int qos_adjust_step1;
    unsigned int qos_adjust_threshold2;
    unsigned int qos_adjust_step2;
    unsigned int qos_adjust_threshold3;
    unsigned int qos_adjust_step3;
    unsigned int qos_adjust_threshold4;
    
    
}QosControlMessage;

typedef enum AudioSampleFormat {
    AUDIO_SAMPLE_FMT_NONE = -1,
    AUDIO_SAMPLE_FMT_U8,          ///< unsigned 8 bits
    AUDIO_SAMPLE_FMT_S16,         ///< signed 16 bits
    AUDIO_SAMPLE_FMT_S32,         ///< signed 32 bits
    AUDIO_SAMPLE_FMT_FLT,         ///< float
    AUDIO_SAMPLE_FMT_DBL,         ///< double
    
    AUDIO_SAMPLE_FMT_U8P,         ///< unsigned 8 bits, planar
    AUDIO_SAMPLE_FMT_S16P,        ///< signed 16 bits, planar
    AUDIO_SAMPLE_FMT_S32P,        ///< signed 32 bits, planar
    AUDIO_SAMPLE_FMT_FLTP,        ///< float, planar
    AUDIO_SAMPLE_FMT_DBLP,        ///< double, planar
    
    AUDIO_SAMPLE_FMT_NB           ///< Number of sample formats. DO NOT USE if linking dynamically
}AudioSampleFormat;

typedef enum AudioCODECType {
    LSAudioCODECNONE = -1,
    LSAudioCODECAAC,
    LSAudioCODECSpeex,
    LSAudioCODECMP3,
    LSAudioCODECG711A,
    LSAudioCODECG711U
}AudioCODECType;

typedef enum VideoFormat{
    VIDEO_NV12 = 0,
    VIDEO_NV21,
    VIDEO_I420,
    VIDEO_BGRA32
    
}VideoFormat;//input source format

typedef enum VideoCODECType {
    LSVideoCODECNONE = -1,
    LSVideoCODECAVC,
    LSVideoCODECVP9,
    LSVideoCODECH265
}VideoCODECType;

//will conflict with libyuv::RotationMode, can get current rotationmode with cameraid.
//typedef enum RotationMode {
//    Rotate0 = 0,  // No rotation.
//    Rotate90 = 90,  // Rotate 90 degrees clockwise.
//    Rotate180 = 180,  // Rotate 180 degrees.
//    Rotate270 = 270,  // Rotate 270 degrees clockwise.
//
//    // Deprecated.
//    RotateNone = 0,
//    RotateClockwise = 90,
//    RotateCounterClockwise = 270,
//} RotationMode;

typedef struct SVideoParamContext{
    //deduce from input source
    int width;
    int height;
    int yStride;
    int uvStride;
    VideoFormat fmt;
    
    int bitrate;
    int framerate;
    
    int cameraid;
    //    RotationMode eRotationMode;
    
    int m_video_frame_count;
    
#ifdef __ANDROID__
    int encodeWidth;
    int encodeHeight;
#endif
    
    int m_video_CODEC_type;
    LSVideoRenderScaleMode videoRenderMode;
    
}SVideoParamContext;//video encode needed parameter, you can extented it

typedef struct SAudioParamContext{
    // for input audio frame overflow, we need backup the left buffer//
    unsigned int m_buflen_left;
    int m_frame_count;
    unsigned char *m_audio_encode_buffer;
    int nb_samples;
    
    int sample_rate;
    int channels;
    AudioSampleFormat fmt;
    uint64_t channel_layout;
    int bitrate;//output bitrate
    
    int m_audio_frame_count;
    
    int m_audio_CODEC_type;
}SAudioParamContext;
//~finished parame defined


//#ifdef __cplusplus

class IMediaLiveStream {
    
public:
    
    //Init output file format
    virtual int EXTAPI  InitOutMedia(char* oFilename, LSOutputFormatType oFmt, LSOutputStreamType oSt) = 0;
    
    //Add video transcoder based on ffmpeg api by lingzhu 2015-04-11
    virtual int EXTAPI  InitVideoStream(SVideoParamContext* pVideoParamCtx) = 0;
    virtual int EXTAPI  InitAudioStream(SAudioParamContext* pAudioParamCtx) = 0;
    
    //Just android need audio preprocess
#ifdef __ANDROID__
    virtual int EXTAPI InitAudioPreprocess(SAudioParamContext* pAudioParamCtx) = 0;
#endif
    virtual int EXTAPI InitVideoPreprocess(SVideoParamContext* pVideoParamCtx) = 0;
    
    
    virtual void EXTAPI GetDefaultVideoParamCtx(SVideoParamContext* pVideoParamCtx) = 0;
    virtual void EXTAPI GetDefaultAudioParamCtx(SAudioParamContext* pAudioParamCtx) = 0;
    
    virtual void EXTAPI SetVideoParamCtx(SVideoParamContext* pVideoParamCtx) = 0;
    
    
    virtual int EXTAPI  VideoStreaming(uint8_t* in_yuv, int64_t timestamp) = 0;
    
    virtual int EXTAPI  AudioStreaming(uint8_t* in_pcm, int bufLen, int64_t timestamp) = 0;
    
    
    virtual void EXTAPI  MixAudioStreaming(uint8_t* in_pcm, int bufLen, bool mixAudioEnable, int mixAudioVolume) = 0;
    //virtual int EXTAPI  PrintStatics(int arg1, int arg2, int arg3, int arg4, int arg5) = 0;
    
    
    //for HW Video Encoder: directly packet and send to RTMP.
    virtual int EXTAPI VideoPacketDataHighLevel(uint8_t* video_stream_buffer, int video_stream_size, int64_t timestamp) = 0;
    
    virtual int EXTAPI  ReleaseVideoStream() = 0;
    virtual int EXTAPI  ReleaseAudioStream() = 0;
    virtual int EXTAPI  UnitOutMedia() = 0;
    
    virtual void EXTAPI  SetAudioRelease() = 0;
    virtual void EXTAPI  SetVideoRelease() = 0;
    
    virtual void EXTAPI PauseSingleStream() = 0;
    virtual void EXTAPI ResumeSingleStream() = 0;
    virtual bool GetOutMediaHeaderWritten() = 0;
    
    /**
     * @brief   Set option for encoder, detail option type, please refer to enumurate ENCODER_OPTION.
     * @param   pOption option for encoder such as InDataFormat, IDRInterval, SVC Encode Param, Frame Rate, Bitrate,...
     * @return  CM_RETURN: 0 - success; otherwise - failed;
     */
    virtual int EXTAPI SetOption (LSMediaOption eOptionId, void* pOption) = 0;
    
    /**
     * @brief   Set option for encoder, detail option type, please refer to enumurate ENCODER_OPTION.
     * @param   pOption option for encoder such as InDataFormat, IDRInterval, SVC Encode Param, Frame Rate, Bitrate,...
     * @return  CM_RETURN: 0 - success; otherwise - failed;
     */
    virtual int EXTAPI GetOption (LSMediaOption eOptionId, void* pOption) = 0;
    
    virtual ~IMediaLiveStream() {}
    
#ifdef __ANDROID__
    virtual void EXTAPI SetJavaVM(JavaVM* javaVM) = 0;
#endif
};
//#endif
//typedef void (*lsMediaTraceCallback) (void* ctx, int level, const char* string);
typedef void (*lsMediaTraceCallback) (void* ctx, int level, const char* string);

int CreateMediaLiveStream(IMediaLiveStream** ppLiveStream, LSHardWareEncEnable eHrdEncEnable);
void DestroyMediaLiveStream(IMediaLiveStream* pLiveStream);

int CheckRtmpUrlValued(char* filename);

#endif
