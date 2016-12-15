/*
 ==============================================================================
 
 K-22 DELAY by K Meelu
 
 About: The K-22 Delay plugin allows an alternative approach to creating tap
 and multi-tap delays in your preferred DAW. It serves as a ring buffer, where
 number of taps and delay can be output
 
 Note: This serves as the final project for MUSI 325 (Fundamentals of Music Technology).
 For more information, please contact me (author) at kshitijh.meelu@yale.edu.
 
 ==============================================================================
 */
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <math.h>


//==============================================================================
K22delayAudioProcessor::K22delayAudioProcessor() : delayStore(2,1),
#ifndef JucePlugin_PreferredChannelConfigurations
    AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    writePointer = 0;
//    readPointers.add(0);
    
    delayStoreLength = 44100 * 10;
    
    dryMix = 1.0;
    wetMix = 0.5;
}

K22delayAudioProcessor::~K22delayAudioProcessor()
{
}

//==============================================================================
const String K22delayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool K22delayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool K22delayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double K22delayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int K22delayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int K22delayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void K22delayAudioProcessor::setCurrentProgram (int index)
{
}

const String K22delayAudioProcessor::getProgramName (int index)
{
    return String();
}

void K22delayAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void K22delayAudioProcessor::prepareToPlay (double _sampleRate, int _samplesPerBlock)
{
    // initialize all variables
    rate = _sampleRate;
    samplesPerBlock = _samplesPerBlock;
    
    delayStoreLength = (int) rate * 32;
    
    delayStore.setSize(2, delayStoreLength);
    delayStore.clear();
    
    numTaps = 1;
    delayInSeconds = 1.0;
    
    multLinear = 0.0;
    multQuadratic = 0.0;
    multExponential = 0.0;
    
    diffLinear = 0.0;
    diffQuadratic = 0.0;
    diffExponential = 0.0;
    
    // initial bpm is bpm throughout
    aph = getPlayHead();
    aph->getCurrentPosition(positionInfo);
    
    bpm = positionInfo.bpm;
}

void K22delayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool K22delayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

/*
int getIndex(int writeHead, int delay, int bufferLength, int n)
{
    return ((writeHead - delay * (n+1)) % bufferLength + bufferLength) % bufferLength;
}
*/
 
void K22delayAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int numSamples = buffer.getNumSamples();
    
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    int writeHead, index;
    
    // clear any output channels that didn't contain input data
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    // delay processing here
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);
        float* delayData = delayStore.getWritePointer(jmin(channel, delayStore.getNumChannels() - 1));
        
        writeHead = writePointer;
        
        // loop through all samples in the block
        for (int i = 0; i < numSamples; ++i)
        {
            // sample value in
            const float in = channelData[i];
            
            float out = 0.0;
            float tapMix = 1.0;
            
            index = writeHead;
            
            // iterate through taps and add them to the sample value out
            for (int j = 0; j < numTaps; ++j)
            {
                float t = 1.0 - (multLinear * j) - (multQuadratic * j * j) - multExponential * pow(2.0, j);
                tapMix = jmin(1.0f, jmax(0.0f, t));
                
                index = (int)((int)(index - (delayInSeconds + (diffLinear * j) + (diffQuadratic * j * j) + (diffExponential * pow(2.0, j))) * rate) % delayStoreLength + delayStoreLength) % delayStoreLength;

                out += delayData[index] * tapMix;
                //out += delayData[getIndex(writeHead, (int) delayInSeconds * rate, delayStoreLength, j)];
            }
            
            // write sample out & assign next ring buffer value
            channelData[i] = out * wetMix + in * dryMix;
            delayData[writeHead] = in;
            
            // iterate writeHead through ring buffer
            ++writeHead %= delayStoreLength;
        }
    }
    
    writePointer = writeHead;
}
        
        //==============================================================================
bool K22delayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* K22delayAudioProcessor::createEditor()
{
    return new K22delayAudioProcessorEditor (*this);
}

//==============================================================================
void K22delayAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void K22delayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new K22delayAudioProcessor();
}
