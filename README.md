# BonreeAgent

## 安装指南

### Cocoapods方式

* 在工程**Podfile**文件中添加

  ```objective-c
  pod 'bonreeAgent'
  ```

### 安装包方式

* 解压**bonreeAgent.framework.tar.gz**，将**bonreeAgent.framework**加入到项目中，如图所示:

![image](https://github.com/TuYuWang/NewBonreeAgent/raw/master/img/Add.png)

* 在**BuildPhass** -> **Link Binary With Libraries**中添加**bonreeAgent.framework**，如图所示：

![image](https://github.com/TuYuWang/NewBonreeAgent/raw/master/img/Link.png)

* 添加以下依赖库:
  * libresolv.tbd（**必须引入**）
  * libc++.tbd（**必须引入**）
  * webKit.framework（如果项目支持iOS8之前版本需要添加）

![image](https://github.com/TuYuWang/NewBonreeAgent/raw/master/img/Dependce.png)

* 在**Build Setting**中搜索**Other Linker Flags**, 添加编译标志**-ObjC**。如图所示:

![image](https://github.com/TuYuWang/NewBonreeAgent/raw/master/img/OtherLinker.png)



### 使用

#### Objective-C

* 引入头文件: 在AppDelegate.m中导入头文件。

* 在application:didFinishLaunchingWithOptions中设置config地址与AppId，如图所示:

```objective-c
[BRSAgent setConfigAddress:@"https://sdkupload.bonree.com/config"];
[BRSAgent startWithAppID:@"40766f87-13a8-48d3-9c96-1ce7c3cde50f"];
```

![image](https://github.com/TuYuWang/NewBonreeAgent/raw/master/img/OC.png)

#### Swift

* 在对应的桥接⽂件⾥bridging-header.h⾥导⼊头⽂件，如图所示:

![image](https://github.com/TuYuWang/NewBonreeAgent/raw/master/img/Swift-H.png)

* AppDelegate.swift文件中设置config地址和AppId，如图所示:

![image](https://github.com/TuYuWang/NewBonreeAgent/raw/master/img/Swift.png)

运行后有日志 bonreeAgent config succeeded ,即表示嵌码成功,如下:

```objective-c
2019-06-21 13:55:40 +0000 [bonreeAgent] bonreeAgent config succeeded
```





### API

```objective-c
/**启动bonreeAgent*/
+ (void)startWithAppID:(NSString*)appid;

/**设置config地址,默认公有云不用设置*/
+ (void)setConfigAddress:(NSString*)configAddress;

/**设置app版本(请在bonreeAgent启动之前设置)*/
+ (void)setAppVersion:(NSString *)appVersion;

/**设置下载渠道名称*/
+ (void)setChannelName:(NSString*)channelName;

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
+ (NSString *)SDKVersion;

/// 设置是否保存upload数据
+ (void)setIsKeepUploadData:(BOOL)isKeepUploadData;

/**即时upload接口，客户调用该接口，将sdk目前保存的数据及当前视图的信息直接上传，返回值为YES表示上传成功，NO表示上传失败。(同步上传，建议客户启用新的线程调用)*/
+ (void)upload:(void(^)(NSError *error))result;

+ (void)stopSDK;


#pragma mark - 自定义

/**
 自定义异常收集
 
 @param exceptionType 异常类型
 @param causedBy 异常原因
 @param errorDump 异常堆栈
 */
+ (void)setCustomExceptionWithExceptionType:(NSString *)exceptionType
                                    causeBy:(NSString *)causedBy
                                  errorDump:(NSString *)errorDump;

/**
 自定义日志
 
 @param memberId 会员ID
 @param info 日志信息
 */
+ (void)setCustomLogWithMemberId:(NSString *)memberId
                            info:(NSString *)info;

/**
 自定义事件
 
 @param eventId 事件ID
 @param eventName 事件名
 @param eventInfo 事件信息，对事件的描述
 */
+ (void)setCustomEventWithEventId:(NSString *)eventId 
                        eventName:(NSString *)eventName
                        eventInfo:(NSDictionary *)eventInfo;


/**
 自定义视图之标记页面开始（和页面结束方法成对调用）
 
 @param pageId 页面ID
 @param pageName 页面名
 
 一般调用位置：viewWillAppear或者viewDidAppear
 */
+ (void)setCustomViewOfBeginWithPageId:(NSString *)pageId
                              pageName:(NSString *)pageName;

/**
 自定义视图之标记页面结束（和页面开始方法成对调用）
 
 @param pageId 页面ID
 @param pageName 页面名
 
 一般调用位置：viewWillDisappear或者viewDidDisappear
 */
+ (void)setCustomViewOfEndWithPageId:(NSString *)pageId
                            pageName:(NSString *)pageName;

/**
 用户测速接口
 
 @param parsingType 解析类型 ,客户标识
 @param content 需要解析的内容（一般为json格式的数据字典或者数组转换的结果）
 @param isOnce 是否只上传一次，true上传后清空content，false上传完成后不清空content，到下次上传的时候继续上传该content
 */
+ (void)setCustomSpeedWithParsingType:(NSString *)parsingType
                              content:(NSString *)content
                               isOnce:(BOOL)isOnce;
```



### 注意点

* config地址接口调用须在sdk初始化接口startWithAppID之前调用，否则私有云地址设置将无法生效;
* 私有云需要调用setConfigAddress,设置config地址,具体地址由技术支持提供 
* 私有云使用6.1.0版本SDK，平台最低为5.9.2版本
* SDK仅支持iOS8.0及以上版本
* 网络模块仅支持iOS10及以上版本
* WKWebView仅支持iOS11及以上版本

### F&Q

* 与友盟崩溃同时使用，启动位置需要在友盟之后，才可以正常抓取崩溃

* 极光开启崩溃日志功能，会导致部分崩溃采集异常

* 与buggly同时使用，启动需要在buggly启动之前，否则可能会引发buggly崩溃卡死问题

* 如果使用了NSSetUncaughtExceptionHandler方法，建议在该方法调用之后启动

  

