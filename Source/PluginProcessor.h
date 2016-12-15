/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/**
*/
class K22delayAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    K22delayAudioProcessor();
    ~K22delayAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    // parameters to accept from editor
    float dryMix, wetMix;
    int numTaps;
    float delayInSeconds, old = 1.0;
    float multLinear, multQuadratic, multExponential;
    float diffLinear, diffQuadratic, diffExponential;
    
private:
    // Ring buffer for delay
    AudioSampleBuffer delayStore;
    
    // pointers in the buffer to write in dry mix and read out wet mix
    int writePointer;
    int readPointer;
    
    //int oldTaps, oldDelayInSeconds;
    
    // stores length of delayStore buffer (for now, will be 10s)
    int delayStoreLength;
    
    double rate;
    int samplesPerBlock;
    
    // AudioPlayHead gives us info about the environment outside of plugin
    AudioPlayHead* aph;
    AudioPlayHead::CurrentPositionInfo positionInfo;
    
    double bpm = 60.0;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (K22delayAudioProcessor)
    
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
