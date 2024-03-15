//
//  AROasisUnityPrepareOption.h
//  InsightSDK
//
//  Created by Dikey on 2020/11/6.
//  Copyright © 2020 DikeyKing. All rights reserved.
//

#import <Foundation/Foundation.h>

@class AROasisUnityLandmarker;
@class AROasisUnityRespLandmarker;

/// 坐标系
typedef NS_ENUM(NSUInteger, AROasisUnityCoordiType) {
    /// 1-GCJ02-----------火星坐标系
    AROasisUnityCoordiTypeGCJ02 = 1,
    /// 2-WGS84-----------大地坐标系
    AROasisUnityCoordiTypeWGS84 = 2,
    /// 3-BD09------------百度坐标系
    AROasisUnityCoordiTypeBD09 = 3,
    /// 4-mapbar----------图吧私有坐标系
    AROasisUnityCoordiTypeMapbar = 4
};

/**
 download progress callback

 @param downloadProgress 下载进度
 */
typedef void(^ARODownloadProgressBlock)(NSProgress *downloadProgress);

/**
  error call back

 @param error NSError
 */
typedef void(^AROErrorBlock)(NSError *error);

/**
 Finish callback

 @param object updateBlock
 */
typedef void(^AROFinishBlock)(id object);

/**
 Finish callback

 @param object updateBlock
 */
typedef void(^AROasisUnityLandmarkerBlock)(NSError *error, AROasisUnityLandmarker *landmarker);

@interface AROasisUnityPrepareOption : NSObject

/**
 需要请求的内容ID
 */
@property (assign,nonatomic) int cid;

/// download progress
@property (nonatomic, copy) ARODownloadProgressBlock progressBlock;

/// finish block
@property (nonatomic, copy) AROasisUnityLandmarkerBlock completionHandler;

/**
 是否需要LBS;
 
 某些场景（和产品确认是否有）增加了LBS验证，ARCode限定了使用的地理位置
 如果需要处理，参考以下代码设置
 */
@property (assign, nonatomic) BOOL needLBS;

/**
 1-GCJ02-----------火星坐标系
 2-WGS84-----------大地坐标系，默认
 3-BD09------------百度坐标系
 4-Sogou-----------搜狗私有坐标系，使用墨卡托
 5-mapbar----------图吧私有坐标系
 see https:ardoc.ai.163.com/#sort=dongjian&doc=3_ARSDK/3_1/iOSFAQ.md for detail
 */
@property (assign, nonatomic) AROasisUnityCoordiType coordiType;

/**
 经度
 */
@property (assign, nonatomic) double longitude;

/**
 纬度
 */
@property (assign, nonatomic) double latitude;

/**
 scanned QRCode
 */
@property (nonatomic, copy) NSString *qrCode;

- (instancetype)initWithCid:(int)cid;

/**
 used to scanned QRCode
 */
- (instancetype)initWithQRCode:(NSString *)qrCode;

/**
used to download QRCode
*/
- (instancetype)initWithQRCodeLandmaker:(AROasisUnityRespLandmarker *)resplandmarker;

@end
