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

#define BRS_LOG_OFF      0x0         /// 关闭日志输出
#define BRS_LOG_PUBLIC   0x1         /// 显示主流程信息, default
#define BRS_LOG_PBDATA   0x1 << 1    /// 展示上报数据、响应数据
#define BRS_LOG_INFO     0x1 << 2    /// 提示信息
#define BRS_LOG_WARN     0x1 << 3    /// 警告信息
#define BRS_LOG_ERROR    0x1 << 4    /// 错误信息
#define BRS_LOG_TO_FILE  0x1 << 23

NS_ASSUME_NONNULL_BEGIN
@interface BRSAgent : NSObject

/**启动bonreeAgent(ver:6.6.1)*/
+ (void)startWithAppID:(NSString *)appid;

/**设置config地址,默认公有云不用设置*/
+ (void)setConfigAddress:(NSString *)configAddress;

/**设置app版本(请在bonreeAgent启动之前设置)*/
+ (void)setAppVersion:(NSString *)appVersion;

/**设置下载渠道名称*/
+ (void)setChannelName:(NSString *)channelName;

/**设置会员id*/
+ (void)setMemberId:(NSString *)memberId;
/**设置用户信息(客户可通过kv<key,value>参数增加用户信息，key为NSString类型，value为NSString或NSNumber类型)*/
+ (void)setUserInfo:(NSDictionary *)kv;

/*
打开日志标志,（默认只打开BRS_LOG_PUBLIC日志，此接口调试时调用,不建议在生产环境调用.）

例:打开BRS_LOG_PBDATA日志
[BRSAgent setLogFlag:@(BRS_LOG_PUBLIC|BRS_LOG_PBDATA)];

若需要通过iTunes导出log文件,应在程序的Info.plist文件中添加Application supports iTunes file sharing键，并将键值设置为YES.
 
例:打开BRS_LOG_PBDATA日志且写到文件中
[BRSAgent setLogFlag:@(BRS_LOG_PUBLIC|BRS_LOG_PBDATA|BRS_LOG_TO_FILE)];

关闭日志开关:
[BRSAgent setLogFlag:@(BRS_LOG_OFF)];
*/
+ (void)setLogFlag:(NSNumber *)flag;

/**获取设备的deviceId*/
+ (NSString *)deviceId;

/**
 配置自定义的设备deviceId
 
 注意:该方法必须在 - startWithAppID: 方法前调用,并且只能设置一次.
 */
+ (void)setDeviceID:(NSString *)deviceID;

/**获取SDK的版本号*/
+ (NSString *)SDKVersion;

/**即时upload接口，客户调用该接口，将sdk目前保存的数据及当前视图的信息直接上传。(同步上传，建议客户启用新的线程调用)*/
+ (void)upload:(void(^ _Nullable)(NSError * _Nullable error))result;

+ (void)stopSDK;

/**
  配置博睿的异常接口监听

 @param callback 错误回调
 */
+ (void)setExceptionCallback:(void(^ _Nullable)(NSString * _Nullable errorMessege))callback;

#pragma mark - 自定义

/**
 自定义异常收集
 @param exceptionType 异常类型
 @param causedBy 异常原因
 @param errorDump 异常堆栈
 */
+ (void)setCustomExceptionWithExceptionType:(NSString *)exceptionType
                                    causeBy:(NSString * _Nullable)causedBy
                                  errorDump:(NSString * _Nullable)errorDump;

/**
 自定义事件
 
 @param eventId 事件ID
 @param eventName 事件名
 @param eventInfo 事件信息，对事件的描述
 */
+ (void)setCustomEventWithEventId:(NSString *)eventId 
                        eventName:(NSString * _Nullable)eventName
                        eventInfo:(NSDictionary * _Nullable)eventInfo;


/**
 自定义视图之标记页面开始（和页面结束方法成对调用）
 
 @param pageId 页面ID
 @param pageName 页面名
 
 一般调用位置：viewWillAppear或者viewDidAppear
 */
+ (void)setCustomViewOfBeginWithPageId:(NSString *)pageId
                              pageName:(NSString * _Nullable)pageName;

/**
 自定义视图之标记页面结束（和页面开始方法成对调用）
 
 @param pageId 页面ID
 @param pageName 页面名
 
 一般调用位置：viewWillDisappear或者viewDidDisappear
 */
+ (void)setCustomViewOfEndWithPageId:(NSString *)pageId
                            pageName:(NSString * _Nullable)pageName;

/**
 用户测速接口
 
 @param parsingType 解析类型 ,客户标识
 @param content 需要解析的内容（一般为json格式的数据字典或者数组转换的结果）
 @param isOnce 是否只上传一次，true上传后清空content，false上传完成后不清空content，到下次上传的时候继续上传该content
 */
+ (void)setCustomSpeedWithParsingType:(NSString *)parsingType
                              content:(NSString * _Nullable)content
                               isOnce:(BOOL)isOnce;


/// 记录应用启动时间 (在main函数中调用) 返回值为记录的启动时间戳
+ (uint64_t)recordLaunchTime __attribute__((deprecated("启动时间自动获取，该接口停用。")));

/// 客户自定义请求头业务
/// @param headerArr 要获取的请求头中键名数组
+ (void)setCustomBusinessHeaders:(NSArray *)headerArr;

/// 是否使用mPaaS框架
/// @param used 是否使用mPaaS
+ (void)useMpaas:(BOOL)used;

@end
NS_ASSUME_NONNULL_END
