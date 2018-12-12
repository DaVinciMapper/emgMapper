//
//  MyoComponent.cpp
//  NewProject - App
//
//  Created by Terry Clark on 27/11/2018.
//

#include "MyoComponent.hpp"

MyoComponent::MyoComponent()
:
Thread("Myo Data Thread"),
hub(nullptr),
myo(nullptr)
{
//    s/tartPoll();
}

MyoComponent::~MyoComponent()
{
    disconnect();
    stopPoll();
}

bool MyoComponent::connect()
{
    disconnect();
    
    bool isConnected = false;
    
    try
    {
        if ((hub = new myo::Hub("com.yourcompany.DaVinciMapper")))
        {
            std::cout << "Attempting to find a Myo..." << std::endl;
            hub->addListener(&listener);
            listener.knownMyos.push_back(myo);
            myo = hub->waitForMyo(1000);
        }
        else
        {
            std::cerr << "Error: Myo not found" << std::endl;
            AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                         "Myo not found",
                                         "Open Myo Connect and conncect a Myo armband before opening Da-Vinci Cuffs.",
                                         "OK");
            disconnect();
            JUCEApplication::quit();
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                     "Error",
                                     "Open Myo Connect and conncect a Myo armband before opening Da-Vinci Cuffs.",
                                     "OK");
        disconnect();
        JUCEApplication::quit();
    }
    
    return isConnected;
}

void MyoComponent::run()
{
    if (!myo) return;
    
    while (!threadShouldExit())
    {
        hub->runOnce(20);
        if (tryEnterWrite())
        {
            myoData = listener.getMyoData();
            exitWrite();
        }
    }
}

std::vector<MyoData> MyoComponent::getMyoData(bool &success) const
{
    std::vector<MyoData> dataCopy;
    if (tryEnterRead())
    {
        dataCopy = myoData;
        success = true;        
        exitRead();
    }
    
    return dataCopy;
}

void MyoComponent::disconnect(){
    myo = nullptr;
    
    if (!hub){ return; }
    
    stopPoll();
    
    hub->removeListener(&listener);
    delete hub;
    hub = nullptr;
}

void MyoComponent::startPoll(){
    startThread();
}

void MyoComponent::stopPoll(){
    stopThread(1000);
}

void MyoComponent::vibrate(String VibrationType)
{
    if(VibrationType == "long")
        myo->vibrate(myo::Myo::vibrationLong);
    if(VibrationType == "medium")
        myo->vibrate(myo::Myo::vibrationMedium);
    if(VibrationType == "short")
        myo->vibrate(myo::Myo::vibrationShort);
}
