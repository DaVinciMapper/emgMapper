#pragma once

#include "./Input/Myo/MyoComponent.hpp"
//#include "./ DSP/DSP.hpp"
#include "./UI/UIComponent.hpp"


class MyLookAndFeel : public LookAndFeel_V4
{
public:
    MyLookAndFeel(){
        setColour(Slider::rotarySliderOutlineColourId, Colours::grey);
        setColour(Slider::thumbColourId, Colours::red);
    };
};

class MainComponent : public Component,
                      public Slider::Listener,
                      public Timer
{
public:
    MainComponent();
    ~MainComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(Slider* slider) override
    {
        dial1.setValue(myoData[0].emg.absRaw[0]);
    }
    
    void timerCallback() override;
    
    UIComponent ui;
    MyoComponent myo;
    
    Label myoDataLabel;
    Slider dial1;
    LookAndFeel_V4 *lafv4Midnight;
private:
    
    std::vector<MyoData> myoData;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
