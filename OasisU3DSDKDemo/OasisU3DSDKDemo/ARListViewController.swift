//
//  ARListViewController.swift
//  OasisU3DSDKDemo
//
//  Created by Carmine on 2021/7/30.
//

import UIKit
import OasisUnitySDK

class ARListViewController: UITableViewController {
    
    // 列表数据
    var sceneLandmarks = [AROasisUnityLandmarker]()

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        tableView.register(UINib.init(nibName: "ARSceneCell", bundle: nil), forCellReuseIdentifier: "ARSceneCell")
        
        let refreshControl = UIRefreshControl()
        refreshControl.addTarget(self, action: #selector(requestNearbyLandmarks), for: .valueChanged)
        refreshControl.tintColor = .blue
        refreshControl.attributedTitle = NSAttributedString.init(string: "下拉刷新")
        tableView.refreshControl = refreshControl
    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        requestNearbyLandmarks()
    }
    
    
    @objc fileprivate
    func requestNearbyLandmarks() -> Void {
       // app，联系商务获取
        let longitude = 120.22879352547804
        let latitude = 30.244541980326094
        // 构造请求，默认获取最近的可体验内容
        
        let prepareOptions = AROasisUnityLandmarkersPrepareOption.init(coordiType: .WGS84, longitude: longitude, latitude: latitude, maxDistance: 99999999, tagIds: "")
        
        AROasisUnityManager.shared().queryLandmarkers(prepareOptions) { landmarks in
            self.tableView.refreshControl?.endRefreshing()
            if let results = landmarks {
                print("可体验的列表：" + results.debugDescription)
                self.sceneLandmarks.removeAll()
                self.sceneLandmarks.append(contentsOf: results)
                self.tableView.reloadData()
            } else {
                print("可体验列表为空")
            }
        } failed: { error in
            print("error" + error.debugDescription)
        }
    }
    
    //MARK:  Delegate & Datasource
    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "ARSceneCell", for: indexPath) as! ARSceneCell
        cell.landmark = sceneLandmarks[indexPath.row]
        return cell
    }
    
    override func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }
    
    override func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        return 90
    }
    
    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return sceneLandmarks.count
    }
    
    override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        let landmark = sceneLandmarks[indexPath.row]
        let storyboard = UIStoryboard.init(name: "Main", bundle: nil)
        let arVC = storyboard.instantiateViewController(withIdentifier: "ARViewController") as! ARViewController
        arVC.cid = landmark.cid
        arVC.modalPresentationStyle = .fullScreen
        
        present(arVC, animated: true, completion: nil)
        
        tableView.deselectRow(at: indexPath, animated: true)
    }
    
}
