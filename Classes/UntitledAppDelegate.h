#import <UIKit/UIKit.h>
#include "js.h"
#include "TextViewController.h"

@interface UntitledAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    TextViewController * textViewController;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;

@end

