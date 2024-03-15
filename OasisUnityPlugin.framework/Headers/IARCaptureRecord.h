//
//  IARCaptureRecord.h
//  camera
//
//  Created by ShaoWenjian on 2017/10/26.
//  Copyright © 2017年 Netease. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

typedef NS_ENUM(NSUInteger, IARCaptureRecordResult) {
    IARRecordInitSuccess               = 0,
    IARRecordInitFail                  = 1,
    IARRecordError                     = 2,
    IARRecordSaveSuccess               = 3,
    IARRecordStart                     = 4,
    IARRecordAuthorizationStatusDenied = 5,
    IARRecordDonotStart                = 6,
};

typedef void (^CaptureRecordBlock)(IARCaptureRecordResult result);

static BOOL saveVideoAutomatically = NO;

@interface IARCaptureRecord : NSObject

+ (void)setSaveVideoAutomatically:(BOOL)autoSave;

// native录制
- (id)initWith:(NSString *)moviefileURL resultBlock:(CaptureRecordBlock)block;
- (void)startRecording;
- (void)stopRecording;
- (void)writeSampleBuffer:(CMSampleBufferRef)sampleBuffer ofType:(NSString *)mediaType;

// unity录制
- (id)initWith:(NSString *)moviefileURL imageSize:(CGSize)size scale:(CGFloat)scale resultBlock:(CaptureRecordBlock)block;
- (void)startRecordingUnity;
- (void)stopRecordingUnity;
- (void)writeBytePixels:(UInt8 *)pBytes size:(NSInteger)size timestamp:(CFTimeInterval)timestamp;
- (void)writeTextureHandle:(void *)textureHandle timestamp:(CFTimeInterval)timestamp;


///清空本地录制的视频
+ (void)ClearVideo;

@end
