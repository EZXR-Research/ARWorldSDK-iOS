//
//  AROasisUnityStartResult.h
//  OasisUnitySDK
//
//  Created by Dikey on 2021/1/19.
//  Copyright © 2021 DikeyKing. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AROasisUnityState.h"

@class AROasisUnityStartResult;

typedef void(^AROasisStartBlock)(AROasisUnityStartResult* result);

@interface AROasisUnityStartResult : NSObject

/// see AROasisUnityState
@property (nonatomic, assign) AROasisUnityState state;

/// description of state
@property (nonatomic, copy) NSString *desc;

@end
