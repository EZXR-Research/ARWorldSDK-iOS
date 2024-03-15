//
//  ViewController.swift
//  OasisU3DSDKDemo
//
//  Created by Carmine on 2021/5/20.
//

import UIKit
import OasisUnitySDK
import OasisUnityPlugin
import Toast_Swift

class ARViewController: UIViewController {
    
    /// AR 内容输出视图，这里注意 weak，否则会有内存泄露
    weak var oasisView: UIView?
    var cid: Int32 = 161 // 资源的id
    
    @IBOutlet weak var optionStackView: UIStackView!
    
    // loading 动画
    var loadingView: ARLoadingView?
    // 子场景加载动画
    var poiLoadingView: ARPOILoadingView?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        
        requestNearbyLandmarks() // only for test
        
        /**
         【接入】阶段3.0 - Guideline 4.2.3 下载前，app需要告知用户流量消耗
         前置流程需要给出将要下载的内容体积，以及更新场景下，需要更新的体积
         */
        
        //【接入】阶段3.1 - 检查本地是否已经下载过
        if AROasisUnityManager.shared().isDownloadedLandmarker(cid) {
            //【接入】阶段3.2 - 已下载，检查是否需要更新
            AROasisUnityManager.shared().checkUpdate(self.cid) { shouldUpdate, _ in
                if shouldUpdate {
                    // 需要更新，去检查一下新的资源包信息
                    self.queryLandmarkInfo(cid: self.cid, updating: true)
                } else {
                    // 不需要更新
                    // app接入时，考虑是否打断一下，由用户来触发进入
                    if let local = AROasisUnityManager.shared().getLocalLandmarker(self.cid) {
                        self.startOasisRunning(result: local)
                    } else {
                        // 异常情况，本地不存在，就直接获取资源信息重新加载
                        self.queryLandmarkInfo(cid: self.cid, updating: false)
                    }
                }
            } failed: { error in
                self.view.makeToast("Landmark更新检测失败, error:" + error.debugDescription)
            }

        } else {
            // 没有下载过，就直接获取资源信息
            queryLandmarkInfo(cid: self.cid, updating: false)
        }
    }

    /**
     【接入】阶段3.3 - 获取资源描述
     未下载或者需要更新时，都需要查询一下最新的资源包信息，得到下载体积
     */
    fileprivate
    func queryLandmarkInfo(cid: Int32, updating: Bool = false) -> Void {
        AROasisUnityManager.shared().queryLandmarker(cid) { resp in
            if let landmark = resp?.content {
                self.downloadAlert(landmark: landmark, updating: updating)
            } else {
                self.view.makeToast("Landmark信息为空")
            }
        } failed: { error in
            self.view.makeToast("Landmark信息获取失败, error:" + error.debugDescription)
        }

    }
    
    /**
     【接入】阶段3.4 - 流量提醒
     */
    fileprivate
    func downloadAlert(landmark: AROasisUnityLandmarker, updating: Bool = false) -> Void {
        var sizeTips = "发现新版本，下载需消耗流量：\(landmark.totalSize)字节"
        if updating {
            sizeTips = "本次下载需消耗流量：\(landmark.totalSize)字节"
        }
        let alert = UIAlertController.init(title: "流量提醒", message: sizeTips, preferredStyle: .alert)
        alert.addAction(UIAlertAction.init(title: "取消", style: .cancel, handler: { _ in
            // 看下是否使用本地打开的逻辑，app 接入方自己评估下
            self.dismiss(animated: true, completion: nil)
        }))
        var actionTips = "下载"
        if updating { actionTips = "更新" }
        alert.addAction(UIAlertAction.init(title: actionTips, style: .default, handler: { _ in
            let landmarkerOption = AROasisUnityPrepareOption.init(cid: self.cid)!
            self.startRunningWithOption(landmarkerOption: landmarkerOption)
        }))
        self.present(alert, animated: true, completion: nil)
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        self.navigationController?.setNavigationBarHidden(true, animated: animated)
    }
    
    /**
     【接入】阶段2.1（可选） - 动态获取当前位置附近的所有可体验事件
     此方法适用于有多个体验点位的情况，如某个景区有东西南北4个大门，对应了4个体验点；
     可以使用此方法，传入当前GPS（WGS84，大地坐标系）信息，获取所在位置的可体验列表。
     
     如果APP不具备定位能力，需要传入固定坐标时，请联系商务获取。
     */
    fileprivate
    func requestNearbyLandmarks() -> Void {
        // app，联系商务获取
        let longitude = 120.22879352547804
        let latitude = 30.244541980326094
        // 构造请求，默认获取最近的可体验内容
        let prepareOptions = AROasisUnityNearbyLandmarkersPrepareOption.init(longitude: longitude, latitude: latitude)
        // 获取某个位置周边，指定半径和tag标记的列表
//        let prepareOptions = AROasisUnityManagersPrepareOption.init(coordiType: .WGS84, longitude: 120.22879352547804, latitude: 30.244541980326094, maxDistance: 100000, tagIds: "")
        // 按需查询可体验列表
        AROasisUnityManager.shared().queryLandmarkersNearby(prepareOptions) { landmarks in
            if let results = landmarks {
                print("可体验的列表：" + results.debugDescription)
            } else {
                print("可体验列表为空")
            }
        } failed: { error in
            print("error" + error.debugDescription)
        }
    }
    
    //MARK: 加载相关
    
    /// 截屏事件
    @IBAction func screenshotOnClick(_ sender: Any) {
        AROasisUnityManager.shared().screenshot()
    }
    
    func startRunningWithOption(landmarkerOption: AROasisUnityPrepareOption) {
        /**
         【接入】阶段4.1 - 检查SDK是否准备就绪
         由于SDK初始化是异步操作，大约需要2s-5s时间，因此建议在进入场景前，首先判断下是否准备就绪。
         此场景发生在，app打开后，立即进入场景体验时发生，此操作尽量在流程上避免，若无法避免，请app给出重试提醒。
         */
        if !AROasisUnityManager.shared().isReadyToUse() {
            view.makeToast("SDK 初始化未完成，请稍后再试")
            return
        }
        /**
         【接入】阶段4.2 - 下载体验内容
         该方法会加载对应的cid内容并下载，app可以在这里处理下载进度。
         - 如果有新的内容版本发布，该方法会自动触发下载新的内容包。
         - 本地已经下载过，且不需要更新内容包时，会直接返回结果。
         */
        AROasisUnityManager.shared().prepareLandmarker(withOptions: landmarkerOption) { (progress: Progress?) in
            if let progress = progress{
                let complected = progress.fractionCompleted
                let showString = String(format: "下载进度 = %.0f %%", complected*100)
                self.view.makeToast(showString, point: self.view.center, title: nil, image: nil, completion: nil)
            }
        } completion: { error, result in
            if let error = error {
                let alert = UIAlertController(title: "", message: error.localizedDescription, preferredStyle: .alert)
                alert.addAction(UIAlertAction(title: "退出", style: .default, handler: { (action) in
                    self.view.hideAllToasts()
                    self.navigationController?.popViewController(animated: true)
                }))
                self.present(alert, animated: true)
                return
            }
            self.view.hideToast()
            if let result = result {
                self.checkAuthorizationStatusAndStartRunning(result: result)
            }
        }
    }
    
    /**
     【接入】阶段4.3 - 必要权限检测（可选）
     AR 依赖相机权限，如果没有权限，需要阻塞用户进入下一步；
     SDK在初次授权时，会向用户请求一次权限；
     部分case会依赖相册和音频权限，如果app已有现成组件，可以前置获取相关权限
     */
    func checkAuthorizationStatusAndStartRunning(result: AROasisUnityLandmarker) {
        // 增加权限
        if AVCaptureDevice.authorizationStatus(for: .video) == AVAuthorizationStatus.authorized {
            self.startOasisRunning(result: result)
        } else {
            AVCaptureDevice.requestAccess(for: .video) { (granted) in
                if granted == true {
                    DispatchQueue.main.async {
                        self.startOasisRunning(result: result)
                    }
                } else {
                    DispatchQueue.main.async {
                        let alert = UIAlertController(title: "无法获取相机权限", message: "是否去获取", preferredStyle: .alert)
                        alert.addAction(UIAlertAction(title: "否", style: .default, handler: { (action) in
                            self.oasisView?.removeFromSuperview()
                            AROasisUnityManager.shared()?.stopAROasis(withNotifyEngine: true)
                            self.navigationController?.popViewController(animated: true)
                        }))
                        alert.addAction(UIAlertAction(title: "是", style: .default, handler: { (action) in
                            if let url = URL(string: UIApplication.openSettingsURLString) {
                                if UIApplication.shared.canOpenURL(url) {
                                    UIApplication.shared.open(url, options: [:], completionHandler: nil)
                                }
                            }
                            self.oasisView?.removeFromSuperview()
                            AROasisUnityManager.shared()?.stopAROasis(withNotifyEngine: true)
                            self.navigationController?.popViewController(animated: true)
                        }))
                        self.present(alert, animated: true)
                    }
                }
            }
        }
    }
    
    /**
     【接入】阶段4.4 - 加载场景，最核心的方法
     无论是从2.1的列表中，或是从2.2的单个事件下载完成中到达这里，都可以直接加载AR，AROasisUnityManager封装了AR的全部描述信息
     */
    func startOasisRunning(result: AROasisUnityLandmarker) {
        AROasisUnityManager.shared().startRunning(result) { [unowned self] result in
            guard let result = result else{
                return
            }
            if result.state == .error {
                return
            }
            if self.oasisView == nil {
                /**
                【接入】阶段4.5 - 添加AR输出视图
                防止挡住app已有的UI控件，最好把视图添加到最底层
                */
                if let oasisView = AROasisUnityManager.shared()?.getOasisView() {
                    self.oasisView = oasisView
                    self.view.insertSubview(oasisView, at: 0)
                } else {
                    debugPrint("nil Oasis View")
                }
            }
        } eventCallback: { [unowned self] event in
            self.handleAREvent(event: event)
        } loadCallback: { [unowned self] loadEvent in
            self.handleLifeCycle(lifeEvent: loadEvent)
        }
    }
    
    //MARK: 处理交互事件
    fileprivate
    func handleAREvent(event: AROasisUnityEvent?) -> Void {
        guard let event = event else { return }
        switch event.type {
        case .function_RunScript: // AR 脚本交互，一般用不到
            let data = try? JSONSerialization.data(withJSONObject: event.params ?? "", options: [])
            let str = String(data: data!, encoding: String.Encoding.utf8)
            AROasisUnityManager.shared().runOasisScript("test", param: str) { event in
                print("ARScript脚本执行完成")
            }
        case .function_ScreenShot: // 截屏事件，这里只是做了演示，具体需要app关注后续操作
            if let image = event.params["image"] as? UIImage {
                let imageView = UIImageView.init(image: image)
                imageView.frame = CGRect.init(origin: .zero, size: CGSize.init(width: image.size.width/UIScreen.main.scale/2, height: image.size.height/UIScreen.main.scale/2))
                imageView.center = self.view.center
                self.view.addSubview(imageView)
                DispatchQueue.main.asyncAfter(deadline: .now() + 2) {
                    imageView.removeFromSuperview()
                }
            }
        case .function_Share:
            print(event.params as Any)
            let params = event.params as NSDictionary
            if let path = params["imagepath"] as? String {
                guard let image = UIImage(contentsOfFile: path) else{
                    print("error:function_Share")
                    return
                }
                let imageView = UIImageView.init(image: image)
                imageView.frame = CGRect.init(origin: .zero, size: CGSize.init(width: image.size.width/UIScreen.main.scale/2, height: image.size.height/UIScreen.main.scale/2))
                imageView.center = self.view.center
                self.view.addSubview(imageView)
                DispatchQueue.main.asyncAfter(deadline: .now() + 2) {
                    imageView.removeFromSuperview()
                }
            }
            break
        default:
            return
        }
    }
    
    //MARK: 处理声明周期事件
    fileprivate
    func handleLifeCycle(lifeEvent: AROasisUnityLoadEvent?) -> Void {
        /**
         【接入】阶段4.6 - 监测生命周期
         主要是退出事件，即IAREventTypeExitMainContent
         */
        guard let event = lifeEvent else { return }
        switch event.type {
        case .contentLoading:
            print("进度加载开始。")
            if let progress = event.params["progress"] as? NSNumber {
                if let style = event.params["loading_style"] as? Int {
                    let type = IARSceneLoadingType.init(rawValue: style)
                    switch type {
                    case .fullScreen:
                        // 全屏样式，用于下载完成后，内容加载到展示的阶段
                        if self.loadingView == nil {
                            self.loadingView = ARLoadingView.init(frame: self.view.bounds)
                            self.view.addSubview(self.loadingView!)
                        }
                        self.loadingView?.updateProgress(progress: progress.floatValue)
                    case .fullMask:
                        // 用于子场景切换
                        if self.poiLoadingView == nil {
                            self.poiLoadingView = ARPOILoadingView.init(frame: self.view.bounds, type: type!)
                            self.view.addSubview(self.poiLoadingView!)
                            self.poiLoadingView?.performAnimations()
                        }
                    case .unloading:
                        // 用于场景卸载
                        if self.poiLoadingView == nil {
                            self.poiLoadingView = ARPOILoadingView.init(frame: self.view.bounds, type: type!)
                            self.view.addSubview(self.poiLoadingView!)
                            self.poiLoadingView?.performAnimations()
                        }
                    default:
                        _ = "未知的类型"
                    }
                    print("正在打开：\(progress.floatValue)")
                }
            }
        case .contentLoadingCompleted:
            print("进度加载结束。")
            if let style = event.params["loading_style"] as? Int {
                switch IARSceneLoadingType.init(rawValue: style) {
                case .fullScreen:
                    // 全屏样式，用于下载完成后，内容加载到展示的阶段
                    self.loadingView?.removeFromSuperview()
                    self.loadingView = nil
                case .fullMask:
                    // 用于子场景切换
                    self.poiLoadingView?.removeFromSuperview()
                    self.poiLoadingView = nil
                case .unloading:
                    // 用于场景卸载
                    self.poiLoadingView?.removeFromSuperview()
                    self.poiLoadingView = nil
                default:
                    _ = "未知的类型"
                }
            }
        case .loadMainContentSuccess:
            print("表示AR已经加载成功，可以直接打开相机")
//            self.closeButton.isHidden = false
        case .exitMainContent:
            self.oasisView?.removeFromSuperview()
            self.oasisView = nil
            self.dismiss(animated: true, completion: nil)
        default:
            return
        }
        
        UIView.animate(withDuration: 0.25, delay: 0, usingSpringWithDamping: 0.3, initialSpringVelocity: 0.8, options: .curveEaseInOut) {
            //
        } completion: { _ in
            //
        }
        
    }
    
    /// 退出事件
    @IBAction func exitAROnClick(_ sender: Any) {
        if let _ = oasisView {
            AROasisUnityManager.shared().stopAROasis { [unowned self] in
                self.dismiss(animated: true, completion: nil)
            }
        } else {
            self.dismiss(animated: true, completion: nil)
        }
    }

}

