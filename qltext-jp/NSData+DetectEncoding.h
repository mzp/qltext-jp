#import <Foundation/Foundation.h>

// http://qiita.com/mosson/items/c4c329d433d99e3583ec
@interface NSData (DetectEncoding)
+(NSStringEncoding) detectEncoding:(NSData *)data;
+(NSStringEncoding) detectEncodingOfURL:(NSURL *)url;
@end