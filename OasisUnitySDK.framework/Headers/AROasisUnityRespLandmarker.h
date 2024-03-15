//
//  ARORespLandMarkers.h
//  InsightSDK
//
//  Created by Dikey on 2020/11/4.
//  Copyright © 2020 DikeyKing. All rights reserved.
//

#import <Foundation/Foundation.h>

@class AROasisUnityPrepareOption;

typedef NS_ENUM(NSUInteger, ARORespLandmarkerType) {
    ARORespLandmarkerTypeContent = 1,
    ARORespLandmarkerTypeSubContent = 2,
};
@class AROasisUnityLandmarker;

@interface AROasisUnityRespLandmarker : NSObject

@property (nonatomic, strong) AROasisUnityLandmarker *content;

/// 仅在 queryByQRCode 需要switch case 处理
@property (nonatomic, assign) ARORespLandmarkerType resultType;

/// 用于回调
@property (nonatomic, strong) AROasisUnityPrepareOption *aro_option;

@end
