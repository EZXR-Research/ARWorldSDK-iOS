//
//  AROasisHoldContent.h
//  OasisUnitySDK
//
//  Created by Carmine on 2021/12/8.
//  Copyright © 2021 DikeyKing. All rights reserved.
//

#import "AROasisUnityLandmarker.h"

NS_ASSUME_NONNULL_BEGIN

@interface AROasisUnityHoldContent : NSObject

/// 内容id
@property (nonatomic, assign) int cid;
/// 快照id
@property (nonatomic, assign) int sid;
/// 内容名称
@property (nonatomic, strong) NSString *name;
/// 总的下载大小，单位是KB，Integer
@property (nonatomic, assign) NSInteger totalSize;
/// 方向
@property (nonatomic, assign) AROasisUnityLandmarkerOrientation orientation;
/// 封面url
@property (nonatomic, copy)   NSString *coverImageUrl;
/// 最后更新时间，时间戳，精确到毫秒
@property (nonatomic, assign) NSInteger updateTime;
/// 下载前是否提示
@property (nonatomic, assign) BOOL promptBeforeDownload;

@end

NS_ASSUME_NONNULL_END
