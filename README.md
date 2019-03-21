# 			   BonreeAgent

### 安装指南

1、解压bonreeAgent.framework.tar.gz，将bonreeAgent.framework加入到项目中，如图所示:

![image](https://github.com/TuYuWang/NewBonreeAgent/raw/master/img/Add.png)

2、在BuildPhass -> Link Binary With Libraries中添加bonreeAgent.framework，如图所示：

![image](https://github.com/TuYuWang/NewBonreeAgent/raw/master/img/Link.png)

3、添加以下依赖库:

- CoreLocation.framework
- CoreTelephony.framework
- Security.framework
- SystemConfiguration.framework
- libz.1.2.5.tbd
- libresolv.9.tbd
- libc++.tbd

![image](https://github.com/TuYuWang/NewBonreeAgent/raw/master/img/Dependce.png)

4、在Build Setting中搜索Other Linker Flags, 添加编译标志-ObjC。如图所示:

![image](https://github.com/TuYuWang/NewBonreeAgent/raw/master/img/OtherLinker.png)

5、嵌码

- Objective-C
- Swift
- Cocoapods

Objective-C：

（1）引入头文件: 在AppDelegate.m中导入头文件。

（2）在application:didFinishLaunchingWithOptions中设置config地址与AppId，如图所示:

[BRSAgent setConﬁgAddress:@“https://sdkupload.bonree.com/conﬁg/"];

[BRSAgent startWithAppID:@“40766f87-13a8-48d3-9c96-1ce7c3cde50f”];

![image](https://github.com/TuYuWang/NewBonreeAgent/raw/master/img/OC.png)

Swift:

（1）在对应的桥接⽂件⾥bridging-header.h⾥导⼊头⽂件，如图所示:

![image](https://github.com/TuYuWang/NewBonreeAgent/raw/master/img/Swift-H.png)

（2）注释掉AppDelegate.swift⾥设置config地址和AppId，如图所示:

![image](https://github.com/TuYuWang/NewBonreeAgent/raw/master/img/Swift.png)

(参数字符串是在网站上得到的appid,现在临时用40766f87-13a8-48d3-9c96-1ce7c3cde50f)

运行后有日志 bonreeAgent config succeeded ,即表示嵌码成功,如下图:

![image](https://github.com/TuYuWang/NewBonreeAgent/raw/master/img/success.png)

Cocoapods:

（1）此方式目前只支持公有云。

（2）在工程Podfile文件中添加 -> pod ‘bonreeAgent’



### API

//设置下载渠道名称 

+(void)setChannelName:(NSString*)channelName;

//自定义事件 

+(void)trackEvent:(NSString*)eventID name:(NSString*)eventName;

//自定义事件(客户可通过dictionary<key,value>参数增加对事件的描述，key为NSString

类型，val- ue为NSString或NSNumber类型)

+(void)trackEvent:(NSString*)eventID name:(NSString*)eventName parameters:

(NSDictionary*)dictionary;

/* 

标记页面开始和结束,这两个接口需要成对调用. 在viewWillAppear或者viewDidAppear调用

trackPageBegin方法 在viewWillDisappear或者viewDidDisappear调用trackPageEnd方法

*/ 

+(void)trackPageBegin:(NSString *)pageId pageName:(NSString *)pageName; +

(void)trackPageEnd:(NSString *)pageId pageName:(NSString*)pageName;

//设置会员id 

+(void)setMemberId:(NSString *)memberId;

//设置⽤用户信息(客户可通过kv<key,value>参数增加用户信息，key为NSString类型，

value为 NSString或NSNumber类型)

+(void)setUserInfo:(NSDictionary *)kv; 例:

NSDictionary *infoDic = @{@"br_test_number":@10086,@"brs_test_str":@"string"};

[BRSAgent setUserInfo:infoDic];



//设置app版本(请在bonreeAgent启动之前设置)

+(void)setAppVersion:(NSString*)appVersion;

//即时upload接口，客户调用该接⼝口，将sdk目前保存的数据及当前视图的信息直接上传，返回值为 YES表示上传成功，NO表示上传失败。(同步上传，建议客户启用新的线程调用)

+(BOOL)upload;



### 其它

cocoapods的配置:(cocoapods的版本只支持公有云) 在工程Podfile文件中添加

pod ‘bonreeAgent’ 

或者 pod ‘bonreeAgent’, ‘版本号’ 即可

增加config地址接口(须在sdk初始化接口startWithAppID之前调用，否则私有云地址设置将无法生 效):



私有云需要调用setConfigAddress,设置config地址,具体地址由技术提供 

例:

[BRSAgent setConfigAddress:@"https://sdkconfig.reedoun.com/config/"];

接口说明: 具体见bonreeAgent.h

