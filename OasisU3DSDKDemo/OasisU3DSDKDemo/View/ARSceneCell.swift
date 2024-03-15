//
//  ARSceneCell.swift
//  OasisU3DSDKDemo
//
//  Created by Carmine on 2021/7/30.
//

import UIKit
import SDWebImage
import OasisUnitySDK

class ARSceneCell: UITableViewCell {
    
    @IBOutlet weak var coverImageView: UIImageView!
    @IBOutlet weak var sceneNameLabel: UILabel!
    
    var landmark: AROasisUnityLandmarker! {
        didSet {
            coverImageView.sd_setImage(with: URL.init(string: landmark.coverImageUrl), completed: nil)
            sceneNameLabel.text = landmark.name
        }
    }
    
    override func awakeFromNib() {
        super.awakeFromNib()
        // Initialization code
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }
    
}
