//
//  OasisUnityPluginRequest.h
//  OasisUnityPlugin
//
//  Created by Carmine on 2021/5/21.
//  Copyright © 2021 Carmine. All rights reserved.
//

#ifndef OasisUnityPluginRequest_h
#define OasisUnityPluginRequest_h

#ifdef __cplusplus
extern "C" {
#endif

#pragma mark - Data Request

/**
 http 数据请求的回调
 */
typedef void (* IHttpRequestCallback)(const char * user_data, const char * resulCode, const char * resultMsg, const char * result);

/**
 http 数据请求的回调注册
 */
void nbSetRequestCallback(IHttpRequestCallback callback);

// 数据请求
void nbRequest(const char * url,
               const char * method,
               const char * header,
               const char * body,
               const char * user_data);


#pragma mark - Download Request

/**
 http 下载请求成功回调
 */
typedef void (* IHttpDownloadSuccessCallback)(const char * downloadURL,
                                              const char * downloadPath,
                                              const char * user_data);
/**
 http 下载请求进度回调
 */
typedef void (* IHttpDownloadProgressCallback)(const char * downloadURL,
                                               float progress,
                                               const char * user_data);
/**
 http 下载请求失败回调
 */
typedef void (*IHttpDownloadFailCallback)(const char * downloadURL,
                                          const char * resultCode,
                                          const char * resultDescription,
                                          const char * user_data);

/**
 http 下载请求的回调注册
 */
void nbSetDownloadCallback(IHttpDownloadSuccessCallback successCallback,
                           IHttpDownloadProgressCallback progressCallback,
                           IHttpDownloadFailCallback failedCallback);

///// 文件下载，不带参数
//void nbDownload(const char *url, const char * user_data);


#pragma mark - 媒体文件下载

void nbDownloadFile(const char *url, const char * downloadPath, const char * user_data);

#ifdef __cplusplus
}
#endif

#endif /* OasisUnityPluginRequest_h */
