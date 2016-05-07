#include <CoreFoundation/CoreFoundation.h>
#include <CoreServices/CoreServices.h>
#include <QuickLook/QuickLook.h>
#import <Cocoa/Cocoa.h>
#import "NSData+DetectEncoding.h"

OSStatus GeneratePreviewForURL(void *thisInterface, QLPreviewRequestRef preview, CFURLRef url, CFStringRef contentTypeUTI, CFDictionaryRef options);
void CancelPreviewGeneration(void *thisInterface, QLPreviewRequestRef preview);

/* -----------------------------------------------------------------------------
 Generate a preview for file

 This function's job is to create preview for designated file
 ----------------------------------------------------------------------------- */

OSStatus GeneratePreviewForURL(void *thisInterface, QLPreviewRequestRef preview, CFURLRef url, CFStringRef contentTypeUTI, CFDictionaryRef options)
{
    @autoreleasepool {
        NSStringEncoding encoding = [NSData detectEncodingOfURL:(__bridge NSURL*)url];
        if(encoding != 0) {
            NSDictionary *props = @{
                (NSString *)kQLPreviewPropertyStringEncodingKey : @(CFStringConvertNSStringEncodingToEncoding(encoding))
            };
            QLPreviewRequestSetURLRepresentation(preview, url, kUTTypePlainText, (__bridge CFDictionaryRef)props);
            return noErr;
        } else {
            return -1;
        }
    }
}

void CancelPreviewGeneration(void *thisInterface, QLPreviewRequestRef preview)
{
    // Implement only if supported
}
