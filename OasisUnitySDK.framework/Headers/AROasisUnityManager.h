//
//  AROasisUnityManager.h
//  InsightSDK
//
//  Created by Dikey on 2020/11/6.
//  Copyright © 2020 DikeyKing. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "AROasisUnityDataDefine.h"

@interface AROasisUnityManager : NSObject

#pragma mark - Init & Register

/**
 Appple A9 & iOS 12.0 required ; x86 simulator is not supported；A11 and later is recommended （iPhone 8、iPhone X）
 需要A10及以上处理器的机型（iPhone 7 及以上）；系统 iOS 11.0 及以上； 不支持x86架构；建议A11及以上（iPhone 8、iPhone X）
  */
+ (BOOL)isSDKSupported;

/**
 SDK 初始化需要一段时间，此期间无法支持加载资源
 调用 AR 相关方法时，请前置此状态判断
  */
- (BOOL)isReadyToUse;

+ (instancetype)shared;

/**
 register SDK ，return error if key is invalide
 注册SDK
 
 @param key key
 @param secret secret
 @param launchOptions Application LaunchOptions
 @return return error if key is invalide ，nil when OK
 */
- (NSError *)registerAppKey:(NSString *)key
                  appSecret:(NSString *)secret
              launchOptions:(NSDictionary *)launchOptions;

#pragma mark - Specified Data

/// get landmark by cid
/// @param cid 场景ID
/// @param finishBlock AROasisUnityRespLandmarker
/// @param failedBlock 错误回调
- (void)queryLandmarker:(int)cid
                  onSuc:(void(^)(AROasisUnityRespLandmarker *result))finishBlock
                 failed:(void(^)(NSError *error))failedBlock;

#pragma mark - List Data

/**
 get landmarkers near by
 获取周围 AROasisUnityLandmarker

 @param option 传入当前GPS信息
 @param finishBlock AROasisUnityLandmarker数组
 @param failedBlock 错误回调
 */
- (void)queryLandmarkersNearby:(AROasisUnityNearbyLandmarkersPrepareOption *)option
                         onSuc:(void(^)(NSArray<AROasisUnityLandmarker *> *landmarkers))finishBlock
                        failed:(void(^)(NSError *error))failedBlock;

/**
 get all main landmarkers , see AROasisUnityLandmarkersPrepareOption for detail
 获取所有 AROasisUnityLandmarker，AROasisUnityLandmarkersPrepareOption 查看详情
 
 @param option 传入当前GPS信息
 @param finishBlock AROasisUnityLandmarker数组
 @param failedBlock 错误回调
 */
- (void)queryLandmarkers:(AROasisUnityLandmarkersPrepareOption *)option
                   onSuc:(void(^)(NSArray<AROasisUnityLandmarker *> *landmarkers))finishBlock
                  failed:(void(^)(NSError *error))failedBlock;

/**
 Get Content List by tag
 查询主内容列表（根据标签查询）
 
 @param option 标签ID列表，以半角逗号分隔。任意一个标签匹配即可。使用 initWithTagIds 进行初始化
 @param finishBlock AROasisUnityLandmarker数组
 @param failedBlock 错误回调
 */
- (void)queryLandmarkersByTags:(AROasisUnityLandmarkersPrepareOption *)option
                         onSuc:(void(^)(NSArray<AROasisUnityLandmarker *> *landmarkers))finishBlock
                        failed:(void(^)(NSError *error))failedBlock;

/**
 Get Hold Content List
 查询独立事件列表
 
 @param finishBlock AROasisUnityHoldContent数组
 @param failedBlock 错误回调
 */
- (void)queryHoldContentsOnSuc:(void(^)(NSArray<AROasisUnityHoldContent *> * contents))finishBlock
                        failed:(void(^)(NSError *error))failedBlock;

#pragma mark - Download

/**
 get pid ar product
 根据Pid（ProductID）获取获取 ARProduct
 
 @param options ARPrepareOptions
 @param progressBlock ARDownloadProgressBlock
 @param completionHandler ARCompletionBlock
 */
- (void)prepareLandmarkerWithOptions:(AROasisUnityPrepareOption *)options
                   downloadProgress:(ARODownloadProgressBlock)progressBlock
                         completion:(AROasisUnityLandmarkerBlock)completionHandler;

/**
 stop prepare resource
 停止下载

 @param cid landmark ID
 */
- (void)stopPrepare:(int)cid;

#pragma mark - Start/Stop

/**
 start Running landmarker，only can run one AR case
 开始 运行 landmarker, 同时只能运行单个AR场景
 
 @param landmarker landmarker should downloaded
 @param AROasisStartBlock use for add ARView, handle Error
 @param eventCallback use for communicating with
 @param loadEventCallback use for load event handling
 */
- (void)startRunning:(AROasisUnityLandmarker *)landmarker
       stateCallback:(AROasisStartBlock)stateCallback
       eventCallback:(AROasisUnityEventBlock)eventCallback
        loadCallback:(AROasisLoadEventBlock)loadEventCallback;

/**
  Stop AR Engine async.
 */
- (void)stopAROasisWithNotifyEngine:(BOOL)notifyEngine;

/**
 stop and finished
*/
- (void)stopAROasis:(void(^)(void))finished __attribute__((deprecated));

/**
 get AROasisView,
 ! should use weak attribute to avoid retain cycle
 
 获取AR视图，
 ！需要使用weak属性用来避免循环引用
 
 @param UIView
 */
- (UIView *)getOasisView;

#pragma mark - Delete

/**
  delete resource in disk
  删除本地资源
 */
- (BOOL)removeResource:(int)cid;

/**
  delete all downloaded resource
  删除本地所有资源
 */
- (BOOL)removeAllResources;

#pragma mark - Helper

/**
  if is downloaded
  判断是否本地已下载

 @param cid contentID
 */
- (BOOL)isDownloadedLandmarker:(int)cid;

/**
  get local landmarker,return nil if not downloaded
  判获取本地的landmarker，没有会返回nil

 @param cid contentID
 */
- (AROasisUnityLandmarker *)getLocalLandmarker:(int)cid;

/**
 check update, if want to keep version at latest version, ignore checkUpdate API, prepareLandmarkerWithOptions is recommended to use.
 检测是否有更新，如果需要保持版本最新，会更建议直接调用 prepareLandmarkerWithOptions，不需要使用此接口
 
 @param cid cid
 @param resultBlock  hasUpdate：是否有更新，会在成功回调时候调用该block；result 为留空参数，未使用
 @param failedBlock 检测更新失败
*/
- (void)checkUpdate:(int)cid
             result:(void(^)(BOOL hasUpdate, id result))resultBlock
             failed:(void(^)(NSError *error))failedBlock;

#pragma mark - QRCode

/**
 query content By QRCode, use  -initWithQRCode  to initialize AROasisUnityPrepareOption
 查询内容（扫描二维码），AROasisUnityPrepareOption 使用 -initWithQRCode 方法初始化
 
 @param option qrCode use -initWithQRCode
 @param finishBlock finish callback
 @param failedBlock failed callback
*/
- (void)queryByQRCode:(AROasisUnityPrepareOption *)option
                onSuc:(void(^)(AROasisUnityRespLandmarker *result))finishBlock
               failed:(void(^)(NSError *error))failedBlock;

#pragma mark - AR Script

/**
 use ARScript to communicate with AR Scene
 native端可以通过执行脚本函数，与AR场景通信；
 可以执行的脚本函数，详情请看文档

 @param scriptName 脚本名
 @param param 传参
 @param callback 内容回调，暂未实现
 */
- (void)runOasisScript:(NSString *)scriptName
                 param:(NSString *)param
              callback:(void(^)(AROasisUnityEvent *event))callback;

#pragma mark - Snapshot

/**
 发起截屏，异步操作
 结果详见 startRunning 的 AROasisUnityEventBlock 回调
 事件对应：AROasisUnityEvent_Function_ScreenShot
 */
- (void)screenshot;

#pragma mark - Record Video

/**
 发起录屏
 结果详见 startRunning 的 AROasisUnityEventBlock 回调
 事件对应：AROasisUnityEvent_Function_ScreenShot
 */
- (void)startRecord;

/**
 结束录屏
 结果详见 startRunning 的 AROasisUnityEventBlock 回调
 事件对应：AROasisUnityEvent_Function_ScreenShot
 */
- (void)stopRecord;

#pragma mark - Utility

/**
 setLogLevel, default is AROLogLevelERROR in release
 设置Log输出等级, 默认 AROLogLevelERROR in release

 @param scriptName 脚本名
 @param param 传参
 @param level 内容回调，暂未实现
 */
+ (void)setLogLevel:(AROasisUnityLogLevel)level;

/**
 a.b.c format : as like 1.0.0 1.0.1 1.1.0
 a.b.c 格式：比如 1.0.0 1.0.1 1.1.0
  */
+ (NSString *)getSDKVersion;

/**
 获取算法库版本
 */
+ (NSString *)getEngineVersion;

@end
