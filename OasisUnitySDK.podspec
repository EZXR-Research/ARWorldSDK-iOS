Pod::Spec.new do |s|

  s.name         = "OasisUnitySDK"
  s.version      = "1.9.5"
  s.summary      = "Oasis AR SDK based on Unity."

  s.homepage     = "https://github.com/EZXR-Research/ARWorldSDK-iOS.git"
  s.license      = "MIT"
  s.author             = { "Carmine" => "zhenghongsheng@ezxr.com" }
  s.social_media_url   = "https://gitlab.com/CarmineCcc"

  # 支持平台
  s.platform     = :ios
  s.platform     = :ios, "12.0"
  s.ios.deployment_target = "12.0"

  # 路径地址
  s.source       = { :git => 'https://github.com/EZXR-Research/ARWorldSDK-iOS.git', :tag => s.version }

  s.source_files  = 'OasisUnitySDK.framework/Headers/*.{h}'
  
  # old way to integarate images
  # s.resource = "OasisUnitySDK.bundle"
  
  # new way to integarate images, after 2.4.4
  # see https://github.com/CocoaPods/CocoaPods/issues/8122 for reason
  s.resource_bundles = {'OasisUnitySDK' => ['Resources/*.xcassets',
                                          'Resources/*.p12',
                                          'Resources/*.cer',]}

  # s.resource = ['Resources/*']
  # s.resource = "InsightSDK.bundle"
  # s.resources = "InsightSDK.xcassets"
  s.frameworks = 'AssetsLibrary', 'AVFoundation', 'CoreMedia', 'CoreMotion', 'Photos'
  s.libraries = 'bz2', 'sqlite3.0', "c++"
  s.requires_arc = true
  s.dependency "SSZipArchive" , ">= 2.0.0"
  s.vendored_frameworks = 'OasisUnitySDK.framework', 'UnityFramework.framework', 'OasisUnityPlugin.framework', 'BeaconLib.framework', 'Mapbox.framework', 'opencv2.framework'
  # s.vendored_libraries = "MMTrackerSDK/**/*.a"

end
