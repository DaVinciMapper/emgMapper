//
//  InputCompoent.hpp
//  Da_Vinci_Cuffs_2_0 - App
//
//  Created by Terry Clark on 01/12/2018.
//

#pragma once

class InputComponent {
public:
    InputComponent();
    virtual ~InputComponent();
    virtual bool connect()=0;
    virtual void disconnect()=0;
    virtual void run()=0;
};
