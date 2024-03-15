//
//  ARLoadingView.swift
//  OasisUnitySDKDemo
//
//  Created by Carmine on 2021/7/26.
//  Copyright © 2021 Dikey. All rights reserved.
//

import UIKit
import SnapKit
import Lottie

class ARLoadingView: UIView {

    var animationView = LottieAnimationView()
    var progressView: UIProgressView!
    var loadingLabel: UILabel!
    
    override init(frame: CGRect) {
        super.init(frame: frame)
        setupSubviews()
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    // layout
    fileprivate
    func setupSubviews() -> Void {
        backgroundColor = .black
        
        let animation = LottieAnimationView.init(name: "lottie-loading")
        animation.contentMode = .scaleAspectFit
        addSubview(animation)
        animation.snp.makeConstraints { make in
            make.centerX.equalTo(self)
            make.centerY.equalTo(self).offset(-30)
            make.width.height.equalTo(150)
        }
        playInfiniteAnimations()
        animationView = animation
        
        let label = UILabel()
        label.font = .systemFont(ofSize: 14)
        label.textColor = .white
        label.textAlignment = .center
        addSubview(label)
        loadingLabel = label
        label.snp.makeConstraints { make in
            make.top.equalTo(animationView.snp.bottom).offset(-20) // 这里仅做示例，lottie动画height太大了，fixed
            make.centerX.equalTo(animationView)
            make.width.equalTo(200)
            make.height.equalTo(16)
        }
        
        progressView = UIProgressView()
        progressView.tintColor = .white
        progressView.backgroundColor = .darkGray
        progressView.progressTintColor = .white
        progressView.progress = 0
        addSubview(progressView)
        progressView.snp.makeConstraints { make in
            make.bottom.equalTo(self)
            make.leading.trailing.equalTo(self)
            make.height.equalTo(3)
        }
    }
    
    func updateProgress(progress: Float) -> Void {
        progressView.progress = progress
        loadingLabel.text = String.init(format: "资源加载中（%d%%）", Int(progress*100))
        if !animationView.isAnimationPlaying {
            playInfiniteAnimations()
        }
        if progress == 1 {
            animationView.stop()
        }
    }
    
    fileprivate
    func playInfiniteAnimations() -> Void {
        animationView.play(fromProgress: 0,
                           toProgress: 1,
                           loopMode: LottieLoopMode.loop,
                           completion: { (finished) in
                           })
    }
    
    fileprivate
    func frameImages(frameName: String, frameCount: Int) -> [UIImage] {
        var animatedImages = [UIImage]()
        for i in 0..<frameCount {
            let key = String.init(format: "\(frameName)%2d", i)
            if let image = UIImage.init(named: key) {
                animatedImages.append(image)
            }
        }
        return animatedImages
    }

}
