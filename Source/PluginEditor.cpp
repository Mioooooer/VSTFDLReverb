/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FDLReverbAudioProcessorEditor::FDLReverbAudioProcessorEditor (FDLReverbAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p), valueTreeState(vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (200, 200);
    mixSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    //mixSlider.setRange(0.0, 1.0, 0.01);
    addAndMakeVisible (&mixSlider);
    mixAttachment.reset(new SliderAttachment(valueTreeState, "mix", mixSlider));

    mixLabel.setText("Mix", juce::dontSendNotification);
    mixLabel.attachToComponent(&mixSlider, false);
    mixLabel.setFont(juce::Font (11.0f));
    
}

FDLReverbAudioProcessorEditor::~FDLReverbAudioProcessorEditor()
{
}

//==============================================================================


void FDLReverbAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("This is Emothion Renderer:)", getLocalBounds(), juce::Justification::centred, 1);
}

void FDLReverbAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    mixSlider.setBounds(20, 20, 150, 40);
}
