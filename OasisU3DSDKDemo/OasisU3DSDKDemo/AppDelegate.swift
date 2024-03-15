//
//  AppDelegate.swift
//  OasisU3DSDKDemo
//
//  Created by Carmine on 2021/5/20.
//

import UIKit
import OasisUnitySDK

@main
class AppDelegate: UIResponder, UIApplicationDelegate {

    public let kOasisUnitySDKEnv:OasisUnitySDKEnv = .publicChannel

    var window: UIWindow? // for iOS 12
    
    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
        // Override point for customization after application launch.
        
        /**
         【接入】阶段1.1 - 判断当前设备是否支持
         如果不支持，需要接入方app处理此场景，如给出提醒或者隐藏体验入口
         */
        if !AROasisUnityManager.isSDKSupported() {
            assert(false, "This device is not supported.")
        }

        /**
         【接入】阶段1.2 - appkey/secret注册
         每个app都有对应一套独立的key和secret，请提前联系商务获取
         */
        let appKey = kOasisUnitySDKEnv.appKey
        let appSecret = kOasisUnitySDKEnv.appSecret
        // app 启动时一定要先注册
        AROasisUnityManager.shared()?.registerAppKey(appKey, appSecret: appSecret, launchOptions: launchOptions)
        /**
         【接入】阶段1.3 - 设置日志级别
         接入阶段免不了有暴露问题，建议debug模式下打开日志输出
         */
        #if DEBUG
        AROasisUnityManager.setLogLevel(.DEBUG)
        #else
        AROasisUnityManager.setLogLevel(.OFF)
        #endif
        
        return true
    }

    // MARK: UISceneSession Lifecycle

    @available(iOS 13.0, *)
    func application(_ application: UIApplication, configurationForConnecting connectingSceneSession: UISceneSession, options: UIScene.ConnectionOptions) -> UISceneConfiguration {
        // Called when a new scene session is being created.
        // Use this method to select a configuration to create the new scene with.
        return UISceneConfiguration(name: "Default Configuration", sessionRole: connectingSceneSession.role)
    }

    @available(iOS 13.0, *)
    func application(_ application: UIApplication, didDiscardSceneSessions sceneSessions: Set<UISceneSession>) {
        // Called when the user discards a scene session.
        // If any sessions were discarded while the application was not running, this will be called shortly after application:didFinishLaunchingWithOptions.
        // Use this method to release any resources that were specific to the discarded scenes, as they will not return.
    }
    
    /// onlineFormal Demo 测试用的正式组织
    /// onlineTest Demo 测试用的测试组织
    /// ❗第三方接入APP应当向产品申请自己的AppKey（需要提供bundleID）
    public enum OasisUnitySDKEnv:Int {
        
        case publicChannel
        
        var appKey: String {
            switch self {
            case .publicChannel:
                return "NAR-XWBH-EPF0FGUDY4OLF-I-F"
            }
        }
        
        var appSecret: String {
            switch self {
            case .publicChannel:
                return "Qn5NkNzbTt"
            }
        }
    }

}

