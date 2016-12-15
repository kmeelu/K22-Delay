/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

void K22delayAudioProcessorEditor::makeSlider(Slider* s, float min, float max, float step, float val, int i)
{
    if (i == 2)
    {
        s->setSliderStyle(Slider::RotaryVerticalDrag);
        s->setColour(Slider::rotarySliderFillColourId, Colour (150, 28, 0));
        s->setColour(Slider::rotarySliderOutlineColourId, Colour (240, 238, 240));
        s->setColour (Slider::textBoxTextColourId, Colour (240,238,240));
    }
    else if (i == 1)
    {
        s->setSliderStyle(Slider::RotaryVerticalDrag);
        s->setColour(Slider::rotarySliderFillColourId, Colour (150, 28, 0));
        s->setColour(Slider::rotarySliderOutlineColourId, Colour (48, 48, 48));
        s->setColour (Slider::textBoxTextColourId, Colour (0xff484848));
    }
    else
    {
        s->setSliderStyle(Slider::LinearVertical);
        s->setColour(Slider::trackColourId, Colour (150, 28, 0));
        s->setColour(Slider::thumbColourId, Colour (48, 48, 48));
        s->setColour (Slider::textBoxTextColourId, Colour (0xff484848));
    }
    
    s->setRange(min, max, step);
    s->setValue(val);
    
    s->setColour (Slider::textBoxBackgroundColourId, Colour (0x00ffffff));
    s->setColour (Slider::textBoxHighlightColourId, Colour (0x001111ee));
    s->setColour (Slider::textBoxOutlineColourId, Colour (0x009e1212));
    s->setTextBoxStyle (Slider::TextBoxBelow, true, 90, 10);
    
    s->addListener(this);
    addAndMakeVisible(s);
}


//==============================================================================
K22delayAudioProcessorEditor::K22delayAudioProcessorEditor (K22delayAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    background = ImageCache::getFromMemory(Background::delayDesigner_png, Background::delayDesigner_pngSize);
    
    setSize (width, height);
    
    makeSlider(&mixWet, 0.0, 1.0, 0.01, 0.5, 0);
    makeSlider(&mixDry, 0.0, 1.0, 0.01, 1.0, 0);
    
    makeSlider(&taps, 0.0, 16.0, 1.0, 1.0, 1);
    makeSlider(&delayLength, 0.0, 2.0, 0.1, 1.0, 1);
    
    makeSlider(&multLin, 0.0, 0.25, 0.01, 0.0, 2);
    makeSlider(&multExp, 0.0, 0.25, 0.001, 0.0, 2);
    makeSlider(&multQuad, 0.0, 0.25, 0.01, 0.0, 2);

    makeSlider(&diffLin, -0.25, 0.25, 0.01, 0.0, 2);
    makeSlider(&diffExp, -0.1, 0.1, 0.001, 0.0, 2);
    makeSlider(&diffQuad, -0.25, 0.25, 0.01, 0.0, 2);
    
}

K22delayAudioProcessorEditor::~K22delayAudioProcessorEditor()
{
}

//==============================================================================
void K22delayAudioProcessorEditor::paint (Graphics& g)
{
    g.drawImage(background, 0, 0, width, height, 0, 0, 2400, 450);
}

void K22delayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    mixWet.setBounds(width - 148, 70, 80, 120);
    mixDry.setBounds(width - 195, 70, 80, 120);
    
    int z = 5;
    int w = 70;
    
    taps.setBounds(250 + z, w, 100, 100);
    delayLength.setBounds(375 - z, w, 100, 100);
    
    int x = -10;
    int y = -5;
    int v = 70;
    int u = 70;
    
    multLin.setBounds(515 + x,v,u,u);
    multExp.setBounds(685 + x,v,u,u);
    multQuad.setBounds(600 + x,v,u,u);
    
    diffLin.setBounds(765 + y,v,u,u);
    diffExp.setBounds(935 + y,v,u,u);
    diffQuad.setBounds(850 + y,v,u,u);
}

void K22delayAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    
    if (slider == &mixWet)
    {
        processor.wetMix = mixWet.getValue();
    }
    else if (slider == &mixDry)
    {
        processor.dryMix = mixDry.getValue();
    }
    else if (slider == &taps)
    {
        processor.numTaps = taps.getValue();
    }
    else if (slider == &delayLength)
    {
        processor.delayInSeconds = delayLength.getValue();
    }
    else if (slider == &multLin)
    {
        processor.multLinear = multLin.getValue();
    }
    else if (slider == &multExp)
    {
        processor.multExponential = multExp.getValue();
    }
    else if (slider == &multQuad)
    {
        processor.multQuadratic = multQuad.getValue();
    }
    else if (slider == &diffLin)
    {
        processor.diffLinear = diffLin.getValue();
    }
    else if (slider == &diffExp)
    {
        processor.diffExponential = diffExp.getValue();
    }
    else if (slider == &diffQuad)
    {
        processor.diffQuadratic = diffQuad.getValue();
    }

}
