//
//  AROasisUnityLandmarker.h
//  InsightSDK
//
//  Created by Dikey on 2020/11/3.
//  Copyright © 2020 DikeyKing. All rights reserved.
//

#import <Foundation/Foundation.h>

@class AROasisUnityMaterial;
@class AROasisUnityTag;
@class AROasisUnityCentroid;

typedef NS_ENUM(NSUInteger, AROasisUnityLandmarkerOrientation) {
    AROasisUnityLandmarkerOrientationPortrait = 1,
    AROasisUnityLandmarkerOrientationLandscapeRight = 3
};

@interface AROasisUnityLandmarker : NSObject

/// 内容id
@property (nonatomic, assign) int cid;

/// 封面url
@property (nonatomic, copy)   NSString *coverImageUrl;

/// 内容快照ID
@property (nonatomic, strong) NSString *name;

/// 总的下载大小，单位是KB，Integer
@property (nonatomic, assign) NSInteger totalSize;

@property (nonatomic, assign) AROasisUnityLandmarkerOrientation orientation;

/// 最后更新时间，时间戳，精确到毫秒
@property (nonatomic, assign) NSInteger updateTime;

/// 下载前是否提示
@property (nonatomic, assign) BOOL promptBeforeDownload;

/// 是否启用导航
@property (nonatomic, assign) BOOL navEnabled;

///  【必填*】区域中心点geojson
@property (nonatomic, strong) AROasisUnityCentroid *centroid;

#pragma mark - Local Resource Necessary.

/// 【可选】外部必要参数，供加载本地资源，传入一个JSON Object
@property (nonatomic, strong) id externalJSON;

/// 唯一ID
- (NSString *)uid_string;

/// 内容id
- (NSString *)cid_string;

/// 快照id
- (NSString *)sid_string;

- (BOOL)aro_local;

/// 资源是否已下载
- (BOOL)aro_downloaded;

- (BOOL)isMaterialDownloaded:(AROasisUnityMaterial *)material
                         sid:(int)sid;
/// pid 对应的下载目录
- (NSString *)getContentFilePath;

/// 获取楼层GEO files
- (NSString *)getLevelsPath;

/// 获取样式文件目录
- (NSString *)getStyleDir;

/// 获取样式配置文件
- (NSString *)getStyleFilePath;

/// use for local resource bundle only
/// @param path use for local Landmarker
/// @param url use for cloudReposition
- (instancetype)initWithLocalResource:(NSString *)path
                   cloudRepositionURL:(NSString *)url;

/// use for decode local resource string.
- (instancetype)initWithJSON:(id)json localPath:(NSString *)localPath;

@end



