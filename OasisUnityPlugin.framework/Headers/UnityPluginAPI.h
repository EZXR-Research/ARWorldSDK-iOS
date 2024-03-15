//
//  UnityPluginAPI.h
//  OasisUnityPlugin
//
//  Created by Carmine on 2020/3/30.
//  Copyright © 2020 Carmine. All rights reserved.
//

#ifndef UnityPluginAPI_h
#define UnityPluginAPI_h

#import <Foundation/Foundation.h>
#import "UnityARDataDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

/// 云端重定位，图片时间戳
typedef struct InsightARCloudLocRequestMeta{

    double timestamp;           // the query jpg's timestamp
}InsightARCloudLocRequestMeta;
/// 云端重定位，本地请求
typedef struct InsightARCloudLocRequest
{
    InsightARCloudLocRequestMeta meta;  // query struct

    const void *jpgPtr;         // jpg ptr
    int byteLength;             // jpg ptr byte length
    const void *reqestInfoPtr;         // proto ptr
    int reqestInfoLength;             // proto byte length
} InsightARCloudLocRequest;
/// 云端重定位，元数据
typedef struct InsightARCloudLocResultMeta{

    int status;                 // the result of cloud loc.
    double timestamp;           // the query jpg's timestamp
}InsightARCloudLocResultMeta;
/// 云端重定位结果
typedef struct InsightARCloudLocResult
{
    InsightARCloudLocResultMeta meta;   // result strcut

    const void *resultInfoPtr;         // proto ptr
    int resultLength;             // proto byte length

} InsightARCloudLocResult;

/// 权限回调
typedef void (* IAuthorizationStatusCallback)(enum IAuthorizationType type, enum IAuthorizationStatus state);
/// 上传结果回调
typedef void (* IUploadCallback)(struct ImageUploadStatus status);
/// 选择媒体回调
typedef void (* IPickImageCallback)(const char *path);
/// 导航回调
typedef void (* INavigationCallback)(enum INavigationType type, const char *poiName);
/// GPS 结果回调
typedef void (* IGPSCallback)(struct IGPSResult location);
/// UI 用户事件回调
typedef void (* IUserEventCallback)(enum IUserEventType type);
/// 扫码回调，核销项目用，保留
typedef void (* IScannedQRCodeCallback)(const char *scannedQRCode);
/// AR 场景资源路径回调
/// 这里的规则就暂时不写死了，方便扩展，我们统一用 json 格式，ar_path
/// { "ar_path": "../xx/xx/" }
/// @wangyue 从json中解析本地路径
/// important!!! int to string
typedef void (* IARResourceLocalPathCallback)(const char *localARPathData);
/// 云端重定位的结果回调
typedef void (* ICloudLocationCallback)(int algCode, const char *protobufEncodingData);
/// 云端重定位请求，指向SDK的外部函数地址
typedef void (* ICloudLocationRequestHandler)(NSString * jpegStr, NSString * protoStr);
/// ar script 脚本指令回调
typedef void (* IDoScriptCallback)(const char *script);
//子场景资源进度下载回调
typedef void (*IPoiStatusCallback)(const char *script);
//主场景资源进度下载回调
typedef void (*IMainSceneStatusCallback)(const char *script);

void nbInit(IAuthorizationStatusCallback authorizationCallback,
//            IUploadCallback uploadCallback,
//            IPickImageCallback pickImageCallback,
            INavigationCallback navigationCallback,
//            IGPSCallback gpsCallback,
            IUserEventCallback eventCallback,
//            IScannedQRCodeCallback scanCallback,
            IARResourceLocalPathCallback arPathCallback,
            ICloudLocationCallback cloudLocationCallback,
            IDoScriptCallback doScriptCallback,
            IPoiStatusCallback poiStatusCallback,
            IMainSceneStatusCallback mainSceneStatusCallback);

void nbRequestAuthorizationAccess(enum IAuthorizationType type);
enum IAuthorizationStatus nbGetAuthorizationAccess(enum IAuthorizationType type);

void nbCheckSceneState(int cid);

/// 1 打开，0 关闭
int nbGetLocationSwitchStatus(void);

/// 跳设置，然后记录该次跳转，后台返回后回调 GPS 开关状态，脏代码
void nbRequestLocationSwitch(void);
typedef void (*ILocationSwitchCallback)(int status);
void nbSetLocationSwitchCallback(ILocationSwitchCallback bluetoothSwitchCallback);

#pragma mark ------ 通用能力 ------

void nbSaveEngineVersion(int);
bool nbIsWifi(void);
bool nbIsNetworkAvailable(void);
void nbGoSettings(void);
bool nbIsBottomBarSeries(void);
/// 弹出提示
void nbMakeToast(const char * text, int during);
/// 触发震动，场景效果需要用到
void nbVibrate(void);
/// 获取当前位置，定位成功后，需要通过 IGPSCallback 回调
void nbGetCurrentGPS(void);

void nbPickImageFromAlbum(void);
void nbSaveMediaFile(const char * resourcePath, enum IMediaType type);
/// 截屏在 unity 那边处理，截屏的结果在这里回调
void nbTakePhoto(const char * absolutePath);

#pragma mark - 通用接口，unity纯粹透传

typedef void (*ICommonDataCallback)(const char *commonData);
void nbSetCommonDataCallback(ICommonDataCallback commonDataCallback);

/// 算法通过unity向Native传输通用请求
/// @param type 冗余位，定义待定
/// @param data 冗余位，定义待定
void nbCommonDataRequest(int type, const char *data);

#pragma mark - debug用：云端回放

typedef struct InsightARDebugFrame
{
    /*******************************************************************************
                                   IMAGE
     *******************************************************************************/
    bool imageValid;             // 是否需要保存
#ifdef __APPLE__
    void *imagePtr;              // CVPixelBufferRef, 保存时与下面的imageWidth/Height一致。
#endif
#ifdef __ANDROID__
    
#endif
    double  imageTimeStamp;      // timestamp
    float   fx;                  // fx
    float   fy;                  // fy
    float   cx;                  // cx
    float   cy;                  // cy
    int     imageWidth;          // width
    int     imageHeight;         // height

    /*******************************************************************************
                                   LOC_TRAJ
     *******************************************************************************/
    bool    locValid;            // 是否需要保存, 如果云定位失败，则Valid = false。
    double  locTimeStamp;        // timestamp
    float   locPosition[3];      // x, y, z
    float   locRotation[4];      // qx,qy,qz,qw
    
    /*******************************************************************************
                                   VIO_TRAJ
     *******************************************************************************/
    bool    vioValid;            // 是否需要保存
    double  vioTimeStamp;        // timestamp
    float   vioPosition[3];      // x, y, z
    float   vioRotation[4];      // qx, qy, qz, qw
    
    /*******************************************************************************
                                   LOC_VIO_TRAJ
     *******************************************************************************/
    bool    locVioValid;         // 是否需要保存
    double  locVioTimeStamp;     // timestamp
    float   locVioPosition[3];   // x, y, z
    float   locVioRotation[4];   // qx, qy, qz, qw
    
    /*******************************************************************************
                                   TO BE CONTINUED
     *******************************************************************************/
    
} InsightARDebugFrame;

void nbSendDebugFrameInfo(InsightARDebugFrame frame, void *pHandler);

#pragma mark ------ NOS ------

void nbUploadImageToNos(const char *absolutePath, const char *token, const char *object, const char *bucket);

#pragma mark ------ 2D 导航 ------

void nbLoad2DMapData(const char * mapData, int floor);
/// 设置当前位置。 floor：所在楼层
void nbUpdate2DMapLocation(const char * geoJsonString);
/// 设置场景内的 POI 集合
void nbSet2DMapPoiList(const char * poiListInfo);
//void nbStartNavigation(const char * poiName); // deprecated，instead of IGPSCallback .
/// 增加导航类型
void nbUpdate2DMapNaviPath(enum INavigationType type, const char * pathData);
/// 结束2D导航
void nbExit2DNavigation(void);
/// 设置2D地图页面是否显示
void nbSet2DMapVisibility(int visiable);
/// 设置录屏页面是否显示
void nbSetRecordViewVisibility(int visiable);
/// for Android only
void nbRelease(void);

#pragma mark ------ 内容交互 ------

/// 增加内容事件
void nbSetAREvent(enum IAREventType type);

#pragma mark ------ 核销类项目 ------

/// open To Scan, default full Screen, will callback via [ARUUnityMessager shared].scannedQRCodeCallback, set block using nbSetScannedQRCodeCallback API in UnityPluginAPI.h
void nbOpenQRCodeScan(void);

/// Close and stop Scanning
void nbStopQRCodeScan(void);

/// default is YES, can stop scanning when Camera is Open
void nbSetScannnig(bool scanning);
    
/// unity 告知 QR 无效
void nbInvalidQRCode(void);

/// 调起外部导航
void nbCallExternalNavi(const char * destName, double destLatitude, double destLongitude, enum IExternalNavMode naviMode);

#pragma mark ------ 云端重定位 ------

void nbCloudLocationRequest(double timestamp, const char * jpgStr, const char * protoBufferStr);

#pragma mark ------ 事件交互 ------

void nb3DEventMessage(int identity, int version, int type, const char * desc);

#pragma mark ------ Unity 加载进度 ------

/**
 unity 加载进度 - 加载中
 user_data: 内容自定义参数
 progress: loading进度
 IARContentSceneType: 场景类型
 */
void nbSetUnityLoadingProgress(const char * user_data, double progress, enum IARSceneLoadingType);

/**
 unity 进度加载 - 加载完成
 user_data: 内容自定义参数，传负值则默认0.5s（SDK决定一个默认值）
 progress: loading进度
 IARContentSceneType: 场景类型
 */
void nbSetUnityLoadingCompleted(const char * user_data, double delay_to_open, enum IARSceneLoadingType);

#pragma mark ------ 语音转文字 ------

/// 语音识别服务的回调 recogCallback = nil表示发生错误；
typedef void (*IAudioRecognitionCallback)(const char *recogCallback);

/// 设置语音识别回调
void nbSetRecogCallback(IAudioRecognitionCallback audioRecognitionCallback);

/// 设置Key和secret；需要保证在 nbActiveAudioRecognition 调用之前设置
void nb_setAudioRecognitionKey(const char *key, const char *secret);

/// 开始录音
void nbActiveAudioRecognition(void);

/// 结束录音；会通过 IAudioRecognitionCallback 回调JSON结果 "{\"result\":[\"亲一下。\"],\"result_debug\":[\"亲\\t一下\"],\"sn\":\"b9e7caf0-5f42-4714-9b10-ebbfea9668d6\",\"ret_code\":1,\"audio_duration\":0.62131202220916748,\"ret_msg\":\"recognition succeeded!\"}"
void nbCloseAudioRecognition(void);

#pragma mark ------ 声音频率检测 ------

/*
frequency 频率
success 成功失败的回调
*/
typedef void(* IAudioFrequenceCallback)(float frequency, BOOL success);

void nbSetAudioFrequenceCallback(IAudioFrequenceCallback audioFrequenceCallback);

/*
 开始检测声音的频率
 */
void nbStartRecogniseAudioFrequence(void);

/*
 结束检测
 */
void nbStopRecognisingAudioFrequence(void);

#pragma mark - GPS/磁力计等相关

typedef void (*ISensorDataCallback)(const char *sensorData);
void nbSetSensorDataCallback(ISensorDataCallback sensorCallback);

typedef enum OasisUnityPluginSensorType {
    OasisUnityPluginSensorType_GPS         = 1 << 0, // 0001
    OasisUnityPluginSensorType_MAGN        = 1 << 1, // 0010
    OasisUnityPluginSensorType_BLUETOOTH   = 1 << 2, // 0100
    
    ///  all sensor
    OasisUnityPluginSensorType_ALL         = 1 << 10, // 10000000000
}OasisUnityPluginSensorType;

/// start Sensor Update
/// - Parameter sensorType: OasisUnityPluginSensorType
void nbStartSensorUpdate(OasisUnityPluginSensorType sensorType);

/// stop Sensor Update
/// - Parameter sensorType: OasisUnityPluginSensorType
void nbStopSensorUpdate(OasisUnityPluginSensorType sensorType);

/// nbRequestSensorData
/// @param sensorType see OasisUnityPluginSensorType
void nbRequestSensorData(OasisUnityPluginSensorType sensorType);

#pragma mark - 蓝牙状态

/*
 Unknown = 0,
 Resetting = 1,
 Unsupported = 2,
 Unauthorized = 3,
 PoweredOff = 4,
 PoweredOn = 5
 undefined = others
 
 蓝牙打开 = PoweredOn
 */
typedef void (*IBluetoothStatusCallback)(int status);

/// 设置蓝牙回调
void nbSetBluetoothStatusCallback(IBluetoothStatusCallback bluetoothStatusCallback);

/// 请求蓝牙状态：注意调用频率不可过高（比如一秒内多次）
void nbRequestBluetoothStatus(void);

#ifdef __cplusplus
}
#endif

#endif /* UnityPluginAPI_h */
