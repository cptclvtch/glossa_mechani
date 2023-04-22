//
//  main.m
//  macOS
//
//  Created by Dragosh Iarovoi on 3/24/22.
//

#import <Cocoa/Cocoa.h>

#import "../../unit_testing.c"
#define INCLUDE_PRINTING
#import "../../../../glossa_mechani.c"
#undef CLT

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // Setup code that might create autoreleased objects goes here.
    }
    
    #import "../../testing_body.c"
    
    return NSApplicationMain(argc, argv);
}
