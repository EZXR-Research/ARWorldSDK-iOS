//
//  AROasisUnityNearbyLandmarkersPrepareOption.h
//  InsightSDK
//
//  Created by Dikey on 2020/11/19.
//  Copyright © 2020 DikeyKing. All rights reserved.
//

#import "AROasisUnityPrepareOption.h"

/// 配合 queryLandmarkersNearby 接口使用
@interface AROasisUnityNearbyLandmarkersPrepareOption : AROasisUnityPrepareOption

/// 指定初始化方法，需要传入经纬度信息
/// 一般 queryLandmarkersNearby 时候使用
- (instancetype)initWithlongitude:(double)longitude
                         latitude:(double)latitude;

/// 指定初始化方法，需要传入经纬度信息，一般不需要特殊设置 AROCoordiType
- (instancetype)initWithCoordiType:(AROasisUnityCoordiType)coordiType
                         longitude:(double)longitude
                          latitude:(double)latitude;

@end

/// 配合 queryLandmarkers 接口使用
@interface AROasisUnityLandmarkersPrepareOption : AROasisUnityNearbyLandmarkersPrepareOption

/// 距离当前gps中心的距离，单位米，
/// ⚠️ 须配合 queryLandmarkers 接口使用
/// ⚠️ 在queryLandmarkersNearby方法中distance不会生效
@property (nonatomic, readonly, assign) double distance;

/// tag 唯一表示
@property (nonatomic, readonly, copy) NSString *tagIds;

- (instancetype)initWithCoordiType:(AROasisUnityCoordiType)coordiType
                         longitude:(double)longitude
                          latitude:(double)latitude
                       maxDistance:(double)distance
                            tagIds:(NSString *)tagIds;

- (instancetype)initWithTagIds:(NSString *)tagIds;

@end
