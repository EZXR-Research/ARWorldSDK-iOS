//
//  AROasisUnityEvent.h
//  InsightSDK
//
//  Created by Dikey on 2020/11/17.
//  Copyright © 2020 DikeyKing. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AROasisUnityEvent.h"
#import <OasisUnityPlugin/OasisUnityPlugin.h>

/** 通用型AR事件，不跟具体AR Product 相关，需要客户端本地完成对应的功能 */
typedef NS_ENUM(NSUInteger, AROasisUnityEventType) {
    //function event
    /**
    params: key is script, value is script name; if contain "json" key, the value is json string
             特别注释：对于跟具体AR product相关的脚本，是将（scriptName + json） -> app ->  server
                     如果是需要把处理完数据返回给SDK，则server （scriptName+ jsonNew）-> APP -> SDK
                     客户端不要对具体json做任何处理，这样确保，客户端开发是与ar product是独立的
     */
    AROasisUnityEvent_Function_RunScript             = 100,
    /** params: nil */
    AROasisUnityEvent_Function_CloseARProduct        = 101,
    /** params: key is name, value is maker name； 用于比如刷新、云识别到图片加载对应的ar produnct
        假如 params[@"needLBS"]  为 "1" ， 的时候需要传入经度和纬度，在非继承使用InsightARVC同时需要传入params，参考初始化代码：
         ARPrepareOptions *options = [[ARPrepareOptions alloc]initWithDictionary:params longitude:longitude latitude:latitude];
     */
    AROasisUnityEvent_Function_ReloadARProduct       = 102,
    /** params: key is url, value is URL address;key is type, value is 0 (view) or 1 (web vc)*/
    AROasisUnityEvent_Function_OpenURL               = 108,
    /** params: key is image*/
    AROasisUnityEvent_Function_ScreenShot            = 110,
    /** params: key is type, value is 1 (text); 2
     key is title, value is NSString;
     key is description, value is NSString
     key is url, value is NSString
     key is image, value is UIImage
     */
    AROasisUnityEvent_Function_Share                 = 111,
    /** 用于内容的网络数据获取：需要SDK集成方根据AR场景定义访问网络获取数据，然后传给AR内容*/
    AROasisUnityEvent_Function_Network_API   = 116,
    
    /*
     一些内部通知
     */
    
    /**   __attribute__((deprecated)): params: key is name, value is music id*/
    AROasisUnityEvent_PlayMusic   = 103 ,
    /**   __attribute__((deprecated)): params: key is name, value is music id*/
    AROasisUnityEvent_PauseMusic   = 104 ,
    /**   __attribute__((deprecated)): params: key is name, value is music id*/
    AROasisUnityEvent_StopMusic   = 105 ,
    /**   __attribute__((deprecated)): params: nil*/
    AROasisUnityEvent_StartRecordAudio   = 106,
    /**   __attribute__((deprecated)): params: nil*/
    AROasisUnityEvent_StopRecordAudio   = 107,
    /**   __attribute__((deprecated)): params: key is url, value is URL address;key is type, value is 0 (view) or 1 (web vc)*/
    AROasisUnityEvent_Function_DetectEnvironment   = 109,
    /**   __attribute__((deprecated)): params: nil*/
    AROasisUnityEvent_StartScreenRecord   = 112,
    /**   __attribute__((deprecated)): params: nil*/
    AROasisUnityEvent_StopScreenRecord   = 113,
    /**   __attribute__((deprecated)): params: key is image, value is UIImage;*/
    AROasisUnityEvent_TakeBackgroundPickure   = 114,
    /**   __attribute__((deprecated)): . */
    AROasisUnityEvent_Function_TrackEvent   = 115,
    /**   __attribute__((deprecated)): params: key is name, value is model name*/
    AROasisUnityEvent_Model_Load   = 301,
    /**   __attribute__((deprecated)): params: key is name, value is model name*/
    AROasisUnityEvent_Model_Switch   = 302,
    /**   __attribute__((deprecated)): params: key is name, value is model name*/
    AROasisUnityEvent_Model_Unload   = 303,
    /**   __attribute__((deprecated)): params: nil*/
    AROasisUnityEvent_Model_UnloadAll   = 304,
    /**   __attribute__((deprecated)): params: key is name, value is model name*/
    AROasisUnityEvent_Model_Selected   = 305,
    /**   __attribute__((deprecated)): params: key is name, value is model name*/
    AROasisUnityEvent_Model_DeSelected   = 306,
    /**   __attribute__((deprecated)): params: key is count, value is model count; key is max, value is  m */
    AROasisUnityEvent_Model_CountInScene   = 307,
    
    /* 子事件相关 */
    AROasisUnityEvent_Toast = 10005, // toast
    /* 子事件相关 */
    AROasisUnityEvent_Download = 10008, // 下载子事件
    
    
};

@class AROasisUnityEvent;

extern NSString* const kInsightU3DEventNotification;

typedef void(^AROasisUnityEventBlock)(AROasisUnityEvent *event);
typedef void(^AROasisLoadEventBlock)(AROasisUnityLoadEvent *event);

@interface AROasisUnityEvent : NSObject

@property (assign, nonatomic) AROasisUnityEventType type;
@property (copy, nonatomic) NSDictionary *params;

@end

