//
//  MyoFeature.h
//  Da-Vinci Cuffs
//
//  Created by Terry Clark on 29/11/2018.
//

#pragma once

#include <array>
#include <string>

struct EMG {
    std::array<double, 8> absRaw;
    std::array<double, 8> bayes;
    std::array<double, 8> fod;
    std::array<double, 8> fodMin;
    std::array<double, 8> fodMax;
    std::array<double, 8> mean;
    std::array<double, 8> raw;
    std::array<double, 8> rawMin;
    std::array<double, 8> rawMax;
    std::array<double, 8> rms;
    std::array<double, 8> sod;
    std::array<double, 8> sodMin;
    std::array<double, 8> sodMax;
    std::array<double, 8> stdDev;
    std::array<double, 8> zeroXs;

    //Saponas Ratios
    std::array<double, 28> bayesRatio;
    std::array<double, 28> rmsRatio;
    std::array<double, 28> stdRatio;
};

struct Accel {
    double pitch = 0.0;
    double yaw = 0.0;
    double roll = 0.0;
    
    std::array<double, 3> raw;
    std::array<double, 3> rawMin;
    std::array<double, 3> rawMax;
    std::array<double, 3> absRaw;
    std::array<double, 3> bayes;
    std::array<double, 3> fod;
    std::array<double, 3> fodMin;
    std::array<double, 3> fodMax;
    std::array<double, 3> mean;
    std::array<double, 3> rms;
    std::array<double, 3> sod;
    std::array<double, 3> sodMin;
    std::array<double, 3> sodMax;
    std::array<double, 3> stdDev;
    std::array<double, 3> zeroXs;
    
    //Saponas Ratios
    std::array<double, 6> bayesRatio;
    std::array<double, 6> rmsRatio;
    std::array<double, 6> stdRatio;
};

struct MyoData {
    int ID;
    EMG emg;
    Accel acc;
    Accel gyro;
    std::array<double, 4> quat;
    std::string pose;
    int poseID;
    int whichArm;
};
