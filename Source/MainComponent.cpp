/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);
    
    button.setButtonText("Click me!");
    
    int width = 100;
    int height = 50;
    
    button.setBounds(((getWidth() - width) / 2), (getHeight() - height) / 2, width, height);
    button.setEnabled(true);
    button.addListener(this);
    
    addAndMakeVisible (button);
    
    // specify the number of input and output channels that we want to open
    setAudioChannels (0, 2);
    
    for (auto &osc : oscs){
        osc.setAmplitude(0.3);
        osc.setFrequency(160.0);
        osc.setSampleRate(deviceManager.getCurrentAudioDevice()->getCurrentSampleRate());
    }
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

void MainComponent::buttonStateChanged(Button *button){
    bool isOn = (button->getState() == Button::ButtonState::buttonDown);
    oscs[0].setWaveOn(isOn);
    oscs[1].setWaveOn(isOn);
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    for (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel){
        float * const buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);
        oscs[channel].renderAudio(buffer, bufferToFill.numSamples);
    }
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
