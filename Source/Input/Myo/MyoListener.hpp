//
//  MyoListener.hpp
//  Da-Vinci Cuffs - App
//
//  Created by Terry Clark on 28/11/2018.
//

#pragma once


#include "MyoData.h"
#include "myo/myo.hpp"
#include "../JuceLibraryCode/JuceHeader.h"

class MyoListener : public myo::DeviceListener {
public:
    MyoListener();
  
    void onConnect(myo::Myo* myo, uint64_t timestamp, myo::FirmwareVersion firmwareVersion);
    void onPair(myo::Myo* myo, uint64_t timestamp, myo::FirmwareVersion firmwareVersion);
    
    void onDisconnect(myo::Myo* myo, uint64_t timestamp);
    void onUnpair(myo::Myo* myo, uint64_t timestamp);
    
    void onUnlock(myo::Myo* myo, uint64_t timestamp);
    void onLock(myo::Myo* myo, uint64_t timestamp);
    
    void onArmSync(myo::Myo* myo, uint64_t timestamp, myo::Arm arm, myo::XDirection xDirection);
    void onArmUnsync(myo::Myo* myo, uint64_t timestamp);
    
    void onEmgData(myo::Myo* myo, uint64_t timestamp, const int8_t* emg);
    
    void onAccelerometerData(myo::Myo* myo, uint64_t timestamp, const myo::Vector3<float>& accel);
    void onGyroscopeData(myo::Myo* myo, uint64_t timestamp, const myo::Vector3<float>& gyro);
    void onOrientationData(myo::Myo* myo, uint64_t timestamp, const myo::Quaternion<float>& quat);
    
    void onPose(myo::Myo* myo, uint64_t timestamp, myo::Pose pose);
    
    int getMyoID(myo::Myo* myo);
    std::vector<MyoData> getMyoData() const;
    
    std::vector<myo::Myo*> knownMyos;
    std::vector<MyoData> myoData;
    
    myo::Arm whichArm;
    myo::Pose currentPose;
    
    bool onArm;
    bool isUnlocked;
 
    float yaw, pitch, roll;
    float yaw_w,pitch_w, roll_w;
   
    int numberOfMyos;
};


