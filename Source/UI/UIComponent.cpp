//
//  GuiCompoent.cpp
//  DaVinciMapper
//
//  Created by Terry Clark on 06/12/2018.
//

#include "UIComponent.hpp"


//-----------------
// Myo Tab
//-----------------

struct MyoTab : public Component
{
    MyoTab()
    {
        auto* myoGroup = addToList(new GroupComponent("group", "Myo Params"));
        myoGroup->setBounds(20, 20, 220, 140);
        
        StringArray buttonName;
        buttonName.add("Search for Myo(s)");
        buttonName.add("Reset Myo(s)");
        
        for (int i = 0 ;i < buttonName.size(); ++i)
        {
            auto* tb = addToList(new TextButton(buttonName[i]));
            tb->setBounds(45, 46 + i * 22, 180, 22);
        }
    }
    
private:
    
    OwnedArray<Component> components;
    std::unique_ptr<BubbleMessageComponent> bubbleMessage;
    
    template <typename ComponentType>
    ComponentType* addToList (ComponentType* newComp)
    {
        components.add (newComp);
        addAndMakeVisible (newComp);
        return newComp;
    }
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyoTab)
};

//-----------------
// DSP Tab
//-----------------

struct DSPTab : public Component
{
    DSPTab()
    {
        auto* DSPGroup = addToList(new GroupComponent("group", "DSP Params"));
        DSPGroup->setBounds(20, 20, 220, 140);
        
        StringArray buttonName;
        buttonName.add("Search for Myo(s)");
        buttonName.add("Reset Myo(s)");
        
        for (int i = 0 ;i < buttonName.size(); ++i)
        {
            auto* tb = addToList(new TextButton(buttonName[i]));
            tb->setBounds(45, 46 + i * 22, 180, 22);
        }
    }
    
private:
    
    OwnedArray<Component> components;
    std::unique_ptr<BubbleMessageComponent> bubbleMessage;
    
    template <typename ComponentType>
    ComponentType* addToList (ComponentType* newComp)
    {
        components.add (newComp);
        addAndMakeVisible (newComp);
        return newComp;
    }
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DSPTab)
};

//-----------------
// Machine Learning Tab
//-----------------

struct MLTab : public Component
{
    MLTab()
    {
        auto* DSPGroup = addToList(new GroupComponent("group", "DSP Params"));
        DSPGroup->setBounds(20, 20, 220, 140);
        
        StringArray buttonName;
        buttonName.add("Search for Myo(s)");
        buttonName.add("Reset Myo(s)");
        
        for (int i = 0 ;i < buttonName.size(); ++i)
        {
            auto* tb = addToList(new TextButton(buttonName[i]));
            tb->setBounds(45, 46 + i * 22, 180, 22);
        }
    }
    
private:
    
    OwnedArray<Component> components;
    std::unique_ptr<BubbleMessageComponent> bubbleMessage;
    
    template <typename ComponentType>
    ComponentType* addToList (ComponentType* newComp)
    {
        components.add (newComp);
        addAndMakeVisible (newComp);
        return newComp;
    }
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MLTab)
};

//-----------------
// Parameter Mapping Tab
//-----------------

struct MappingTab : public Component
{
    MappingTab()
    {
        auto* DSPGroup = addToList(new GroupComponent("group", "Mapping Params"));
        DSPGroup->setBounds(20, 20, 220, 140);
        
        StringArray buttonName;
        buttonName.add("Search for Myo(s)");
        buttonName.add("Reset Myo(s)");
        
        for (int i = 0 ;i < buttonName.size(); ++i)
        {
            auto* tb = addToList(new TextButton(buttonName[i]));
            tb->setBounds(45, 46 + i * 22, 180, 22);
        }
    }
    
private:
    
    OwnedArray<Component> components;
    std::unique_ptr<BubbleMessageComponent> bubbleMessage;
    
    template <typename ComponentType>
    ComponentType* addToList (ComponentType* newComp)
    {
        components.add (newComp);
        addAndMakeVisible (newComp);
        return newComp;
    }
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MappingTab)
};

//----------------
// Collection of All Tabs
//----------------

UIComponent::UIComponent()
:
TabbedComponent(TabbedButtonBar::TabsAtTop)
{
    auto colour = findColour (ResizableWindow::backgroundColourId);
    
    addTab("Input Setup", colour, new MyoTab( ), true);
    addTab("DSP", colour, new DSPTab(), true);
    addTab("ML", colour, new MLTab(), true);
    addTab("Output Mapping", colour, new MappingTab(), true);
}



