//
//  ARMaskLoadingView.swift
//  OasisUnitySDKDemo
//
//  Created by Carmine on 2021/7/28.
//  Copyright © 2021 Dikey. All rights reserved.
//

import UIKit
import SnapKit
import OasisUnityPlugin

class ARPOILoadingView: UIView {

    var circleImageView: UIImageView!
    var tipsLabel: UILabel!

    init(frame: CGRect, type: IARSceneLoadingType) {
        super.init(frame: frame)
        setupSubviews(type: type)
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    func setupSubviews(type: IARSceneLoadingType) {
        self.backgroundColor = .init(white: 0, alpha: 0.2)
        self.isUserInteractionEnabled = true
        
        let kContainerWidth: CGFloat = 170
        let kContainerHeight: CGFloat = 40
        let container = UIView()
        if type == .unloading {
            container.backgroundColor = UIColor.init(white: 1, alpha: 0.2)
        } else {
            container.backgroundColor = UIColor.init(white: 0, alpha: 0.7)
        }
        container.layer.cornerRadius = kContainerHeight / 2
        addSubview(container)
        container.snp.makeConstraints { make in
            make.center.equalTo(self)
            make.width.equalTo(kContainerWidth)
            make.height.equalTo(kContainerHeight)
        }
        
        // animated circle view
        let imageW: CGFloat = 14
        let imageView = UIImageView.init(image: UIImage.init(named: "loading_icon"))
        addSubview(imageView)
        imageView.snp.makeConstraints { make in
            make.leading.equalTo(container).offset(31)
            make.centerY.equalTo(container)
            make.height.width.equalTo(imageW)
        }
        circleImageView = imageView
        
        // label
        
        let label = UILabel.init()
        if type == .unloading {
            label.text = "正在退出..."
        } else {
            label.text = "正在载入内容"
        }
        label.textColor = .white
        label.font = UIFont.systemFont(ofSize: 14)
        addSubview(label)
        label.snp.makeConstraints { make in
            make.leading.equalTo(imageView.snp.trailing).offset(8)
            make.centerY.equalTo(imageView)
            make.height.equalTo(20)
            make.trailing.equalTo(container).offset(10)
        }
        tipsLabel = label
    }
    
    func performAnimations() -> Void {
        circleImageView.layer.removeAllAnimations()
        circleImageView.layer.add(rotateAnimation(), forKey: "kCircleAnimationKey")
    }
    
    private func rotateAnimation() -> CABasicAnimation! {
        let animation = CABasicAnimation.init(keyPath: "transform.rotation.z")
        animation.fromValue = NSNumber.init(value: 0)
        animation.toValue = NSNumber.init(value: Float.pi * 2)
        animation.duration = 1.5
        animation.autoreverses = false
        animation.fillMode = .forwards
        animation.repeatCount = MAXFLOAT
        return animation
    }
    
}
