/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Background.h"


//==============================================================================
/**
*/
class K22delayAudioProcessorEditor  :   public AudioProcessorEditor,
                                        private Slider::Listener
{
public:
    void makeSlider(Slider* s, float min, float max, float step, float val, int i);
    
    K22delayAudioProcessorEditor (K22delayAudioProcessor&);
    ~K22delayAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    K22delayAudioProcessor& processor;
    
    Image background;
    
    void sliderValueChanged(Slider* slider) override;

    Slider mixWet, mixDry;
    Slider taps, delayLength;
    
    Slider multLin, multExp, multQuad;
    Slider diffLin, diffExp, diffQuad;
    
    
    double mult = 1.5;
    int width = (int) 800*mult;
    int height = (int) 150*mult;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (K22delayAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
