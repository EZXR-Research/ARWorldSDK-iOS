//
//  UnityARDataDefine.h
//  OasisUnityPlugin
//
//  Created by Carmine on 2021/7/26.
//  Copyright © 2021 Carmine. All rights reserved.
//

#ifndef UnityARDataDefine_h
#define UnityARDataDefine_h

#ifdef __cplusplus
extern "C" {
#endif

#import <Foundation/Foundation.h>

/// 录屏开始通知
extern NSString * const kIARRecordStart;
/// 录屏成功通知
extern NSString * const kIARRecordSuccess;
/// 录屏成功通知
extern NSString * const kIARRecordFailed;
/// 录屏停止通知
extern NSString * const kUnityARRecordShouldStop;
/// 录屏超时
extern NSString * const kUnityARRecordViewReachedTimeout;
/// 请求log
extern NSString * const kPluginRequestLogEnabled;
/// Unity初始化结束
extern NSString * const kPluginUnityInitOK;

/// 权限状态，屏蔽 Android 和 iOS 平台差异
enum IAuthorizationStatus {
    IAuthorizationStatusNotNotDetermined = 0,
    IAuthorizationStatusDenied = 1,
    IAuthorizationStatusAuthorized = 2,
};

/// 权限类型，目前只用到了下面4种
enum IAuthorizationType {
    IAuthorizationTypeCamera = 1,
    IAuthorizationTypeAudio = 2,
    IAuthorizationTypeAlbum = 3,
    IAuthorizationTypeGPS = 4,
//    IAuthorizationTypeBluetooth = 5, 蓝牙比较特殊，iOS 13之前不能同步返回
};

/// 媒体类型，目前只有 image 、 video
enum IMediaType {
    IMediaTypeImage = 1,
    IMediaTypeVideo = 3,
};

/// image upload state， for NOS
enum IImageUploadStatus {
    IImageUploadStatusStart = 0,
    IImageUploadStatusUploading = 1,
    IImageUploadStatusSuccess = 2,
    IImageUploadStatusFailed = 3
};

/// upload entity， for NOS
struct ImageUploadStatus {
    enum IImageUploadStatus state;
    int progress;
    const char * nosAddress;
};

/// GPS 状态
enum IGPSResultStatus {
    IGPSResultStateSuccess = 0,
    IGPSResultStateGPSOff = 1,
    IGPSResultStateError = 2
};

/// GPS 的定位结果，包含经纬度，以及当前的 GPS 状态
struct IGPSResult {
    enum IGPSResultStatus status;
    double latitude;
    double longitude;
};

/// 客户端侧触发的交互事件，用于告知 unity 。
/// ！！！ 重点 ！！！
enum IUserEventType {
    IUserEventTypeExit = 0,
    
    /// 导航相关
    IUserEventTypeNaviStop = 100,
    /// 跨楼层过程中，用户选择到达目标楼层
    IUserEventTypeCrossStairArrive = 101,
    
    /// 拍照录屏
    IUserEventTypeRecordSuccess = 200,    // 录屏成功
    IUserEventTypeRecordFail = 201,       // 录屏失败
    IUserEventTypeRecordStart = 202,      // 开始录屏
    IUserEventTypeRecordStop = 203,       // 结束录屏
    IUserEventTypeTakePhoto = 204,        // 拍照
    IUserEventTypeRecordExit = 205,        // 录屏 UI 隐藏，unity 侧需要监听此事件，还原显示状态
    
    /// 音频、视频
    IUserEventTypeAudioPause = 300,        // 音频暂停
    IUserEventTypeAudioResume = 301,        // 音频恢复
    IUserEventTypeVideoPause = 303,        // 视频暂停，保留使用
    IUserEventTypeVideoResume = 304,        // 视频恢复。保留使用
    
    /// Log Level
    IUserEventTypeLogLevelVerbose = 400,
    IUserEventTypeLogLevelDebug = 401,
    IUserEventTypeLogLevelWarn = 402,
    IUserEventTypeLogLevelError = 403,
    IUserEventTypeLogLevelNone = 404,
    
    IUserEventTypeCloudRelocation = 501, // 通知unity重新发起云定位
};

/// 导航类型
enum INavigationType {
    INavigationTypePlan = 0, // 路径规划
    INavigationTypeNavi = 1, // 路径导航
    INavigationTypeNormal = 2, // 默认
};

/// AR 场景类型
typedef NS_ENUM(NSInteger, IAREventType) {
    /// 场景切换
    IAREventTypeSceneSuspendEnter = 100, // 进入挂起
    IAREventTypeSceneSuspendExit = 101, // 退出挂起
    IAREventTypeSceneAttachEnter = 103, // 进入叠加
    IAREventTypeSceneAttachExit = 104, // 退出叠加
    IAREventTypeSceneUnchangedEnter = 105, // 进入unchange，保留吧，暂时用不到
    IAREventTypeSceneUnchangedExit = 106, // 退出unchange，保留吧，暂时用不到
    
    IAREventTypeLoadMainContentSuccess = 201,   // 成功加载主内容
    IAREventTypeExitMainContent = 202,  // 退出主内容
    IAREventTypeExitMainContentError = 203,  // 退出主内容
    IAREventTypeContentLoading = 204,  // AR场景正在加载
    IAREventTypeContentLoadingCompleted = 205,  // AR场景加载完成
    
    IAREventTypeEnableRecordOrPhoto = 301, // 内容唤起拍照录屏
    IAREventTypeDisableRecordOrPhoto = 302, // 内容停止拍照录屏 （保留，暂不实现）
    
    IAREventTypeCloudRelocation = 401, // 2d地图模式重定位请求
};

/// AR 场景类型
typedef NS_ENUM(NSInteger, IARSceneLoadingType) {
    IARSceneLoadingTypeFullScreen = 0,      // 全屏loading且不透明
    IARSceneLoadingTypeFullMask = 1,        // 加载mask
    IARSceneLoadingTypeUnloading = 2,       // 场景卸载进度类型
};

/// 外部导航的出行方式
enum IExternalNavMode {
    IExternalNavModeWalking = 0, // 步行
    IExternalNavModeTransit = 1, // 公共交通
    IExternalNavModeRiding = 2, // 骑行
    IExternalNavModeDriving = 3, // 驾车
};

#ifdef __cplusplus
}
#endif

#endif /* UnityARDataDefine_h */
