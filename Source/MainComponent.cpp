/*
  Da-Vinci Cuffs 0.1 is the Brainchild of Terry Lewis Clark.
  contact him @ i.am.terryclark@gmail.com
*/

#include "MainComponent.h"

MainComponent::MainComponent()
{
    myo.connect();
    myo.startPoll();
    addAndMakeVisible(myo);
    addAndMakeVisible(ui);
    
//    lafv4Midnight = new LookAndFeel_V4 (LookAndFeel_V4::getMidnightColourScheme());
   
//    ui.getTabbedButtonBar().setLookAndFeel(lafv4Midnight);
    
//    for (auto * laf : )
//    {
//        //laf->setLookAndFeel());
//    }
   
    setSize(800, 600);
    startTimer(20);
}

MainComponent::~MainComponent()
{
    myo.disconnect();
    
    addAndMakeVisible(myoDataLabel);
    
    myoDataLabel.setFont(Font (16.0f, Font::bold));
    myoDataLabel.setText(String(), sendNotificationSync);
    myoDataLabel.setColour(Label::textColourId, Colours::lightgreen);
}

void MainComponent::paint(Graphics& g)
{
//     g.fillAll(Colours::aquamarine);
    g.drawText("Hey Hey", getLocalBounds(), Justification::centred, true);
    
    if(myoData.size() > 0){
        g.drawText(String(myoData[0].emg.absRaw[0]), getLocalBounds(), Justification::centred, true);
    }
}

void MainComponent::resized()
{
//    Rectangle<int> area = getLocalBounds();
//
//    Rectangle<int> areaDial1 = area.removeFromLeft(area.getWidth() /4);
//    areaDial1.removeFromBottom(area.getHeight()/2);
//    dial1.setBounds(areaDial1);
//
//    //Draw the back end of the reverb.
//    Rectangle<int> areaMyo(area);
//    areaMyo.removeFromBottom(getHeight()/3);
//    areaMyo.reduce(10, 10);
//    myo.setBounds(areaMyo);
//
//    myoDataLabel.setBounds(100, 10, getWidth(), 30);
    
    ui.setBounds(getLocalBounds().reduced (4));
}

void MainComponent::timerCallback(){
    bool getMyoDataSuccessful = false;
    myoData = myo.getMyoData(getMyoDataSuccessful);
    if (!getMyoDataSuccessful)
    {
        return;
    }
    
    std::cout << myoData[0].emg.raw[0] << std::endl;
}
