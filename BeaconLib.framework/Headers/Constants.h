#import <Foundation/Foundation.h>

#define MT_BEACON_UUID @"FDA50693-A4E2-4FB1-AFCF-C6EB07647825"
#define SUCCESS 0
#define ERROR 1
#define INVALID_KEY 2
#define INVALID_MAPID 3
#define NO_STATION 4
#define CHECK_TIME 5000
#define INVALID_FILE 5
#define MAX_DISTANCE 99
#define CHANGE_FLOOR_COUNT 4
#define STRICT_DISTANCE 10
#define STRICT_SIZE 15
#define STRICT_RSSI -100
#define RSSI_CHAIN_SIZE 5

typedef void (^BeaconInitHandler)(double posx, double posy, int floor, double direction, int code, double distance);

typedef void (^DirectionHandler)(double direction);

typedef void (^ScanHandler)(NSArray *beacons);

@interface Constants : NSObject
@end
