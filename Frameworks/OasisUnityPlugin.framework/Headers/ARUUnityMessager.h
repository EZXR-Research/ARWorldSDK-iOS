//
//  ARUUnityMessager.h
//  OasisUnityPlugin
//
//  Created by Carmine on 2020/3/30.
//  Copyright © 2020 Carmine. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UnityPluginAPI.h"
#import "OasisUnityPluginRequest.h"

NS_ASSUME_NONNULL_BEGIN

extern NSString * const kUnityPickPhotoFromLibrary;
extern NSString * const kUnityUpdateUserLocation;
extern NSString * const kUnityRecievedPoiList;
extern NSString * const kUnityUpdateNavigationPath;
extern NSString * const kUnityExitNavigation;
extern NSString * const kUnitySetMapInvisiable;
extern NSString * const kUnitySetMapVisiable;
extern NSString * const kUnitySetCaptureInvisiable;
extern NSString * const kUnitySetCaptureVisiable;
extern NSString * const kUnityRecievedGeoJSONPath;
extern NSString * const kUnityStartAddPluginView;
extern NSString * const kUnityReceivedAREvent;
extern NSString * const kUnityScanncedQRCode;
extern NSString * const kUnityRecievedCaptureImage;
extern NSString * const kUnityCheckARSceneState;

@interface ARUUnityMessager : NSObject

+ (instancetype)shared;
- (BOOL)callbackReady;
- (void)handleCallbackReady;
- (void)initWithAuthorizationCallback:(IAuthorizationStatusCallback)pCallback;

@property (nonatomic, unsafe_unretained) IAuthorizationStatusCallback authorizationCallback;
@property (nonatomic, unsafe_unretained) IUploadCallback uploadCallback;
@property (nonatomic, unsafe_unretained) IPickImageCallback pickImageCallback;
@property (nonatomic, unsafe_unretained) INavigationCallback navigationCallback;
@property (nonatomic, unsafe_unretained) IGPSCallback gpsCallback;
@property (nonatomic, unsafe_unretained) ILocationSwitchCallback gpsServiceCallback;
@property (nonatomic, assign) BOOL requestGPSServiceStatusChange; // 配合 gpsServiceCallback使用，很脏的参数
@property (nonatomic, unsafe_unretained) IUserEventCallback eventCallback;
@property (nonatomic, unsafe_unretained) IScannedQRCodeCallback scannedQRCodeCallback;
@property (nonatomic, unsafe_unretained) IARResourceLocalPathCallback arPathCallback;
@property (nonatomic, unsafe_unretained) ICloudLocationCallback cloudLocCallback;
@property (nonatomic, unsafe_unretained) IDoScriptCallback arScriptCallback;
@property (nonatomic, unsafe_unretained) IPoiStatusCallback poiStatusCallback;
@property (nonatomic, unsafe_unretained) IMainSceneStatusCallback mainSceneStatusCallback;
@property (nonatomic, unsafe_unretained) ICommonDataCallback commonDataCallback;

/// 外部函数指针
@property (nonatomic, unsafe_unretained) ICloudLocationRequestHandler cloudLocRequestHandler;

/// 用于回调GPS等传感器数据
@property (nonatomic, unsafe_unretained) ISensorDataCallback sensorDataCallback;

/// 用于回调蓝牙当前状态
@property (nonatomic, unsafe_unretained) IBluetoothStatusCallback bluetoothStatusCallback;

#pragma mark - 注册一个外部的云端定位函数
- (void)registerCloudRequestHandler:(ICloudLocationRequestHandler)handler;
/// 发送云定位数据
- (void)postLocCloudRequest:(NSString *)jpegStr protoInfo:(NSString *)protoStr;
/// 处理u3d的内容事件
- (void)handleU3DEvent:(NSUInteger)type params:(NSString *)params;
/// 处理u3d的加载进度
- (void)handleUnityLoadingProgress:(NSNumber *)progress
                          userData:(NSString *)userData
                       loadingType:(enum IARSceneLoadingType)type;
/// 处理u3d的加载完成
- (void)handleUnityLoadingProgressCompleted:(NSNumber *)delay
                                   userData:(NSString *)userData
                                loadingType:(enum IARSceneLoadingType)type;

#pragma mark - Request Register

// 网络相关回调
@property (nonatomic, unsafe_unretained) IHttpRequestCallback dataRequestCallback;

- (void)registerHttpDataHandler:(IHttpRequestCallback)handler;

// 下载相关函数回调
@property (nonatomic, unsafe_unretained) IHttpDownloadSuccessCallback downloadSuccessCallback;
@property (nonatomic, unsafe_unretained) IHttpDownloadProgressCallback downloadProgressCallback;
@property (nonatomic, unsafe_unretained) IHttpDownloadFailCallback downloadFailCallback;


/// 注册下载相关回调
/// @param successHandler 下载成功回调
/// @param progressHandler 下载进度回调
/// @param failedHandler 下载失败回调
- (void)registerHttpDownloadHandler:(IHttpDownloadSuccessCallback)successHandler
                    progressHandler:(IHttpDownloadProgressCallback)progressHandler
                      failedHandler:(IHttpDownloadFailCallback)failedHandler;

#pragma mark - Authorization

/// camera
- (enum IAuthorizationStatus)unity_CameraAuthorizationStatus;
- (void)unity_RequestCameraAuthorization;
/// audio
- (enum IAuthorizationStatus)unity_AudioAuthorizationStatus;
- (void)unity_RequestAudioAuthorization;
/// album
- (enum IAuthorizationStatus)unity_AlbumAuthorizationStatus;
- (void)unity_RequestAlbumAuthorization;
/// GPS
- (enum IAuthorizationStatus)unity_GPSAuthorizationStatus;
- (BOOL)unity_locationServicesEnable;
//- (enum IAuthorizationStatus)unity_BluetoothAuthorizationStatus;

- (void)unity_RequestGPSAuthorization;
//- (void)unity_RequestBluetoothAuthorization;
/// pick image
- (void)unity_pickImageFromAlbum;
/// save image
- (void)unity_saveMediaFile:(NSString *)mediaPath type:(enum IMediaType)mediaType;
/// take photo
- (void)unity_takePhoto:(NSString *)imagePath;
/// upload image
- (void)unity_uploadImageToNos:(NSString *)path token:(NSString *)token object:(NSString *)nosObject bucket:(NSString *)bucket;

#pragma mark - common

- (void)handleCommonMessage:(int)type data:(id)data;
- (void)observeCommonDataCallback;

#pragma mark - Support

/// save ar engine version
- (void)saveAREngineVersion:(NSInteger)version;
/// get ar engine version
- (NSInteger)getAREngineVersion;
/// detect WiFi environment
- (BOOL)unity_isWifi;
/// detect network available
- (BOOL)unity_isNetworkAvailable;
/// open host app's setting page
- (void)unity_openSettingPage;
/// check device is x or not
- (BOOL)unity_nbIsBottomBarSeries;
/// show toast
- (void)unity_nbMakeToast:(NSString *)text duration:(int)duration __attribute__((deprecated("unity_nbMakeToast has been deprecated， please use [AROasisUnityEvent_Toast = 10005] event instead.")));
/// vibrate device
- (void)unity_vibrate;



#pragma mark - Naviagtion

/// 接收unity传过来的geoJSON文件路径，用于加载地图
/// @param mapDataString 楼层描述信息
- (void)unity_load2DMapData:(NSString *)mapDataString;

/// 获取GPS位置信息
- (void)unity_getCurrentGPS;

/// 设置用户定位，算法传入
- (void)unity_update2DMapLocation:(NSString *)locationJSON;

/// 设置POI列表信息，算法传入
- (void)unity_set2DMapPoiList:(NSString *)poiListJsonString;

/// 设置导航信息，算法传入
- (void)unity_update2DMapNaviPath:(NSString *)navListJsonString type:(enum INavigationType)type;

/// 退出导航，unity调起
- (void)unity_exit2DNavigation;

/// unity控制地图页面的导航视图，是否显示
/// @param visiable display or not
- (void)unity_set2DMapVisibility:(BOOL)visiable;

/// unity控制录屏页面的视图，是否显示
/// @param visiable display or not
- (void)unity_setRecordViewVisibility:(BOOL)visiable;

/// unity内容交互中，发起的用户AR事件
- (void)unity_setAREvent:(enum IAREventType)eventType;

/// unity 进度
- (void)handleU3DEvent:(NSString *)user_data params:(float)progress delay:(float)delay;

#pragma mark ------ 语音转文字 ------

@property (nonatomic, unsafe_unretained) IAudioRecognitionCallback audioRecognitionCallback;
- (void)unity_setAudioRecognitionKey:(NSString *)key secret:(NSString *)secret;
- (void)unity_activeAudioRecognition;
- (void)unity_closeAudioRecognition;

#pragma mark ------ 声音频率检测 ------

@property (nonatomic, unsafe_unretained) IAudioFrequenceCallback audioFrequenceCallback;
- (void)unity_startRecogniseAudioFrequence;
- (void)unity_stopRecognisingAudioFrequence;

#pragma mark - Sensor

/// 在开始蓝牙传感器前必需调用
- (void)saveBluetoothRelocKey:(NSString *)key
          bluetoothRelocMapId:(NSString *)mapId;

/// 开始传感器
- (void)startUpdate:(OasisUnityPluginSensorType)sensorType;

/// 结束传感器
- (void)stopUpdate:(OasisUnityPluginSensorType)sensorType;

/// 获取数据
- (void)requestSensorData:(OasisUnityPluginSensorType)sensorType;

#pragma mark - 蓝牙状态

- (void)unity_getBluetoothStatus;

#pragma mark - 场景资源状态检查

- (void)unity_checkSceneState:(int)cid;

@end

NS_ASSUME_NONNULL_END

