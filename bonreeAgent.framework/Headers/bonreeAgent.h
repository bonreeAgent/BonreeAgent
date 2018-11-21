/*
 *
 * Copyright (c) 2015-2020  Bonree Company
 * 北京博睿宏远科技发展有限公司  版权所有 2015-2020
 *
 * PROPRIETARY RIGHTS of Bonree Company are involved in the
 * subject matter of this material.  All manufacturing, reproduction, use,
 * and sales rights pertaining to this subject matter are governed by the
 * license agreement.  The recipient of this software implicitly accepts
 * the terms of the license.
 * 本软件文档资料是博睿公司的资产,任何人士阅读和使用本资料必须获得
 * 相应的书面授权,承担保密责任和接受相应的法律约束.
 *
 */

#import <Foundation/Foundation.h>

//日志标志
#define BRS_LOG_PUBLIC          (0x1)
#define BRS_LOG_BRN             (0x1 << 1)
#define BRS_LOG_PBDATA          (0x1 << 2)
#define BRS_LOG_JS              (0x1 << 3)
#define BRS_LOG_TO_FILE         (0x1 << 4)

@class AFSecurityPolicy;

@interface BRSAgent : NSObject

/**启动bonreeAgent(ver:5.2.0)*/
+ (void)startWithAppID:(NSString*)appid;

/**启动bonreeAgent，并指明是否使用保障开关(如果sdk造成了崩溃，则sdk在下次启动将只开启崩溃收集功能)，默认开启*/
+ (void)startWithAppID:(NSString *)appid GuardOn:(BOOL)guardOn;

/**启动bonreeAgent,并指明是否使用位置服务*/
+ (void)startWithAppID:(NSString*)appId location:(BOOL)locationAllowed;

/**启动bonreeAgent,同时指定是否开启webview功能,默认开启（YES表示开启，NO表示关闭）*/
+ (void)startWithAppID:(NSString *)appId webViewOn:(BOOL)webViewOn;

/**设置是否通过弹框方式显示日志，默认关闭*/
+ (void)enableDebugModel:(BOOL)enable;

/**设置是否异步启动*/
+ (void)enableAsyncStart:(BOOL)enable;

/**设置是否捕获崩溃日志,默认打开*/
+ (void)enableCrashReporting:(BOOL)enable;

/**设置是否获取位置信息,默认关闭*/
+ (void)enableLocation:(BOOL)enable;

/**不通过后台来配置启动概率,100%启动SDK*/
+ (void)enableAllLaunch:(BOOL)enable;

/**设置是否获取网络性能数据,默认打开*/
+ (void)enableBonreeNetwork:(BOOL)enable;

/**设置是否开启数据融合,YES表示开启,NO表示关闭,默认关闭(该接口为定制接口,调用之前请与公司的技术人员咨询确认)*/
+(void)enableMerge:(BOOL)enable;

/**设置是否开启崩溃轨迹，YES表示开启，NO表示关闭,公有云版本默认开启*/
+ (void)enableCrashTrace:(BOOL)enable;

/**设置是否开启交互分析，YES表示开启，NO表示关闭,公有云版本默认开启*/
+ (void)enableInteract:(BOOL)enable;

/**设置是否开启卡顿监测，YES表示开启，NO表示关闭,公有云版本默认开启*/
+ (void)enableStuckMonitorOn:(BOOL)enable;

/**设置是否开启webview监测，YES表示开启，NO表示关闭,公有云版本默认开启*/
+ (void)enableWebviewOn:(BOOL)enable;

/**设置config地址,默认公有云不用设置*/
+ (void)setConfigAddress:(NSString*)configAddress;

/**设置app版本(请在bonreeAgent启动之前设置)*/
+ (void)setAppVersion:(NSString *)appVersion;

+ (void)stopSDK;

/**即时upload接口，客户调用该接口，将sdk目前保存的数据及当前视图的信息直接上传，返回值为YES表示上传成功，NO表示上传失败。(同步上传，建议客户启用新的线程调用)*/
+ (BOOL)upload;

/**自定义崩溃收集接口,exceptionName为崩溃类型，如数组越界等；causeby为崩溃原因，即造成崩溃的方法；errordump为崩溃堆栈*/
+ (void)setUserExceptionWithName:(NSString *)exceptionName CauseBy:(NSString *)causedBy Errordump:(NSString *)errordump;

/**设置自定义信息*/
+ (void)setDefinedLog:(NSString *)memberId Info:(NSString *)definedInfo;

/**增加自定义崩溃轨迹*/
+ (void)addCustomCrashTrace:(NSString *)title action:(NSString *)name;

/**更新cookie、网关及端口信息(该接口为定制接口,调用之前请与公司的技术人员咨询确认)*/
+ (void)setCookie:(id)cookie gateway:(NSString *)gateway port:(NSString *)port;

#pragma mark -
#pragma mark - 行为数据

/**设置下载渠道名称*/
+ (void)setChannelName:(NSString*)channelName;

/**自定义事件*/
+ (void)trackEvent:(NSString*)eventID name:(NSString*)eventName;

/**自定义事件(客户可通过dictionary<key,value>参数增加对事件的描述，key为NSString类型，value为NSString或NSNumber类型)*/
+ (void)trackEvent:(NSString*)eventID name:(NSString*)eventName parameters:(NSDictionary*)dictionary;

/*
 标记页面开始和结束,这两个接口需要成对调用.
 在viewWillAppear或者viewDidAppear调用trackPageBegin方法
 在viewWillDisappear或者viewDidDisappear调用trackPageEnd方法
 */
+ (void)trackPageBegin:(NSString *)pageId pageName:(NSString *)pageName;
+ (void)trackPageEnd:(NSString *)pageId pageName:(NSString*)pageName;


/**设置会员id*/
+ (void)setMemberId:(NSString *)memberId;
/**设置用户信息(客户可通过kv<key,value>参数增加用户信息，key为NSString类型，value为NSString或NSNumber类型)*/
+ (void)setUserInfo:(NSDictionary *)kv;

/*
 打开日志标志,默认只打开BRS_LOG_PUBLIC日志.
 此接口调试时调用,不建议在生产环境调用.
 例:打开BRS_LOG_PBDATA日志
 [BRSAgent setLogFlag:@(BRS_LOG_PUBLIC|BRS_LOG_PBDATA)];
 
 如果将日志写到文件中,
 需要在应用程序的Info.plist文件中添加Application supports iTunes file sharing键，
 并将键值设置为YES.
 例:打开BRS_LOG_PBDATA日志且写到文件中
 [BRSAgent setLogFlag:@(BRS_LOG_PUBLIC|BRS_LOG_PBDATA|BRS_LOG_TO_FILE)];
 
 关闭日志开关:
 [BRSAgent setLogFlag:@0];
 */
+ (void)setLogFlag:(NSNumber*)flag;

/**获取设备的deviceId*/
+ (NSString *)deviceId;
/**获取SDK的版本号*/
+ (NSString *)getBonreeSDKVersion;

/**
 用户测速接口

 @param customerId 解析类型 ,客户唯一标识
 @param jsonData 需要解析的内容 ,json格式的数据
 @param isOnce 是否只上传一次，true上传后清空jsonData，false上传完成后不清空jsonData，到下次上传的时候继续上传该jsonData
 */
+ (void)setThirdData:(NSString *)customerId jsonData:(NSString *)jsonData isOnce:(BOOL)isOnce;
@end

/*
 Example 1:
 最简单的,默认关闭位置服务,默认打开捕获崩溃信息,启动概率为100%,同步启动
 [BRSAgent startWithAppID:@"xxxx"];
 
 Example 2:
 打开捕获崩溃信息
 [BRSAgent enableCrashReporting:YES];
 [BRSAgent startWithAppID:@"xxxx"];
*/
