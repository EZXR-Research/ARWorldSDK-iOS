#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "Constants.h"
#import <CommonCrypto/CommonCryptor.h>

@interface OfflineBeaconLib : NSObject

- (id)init:(NSString *)mapId keyString:(NSString *)key filePath:(NSString *)file initHandler:(BeaconInitHandler)handler;

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
