# jni-example-code
jni-example

用途：

start.c通过jni调用Proj.java中的函数

步骤：
先编译java，因为start.c中需要用到该类

/usr/local/jdk1.8.0_161/bin/javac Prog.java

编译start

gcc start.c -o start -I /usr/local/jdk1.8.0_161/include/ -I /usr/local/jdk1.8.0_161/include/linux/ -L /usr/local/jdk1.8.0_161/jre/lib/amd64/server/ -ljvm -Wl,-rpath,/usr/local/jdk1.8.0_161/jre/lib/amd64/server






需要注意，编译start时候指定的jdk(libjvm)和编译Proj.java的编译器javac版本相同。
比如如下问题
https://www.cnblogs.com/saule/p/11358085.html
交代一下背景：公司运行的一个上线项目，打了个补丁发给客户后，反馈说运行不了。把源码拿回来场景重现。贴上报错信息：
8-15 14:13:29 ERROR doPost(jcm.framework.rmi.RMIServlet:155) - SchedulerService.forceRunJobFlow error.
未指定错误，请查看详细信息
    at jcm.framework.rmi.ClientService.execute(ClientService.java:129)
    at ...(...)
    at jcm.flowengine.impl.JobFlowEngine.runJobFlow(JobFlowEngine.java:230)
Caused by: java.lang.UnsupportedClassVersionError: jcm/flowengine/impl/JobFlowInstance : Unsupported major.minor version 52.0 (unable to load class jcm.flowengine.impl.JobFlowInstance)
    at org.apache.catalina.loader.WebappClassLoader.findClassInternal(WebappClassLoader.java:2908)
    at org.apache.catalina.loader.WebappClassLoader.findClass(WebappClassLoader.java:1173)
    at org.apache.catalina.loader.WebappClassLoader.loadClass(WebappClassLoader.java:1681)
    at org.apache.catalina.loader.WebappClassLoader.loadClass(WebappClassLoader.java:1559)
    at jcm.flowengine.impl.JobFlowEngine.runJobFlow(JobFlowEngine.java:230)
    at jcm.scheduler.impl.StdScheduler.forceRun(StdScheduler.java:190)
    at jcm.scheduler.service.SchedulerService.forceRunJobFlow(SchedulerService.java:57)
    at sun.reflect.NativeMethodAccessorImpl.invoke0(Native Method)
    at sun.reflect.NativeMethodAccessorImpl.invoke(NativeMethodAccessorImpl.java:57)
    at sun.reflect.DelegatingMethodAccessorImpl.invoke(DelegatingMethodAccessorImpl.java:43)
    at java.lang.reflect.Method.invoke(Method.java:606)
    at jcm.framework.rmi.ClientService.execute(ClientService.java:113)
    at jcm.framework.rmi.RMIServlet.doPost(RMIServlet.java:113)
    at javax.servlet.http.HttpServlet.service(HttpServlet.java:647)
    at javax.servlet.http.HttpServlet.service(HttpServlet.java:728)
    at org.apache.catalina.core.ApplicationFilterChain.internalDoFilter(ApplicationFilterChain.java:305)
    at org.apache.catalina.core.ApplicationFilterChain.doFilter(ApplicationFilterChain.java:210)
    at org.apache.catalina.core.StandardWrapperValve.invoke(StandardWrapperValve.java:222)
    at org.apache.catalina.core.StandardContextValve.invoke(StandardContextValve.java:123)
    at org.apache.catalina.authenticator.AuthenticatorBase.invoke(AuthenticatorBase.java:472)
    at org.apache.catalina.core.StandardHostValve.invoke(StandardHostValve.java:171)
    at org.apache.catalina.valves.ErrorReportValve.invoke(ErrorReportValve.java:99)
    at org.apache.catalina.valves.AccessLogValve.invoke(AccessLogValve.java:936)
    at org.apache.catalina.core.StandardEngineValve.invoke(StandardEngineValve.java:118)
    at org.apache.catalina.connector.CoyoteAdapter.service(CoyoteAdapter.java:407)
    at org.apache.coyote.http11.AbstractHttp11Processor.process(AbstractHttp11Processor.java:1004)
    at org.apache.coyote.AbstractProtocol$AbstractConnectionHandler.process(AbstractProtocol.java:589)
    at org.apache.tomcat.util.net.AprEndpoint$SocketProcessor.run(AprEndpoint.java:1822)
       at java.util.concurrent.ThreadPoolExecutor.runWorker(ThreadPoolExecutor.java:1145)
    at java.util.concurrent.ThreadPoolExecutor$Worker.run(ThreadPoolExecutor.java:615)
    at java.lang.Thread.run(Thread.java:745)


查看报错信息，发现是由于JDK版本不对导致。客户运行的项目编译版本是JDK1.5,补丁编译版本是JDK1.8。
要解决这问题，首先我们得知道客户运行的版本是多少。这里有个方法：随便复制一个客户项目的jar包，用解压缩工具解压，在CMD命令中切换到当前
目录，输入命令：javap -verbose classname
classname为解压出来的任意一个class文件名。
会一下信息输出：


Classfile /E:/abc/JCMCommon/jcm/common/LogInfo.class
  Last modified 2015-6-3; size 3087 bytes
  MD5 checksum 8d1347215ae5933e04ad60dacbadfe41
  Compiled from "LogInfo.java"
public abstract class jcm.common.LogInfo extends java.lang.Enum<jcm.common.LogInfo>
  Signature: #138                         // Ljava/lang/Enum<Ljcm/common/LogInfo;>;
  SourceFile: "LogInfo.java"
  InnerClasses:
       static final #8; //class jcm/common/LogInfo$1
       static final #12; //class jcm/common/LogInfo$2
       static final #16; //class jcm/common/LogInfo$3
       static final #20; //class jcm/common/LogInfo$4
       static final #24; //class jcm/common/LogInfo$5
       static final #28; //class jcm/common/LogInfo$6
       static final #32; //class jcm/common/LogInfo$7
       static final #36; //class jcm/common/LogInfo$8
       static final #40; //class jcm/common/LogInfo$9
       static final #44; //class jcm/common/LogInfo$10
       static final #48; //class jcm/common/LogInfo$11
       static final #52; //class jcm/common/LogInfo$12
       static final #56; //class jcm/common/LogInfo$13
       static final #60; //class jcm/common/LogInfo$14
       static final #64; //class jcm/common/LogInfo$15
       static final #68; //class jcm/common/LogInfo$16
       static final #72; //class jcm/common/LogInfo$17
       static final #76; //class jcm/common/LogInfo$18
       static final #80; //class jcm/common/LogInfo$19
       static final #84; //class jcm/common/LogInfo$20
  minor version: 0
  major version: 49
  flags: ACC_PUBLIC, ACC_SUPER, ACC_ABSTRACT, ACC_ENUM
  。。。。。。

信息可能很多，看不到前面的信息。可以用命令：javap -verbose classname >文本文件名.txt ，把信息写入文件。从上面信息可以查看版本信息

minor version: 0
major version: 49

查看JDK版本对应关系

34（对应十进制的50）：JDK1.8

33（对应十进制的50）：JDK1.7

32（对应十进制的50）：JDK1.6

31（对应十进制的49）：JDK1.5

30（对应十进制的48）：JDK1.4

2F（对应十进制的47）：JDK1.3

2E（对应十进制的46）：JDK1.2

可以看出，项目的编译版本是1.5，打补丁根据对应的版本编译就不会有问题了。




运行：
./start
