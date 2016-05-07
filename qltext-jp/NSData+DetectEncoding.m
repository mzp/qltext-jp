#import "NSData+DetectEncoding.h"

const int DEFAULT_MAX_FILE_SIZE = 1024 * 100;

static unsigned long long getFileSize(NSURL* url) {
    NSFileManager *man = [NSFileManager defaultManager];
    NSDictionary *attrs = [man attributesOfItemAtPath: [url path] error: NULL];
    return attrs.fileSize;
}

static NSData* readFromURL(NSURL* url) {
    if(getFileSize(url) > DEFAULT_MAX_FILE_SIZE) {
        NSFileHandle *myFile= [NSFileHandle fileHandleForReadingAtPath:[url path]];
        if(!myFile) {
            return nil;
        }
        NSData *data = [myFile readDataOfLength:DEFAULT_MAX_FILE_SIZE];
        [myFile closeFile];
        return data;
    } else {
        NSError *error = nil;
        return [NSData dataWithContentsOfURL:url options:NSDataReadingUncached error:&error];
    }
}

static NSStringEncoding getFileEncoding(NSData* data) {
    if(data) {
        return [NSData detectEncoding:data];
    } else {
        return 0;
    }
}

@implementation NSData (DetectEncoding)

+(NSStringEncoding) detectEncoding:(NSData *)data
{
    NSStringEncoding encoding;
    NSStringEncoding encodings[] = {
        NSUTF8StringEncoding,
        NSNonLossyASCIIStringEncoding,
        NSShiftJISStringEncoding,
        NSJapaneseEUCStringEncoding,
        NSMacOSRomanStringEncoding,
        NSWindowsCP1251StringEncoding,
        NSWindowsCP1252StringEncoding,
        NSWindowsCP1253StringEncoding,
        NSWindowsCP1254StringEncoding,
        NSWindowsCP1250StringEncoding,
        NSISOLatin1StringEncoding,
        NSUnicodeStringEncoding,
        0
    };

    int i = 0;
    NSString *try_str;

    if (memchr([data bytes], 0x1b, [data length]) != NULL) {
        try_str = [[NSString alloc] initWithData:data encoding:NSISO2022JPStringEncoding];
        if (try_str != nil)
            return NSISO2022JPStringEncoding;
    }

    while(encodings[i] != 0){
        try_str = [[NSString alloc] initWithData:data encoding:encodings[i]];
        if (try_str != nil) {
            encoding = encodings[i];
            break;
        }
        i++;
    }
    return encoding;
}

+(NSStringEncoding) detectEncodingOfURL:(NSURL *)url {
    NSData* data = readFromURL(url);
    if(data) {
        return getFileEncoding(data);
    } else {
        return 0;
    }
}

@end