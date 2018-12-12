//
//  MyoListener.cpp
//  Da-Vinci Cuffs - App
//
//  Created by Terry Clark on 28/11/2018.
//

#include "MyoListener.hpp"

MyoListener::MyoListener()
:
whichArm(),
currentPose(),
onArm(false),
isUnlocked(false)
{
    
}

void MyoListener::onConnect(myo::Myo* myo, uint64_t timestamp, myo::FirmwareVersion firmwareVersion)
{
    
    knownMyos.push_back(myo);
    myoData.resize (knownMyos.size());
    myo->setStreamEmg (myo::Myo::streamEmgEnabled);
    myo->unlock (myo::Myo::unlockHold);
    
    int myoID = getMyoID(myo);
    
    myoData[myoID].ID = myoID;
    
    std::cout << "Myo " << getMyoID(myo) << " has connected" << std::endl;
}

void MyoListener::onPair(myo::Myo* myo, uint64_t timestamp, myo::FirmwareVersion firmwareVersion)
{
    knownMyos.push_back(myo);
    myoData.resize (knownMyos.size());
    myo->setStreamEmg (myo::Myo::streamEmgEnabled);
    myo->unlock (myo::Myo::unlockHold);
    std::cout << "Paired with " << getMyoID(myo) << std::endl;
}

void MyoListener::onDisconnect(myo::Myo* myo, uint64_t timestamp)
{
    std::cout << "Myo " << getMyoID(myo) << " has disconnected." << std::endl;
}

void MyoListener::onUnpair(myo::Myo* myo, uint64_t timestamp)
{
    std::cout << "Unpaired with " << getMyoID(myo) << std::endl;
}


void MyoListener::onUnlock(myo::Myo* myo, uint64_t timestamp)
{
   
    isUnlocked = true;
}

void MyoListener::onLock(myo::Myo* myo, uint64_t timestamp)
{
    isUnlocked = false;
}


void MyoListener::onEmgData(myo::Myo* myo, uint64_t timestamp, const int8_t* emg)
{
    int myoID = getMyoID(myo);
    if (myoID == -1) return;
    
    for (unsigned int i = 0; i < 8; ++i)
    {
        myoData[myoID].emg.raw[i] = emg[i];
    }
}

void MyoListener::onAccelerometerData(myo::Myo* myo, uint64_t timestamp, const myo::Vector3<float>& accel)
{
    int myoID = getMyoID(myo);
    if (myoID == -1) return;
    
    myoData[myoID].acc.raw[0] = accel.x();
    myoData[myoID].acc.raw[1] = accel.y();
    myoData[myoID].acc.raw[2] = accel.z();
}


void MyoListener::onGyroscopeData(myo::Myo* myo, uint64_t timestamp, const myo::Vector3<float>& gyro)
{
    int myoID = getMyoID(myo);
    if (myoID == -1) return;

    myoData[myoID].gyro.raw[0] = gyro.x();
    myoData[myoID].gyro.raw[1] = gyro.y();
    myoData[myoID].gyro.raw[2] = gyro.z();
}

void MyoListener::onOrientationData(myo::Myo* myo, uint64_t timestamp, const myo::Quaternion<float>& quat)
{
    using std::atan2;
    using std::asin;
    using std::sqrt;
    
    // Calculate Euler angles (roll, pitch, and yaw) from the unit quaternion.
    float roll = atan2(2.0f * (quat.w() * quat.x() + quat.y() * quat.z()),
                       1.0f - 2.0f * (quat.x() * quat.x() + quat.y() * quat.y()));
    float pitch = asin(2.0f * (quat.w() * quat.y() - quat.z() * quat.x()));
    float yaw = atan2(2.0f * (quat.w() * quat.z() + quat.x() * quat.y()),
                      1.0f - 2.0f * (quat.y() * quat.y() + quat.z() * quat.z()));
    
    // Convert the floating point angles in radians to a scale from 0 to 20.
    roll_w = static_cast<int>((roll + (float)M_PI)/(M_PI * 2.0f) * 18);
    pitch_w = static_cast<int>((pitch + (float)M_PI/2.0f)/M_PI * 18);
    yaw_w = static_cast<int>((yaw + (float)M_PI)/(M_PI * 2.0f) * 18);
}

void MyoListener::onArmSync(myo::Myo *myo, uint64_t timestamp, myo::Arm arm, myo::XDirection xDirection){
    onArm = false;
}

void MyoListener::onArmUnsync(myo::Myo *myo, uint64_t timestamp)
{
    onArm = false;
    std::cout << "Myo " << getMyoID(myo) << " arm has unsynced." << std::endl;
}

void MyoListener::onPose(myo::Myo* myo, uint64_t timestamp, myo::Pose pose)
{
    int poseID = 0;
    int myoID = getMyoID(myo);
    if (myoID == -1) return;
    
    if (pose==myo::Pose::unknown) poseID = -1;
    if (pose==myo::Pose::rest) poseID = 0;
    if (pose==myo::Pose::fist) poseID = 1;
    if (pose==myo::Pose::fingersSpread) poseID = 2;
    if (pose==myo::Pose::waveIn) poseID = 3;
    if (pose==myo::Pose::waveOut) poseID = 4;
    if (pose==myo::Pose::doubleTap) poseID = 5;
    
    myoData[myoID].pose = pose.toString();
    myoData[myoID].poseID = myoID;
    
    std::cout << "Myo " << getMyoID(myo) << " switched to pose " << pose.toString() << "." << std::endl;
}

std::vector<MyoData> MyoListener::getMyoData() const
{
    return myoData;
}

int MyoListener::getMyoID(myo::Myo* myo)
{
    // Walk through the list of Myo devices that we've seen pairing events for.
    for (unsigned int i = 0; i < knownMyos.size(); ++i)
    {
        // If two Myo pointers compare equal, they refer to the same Myo device.
        if (knownMyos[i] == myo) {
            return i;
        }
    }
    return -1;
}

