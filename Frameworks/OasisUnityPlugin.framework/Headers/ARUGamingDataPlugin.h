//
//  ARUGamingDataPlugin.h
//  InsightSDK
//
//  Created by Dikey on 2019/6/10.
//  Copyright © 2019 DikeyKing. All rights reserved.
//

#ifndef ARUGamingDataPlugin_h
#define ARUGamingDataPlugin_h

#ifdef __cplusplus
extern "C" {
#endif
    
    typedef void (*Are_ReceiveSocketData_Callback)(const void *inputData ,int length, void *userData ,uint64_t socketID );
    
    /**
     connectStatus = 1 链接上了
     connectStatus = 2 断开链接了
     */
    typedef void (*Are_SocketConnectStatus_Callback)(int connectStatus, void *userData ,uint64_t socketID);

    /**
     创建一个socket对象

     @param userData 给引擎用
     @return hash 值，该值对应了Native一个内存中的实例对象
     */
    uint64_t are_CreateSocket(void const *userData);
    
    /**
     TCP 长连接——create new socket instance
     
     @param ipAddress IP address
     @param port port
     @param socketID socketID
	 @return error code，0表示没有错误
     */
    int32_t are_ConnectToHost(const char *ipAddress,
                           uint32_t port, // 不要超过 uint16_t
                           uint64_t socketID);
    

    void are_SetConnectStatusCallback(Are_SocketConnectStatus_Callback callback,
                                      void *userData,
                                      uint64_t socketID);

    /**
     设置回调
     
     @param callback ReceiveSocketDataCalback
     */
    void are_SetReceiveSocketDataCallback(Are_ReceiveSocketData_Callback callback,
                                         void *userData,
                                         uint64_t socketID);

    /**
     发送PB数据给服务器，之后将由Socket服务器同步给其他房间中的玩家
     
     @param inputData PB 数据
     @param length data length
     @param timeout 默认传-1
     */
    int32_t are_SendData(const void * inputData,
                      int length,
                      int timeout,
                      void const *userData,
                      uint64_t socketID);
    
    /**
     断开socket连接
     */
    void are_DisconnectSocket(uint64_t socketID);
    
#ifdef __cplusplus
}
#endif
#endif /* ARUGamingDataPlugin_h */
