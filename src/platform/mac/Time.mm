#import <Foundation/Foundation.h>

#import "../../common/Time.h"

#ifdef __APPLE__

double GetTimeSeconds() {
    return [[NSDate date] timeIntervalSince1970];
}

#endif
