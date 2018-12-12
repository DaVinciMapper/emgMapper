//
//  MyoComponent.hpp
//  NewProject - App
//
//  Created by Terry Clark on 27/11/2018.
//

#pragma once

#include "MyoListener.hpp"

class MyoComponent : public Component,
                     private Thread,
                     private ReadWriteLock
{
    public:
        MyoComponent();
        ~MyoComponent();
    
        bool connect();
        void run() override;
        void disconnect();
        void startPoll();
        void stopPoll();
        void vibrate(String VibrationType);

        std::vector<MyoData> getMyoData (bool &success) const;
    
    private:
        myo::Hub *hub;
        myo::Myo *myo;
        MyoListener listener;
        std::vector<MyoData> myoData;
};
