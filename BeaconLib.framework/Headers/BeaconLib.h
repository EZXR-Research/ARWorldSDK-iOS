#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "Constants.h"
#import <CommonCrypto/CommonCryptor.h>

@interface BeaconLib : NSObject

- (id)init:(NSString *)mapId keyString:(NSString *)key initHandler:(BeaconInitHandler)handler;

- (id)init:(NSString *)mapId keyString:(NSString *)key isExp:(BOOL *)exp initHandler:(BeaconInitHandler)handler;

- (void)setDirectionHandler:(DirectionHandler)handler;

- (void)setScanHandler:(ScanHandler)handler;

- (void)strictDistance:(double)distance;

- (void)strictSize:(int)size;

- (void)strictRssi:(int)rssi;

- (void)rssiChainSize:(int)size;

- (void)enableNearbyMode;

- (void)disableNearbyMode;

- (void)enableAbsoluteStatic;

- (void)disableAbsoluteStatic;

- (void)enableCarMode;

- (void)disableCarMode;

- (void)start;

- (void)start:(NSString *)uuid;

- (void)stop;
@end
