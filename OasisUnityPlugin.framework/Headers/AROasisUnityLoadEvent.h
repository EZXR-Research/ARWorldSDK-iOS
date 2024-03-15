//
//  AROasisUnityLoadEvent.h
//  OasisUnityPlugin
//
//  Created by Carmine on 2022/1/13.
//  Copyright © 2022 Carmine. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ARUUnityMessager.h"

NS_ASSUME_NONNULL_BEGIN

@interface AROasisUnityLoadEvent : NSObject

@property (assign, nonatomic) enum IAREventType type;
@property (copy, nonatomic) NSDictionary *params;

@end

NS_ASSUME_NONNULL_END
