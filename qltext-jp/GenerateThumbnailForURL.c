#include <CoreFoundation/CoreFoundation.h>
#include <CoreServices/CoreServices.h>
#include <QuickLook/QuickLook.h>
#import <Cocoa/Cocoa.h>
#import "NSData+DetectEncoding.h"

OSStatus GenerateThumbnailForURL(void *thisInterface, QLThumbnailRequestRef thumbnail, CFURLRef url, CFStringRef contentTypeUTI, CFDictionaryRef options, CGSize maxSize);
void CancelThumbnailGeneration(void *thisInterface, QLThumbnailRequestRef thumbnail);

/* -----------------------------------------------------------------------------
 Generate a thumbnail for file

 This function's job is to create thumbnail for designated file as fast as possible
 ----------------------------------------------------------------------------- */

OSStatus GenerateThumbnailForURL(void *thisInterface, QLThumbnailRequestRef thumbnail, CFURLRef url, CFStringRef contentTypeUTI, CFDictionaryRef options, CGSize maxSize)
{
    @autoreleasepool {
        NSStringEncoding encoding = [NSData detectEncodingOfURL:(__bridge NSURL*)url];
        NSDictionary *previewProperties = @{
            (NSString *)kQLPreviewPropertyStringEncodingKey : @(CFStringConvertNSStringEncodingToEncoding(encoding))
        };

        NSDictionary *properties = @{
        };

        QLThumbnailRequestSetThumbnailWithURLRepresentation(
                                                            thumbnail,
                                                            url,
                                                            kUTTypePlainText,
                                                            (__bridge CFDictionaryRef)previewProperties,
                                                            (__bridge CFDictionaryRef)properties);
        return noErr;
    }
}

void CancelThumbnailGeneration(void *thisInterface, QLThumbnailRequestRef thumbnail)
{
    // Implement only if supported
}
