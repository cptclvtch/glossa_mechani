//
//  main.m
//  iOS
//
//  Created by Dragosh Iarovoi on 4/5/22.
//

#import <UIKit/UIKit.h>
#import "AppDelegate.h"

#include "../../unit_testing.c"

#define INCLUDE_PRINTING
#include "../../../../glossa_mechani.c"
#undef CLT

int main(int argc, char * argv[]) {
    
    #include "../../testing_body.c"
    
    NSString * appDelegateClassName;
    @autoreleasepool {
        // Setup code that might create autoreleased objects goes here.
        appDelegateClassName = NSStringFromClass([AppDelegate class]);
    }
    return UIApplicationMain(argc, argv, nil, appDelegateClassName);
}
