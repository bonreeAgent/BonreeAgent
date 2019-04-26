# BonreeAgent

## 安装指南

### Cocoapods方式

* 此方式目前只支持公有云。

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
  * CoreLocation.framework
  * CoreTelephony.framework
  * Security.framework
  * SystemConfiguration.framework
  * webKit.framework（如果项目支持iOS8之前版本需要添加）
  * libz.1.2.8.tbd（**必须引入**）
  * libresolv.tbd（**必须引入**）
  * libc++.tbd（**必须引入**）

![image](https://github.com/TuYuWang/NewBonreeAgent/raw/master/img/Dependce.png)

* 在**Build Setting**中搜索**Other Linker Flags**, 添加编译标志**-ObjC**。如图所示:

![image](https://github.com/TuYuWang/NewBonreeAgent/raw/master/img/OtherLinker.png)



### 使用

#### Objective-C

* 引入头文件: 在AppDelegate.m中导入头文件。

* 在application:didFinishLaunchingWithOptions中设置config地址与AppId，如图所示:

```objective-c
[BRSAgent setConﬁgAddress:@"https://sdkupload.bonree.com/conﬁg/"];
[BRSAgent startWithAppID:@"40766f87-13a8-48d3-9c96-1ce7c3cde50f"];
```

![image](https://github.com/TuYuWang/NewBonreeAgent/raw/master/img/OC.png)

#### Swift

* 在对应的桥接⽂件⾥bridging-header.h⾥导⼊头⽂件，如图所示:

![image](https://github.com/TuYuWang/NewBonreeAgent/raw/master/img/Swift-H.png)

* AppDelegate.swift文件中设置config地址和AppId，如图所示:

![image](https://github.com/TuYuWang/NewBonreeAgent/raw/master/img/Swift.png)

运行后有日志 bonreeAgent config succeeded ,即表示嵌码成功,如下图:

![image](https://github.com/TuYuWang/NewBonreeAgent/raw/master/img/success.png)



### API

```objective-c
/**启动bonreeAgent*/
+ (void)startWithAppID:(NSString*)appid;

/**启动bonreeAgent,并指明是否使用位置服务*/
+ (void)startWithAppID:(NSString*)appId location:(BOOL)locationAllowed;

/**启动bonreeAgent,同时指定是否开启webview功能,默认开启（YES表示开启，NO表示关闭）*/
+ (void)startWithAppID:(NSString *)appId webViewOn:(BOOL)webViewOn;

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
```



### 其它

* config地址接口调用须在sdk初始化接口startWithAppID之前调用，否则私有云地址设置将无法生效;
* 私有云需要调用setConfigAddress,设置config地址,具体地址由技术支持提供 
* 如果项目中存在友盟，启动位置需要在友盟启动之后
* 仅支持iOS8.0及以上版本，网络模块仅支持iOS10及以上版本

