#import "UntitledAppDelegate.h"

@implementation UntitledAppDelegate

@synthesize window;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions   
{
    CGRect    rect = [[UIScreen mainScreen] bounds];
    window = [[UIWindow alloc] initWithFrame:rect];
    
    textViewController = [[TextViewController alloc] init];
    
    [window addSubview:textViewController.view];
    [window makeKeyAndVisible];
    dojs([[[NSBundle mainBundle] resourcePath] cStringUsingEncoding:NSASCIIStringEncoding]);
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
}

- (void)applicationWillTerminate:(UIApplication *)application
{
}

- (void)dealloc
{
    [window release];

    [super dealloc];
}

@end
