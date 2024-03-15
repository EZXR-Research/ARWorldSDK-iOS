//
//  AROasisUnityState.h
//  OasisUnitySDK
//
//  Created by Dikey on 2020/11/17.
//  Copyright © 2020 DikeyKing. All rights reserved.
//

#ifndef AROasisUnityState_h
#define AROasisUnityState_h

typedef NS_ENUM(NSInteger, AROasisUnityState) {
    
    /** startOK 之后可以退出AR  */
    AROasisUnityStateCameraStartOK        = -1,

    /** Uninitialized*/
    AROasisUnityStateUninitialized       = 0,
    /** Initing */
    AROasisUnityStateIniting             = 1,
    /** InitOK & can add ARView now */
    AROasisUnityStateInitOK              = 2,
    /** InitFail, should show error message to user & quit AR  */
    AROasisUnityStateInitFail            = 3,
    /** Detecting : currently,nothing you need to do */
    AROasisUnityStateDetecting           = 4,
    /** DetectOK : currently,nothing you need to do   */
    AROasisUnityStateDetectOK            = 5,
    /** DetectFail : currently,nothing you need to do    */
    AROasisUnityStateDetectFail          = 6,
    /** TrackingNormal    : currently,nothing you need to do    */
    AROasisUnityStateTrackingNormal      = 7,
    /** TrackLimited    : currently,nothing you need to do    */
    AROasisUnityStateTrackLimited        = 8,
    /** TrackLost :    */
    AROasisUnityStateTrackLost           = 9,
    /** TrackFail    :    */
    AROasisUnityStateTrackFail           = 10,
    /** TrackStop     :    */
    AROasisUnityStateTrackStop           = 11,

    /** 重要，需要处理。AR 启动时发生错误。
     
     可能原因：文件不完整、文件版本不匹配
     */
    AROasisUnityStateError       = 1000,
};

#endif /* AROasisUnityState_h */
