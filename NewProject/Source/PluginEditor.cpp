/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
// --- Configuration du Slider de DRIVE ---
    driveSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    driveSlider.setRange(1.0, 50.0, 0.1);
    driveSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(driveSlider);
    
    driveLabel.setText("Gain / Drive", juce::dontSendNotification);
    driveLabel.attachToComponent(&driveSlider, false);
    driveLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(driveLabel);

    // --- Configuration du Slider de VOLUME ---
    volumeSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    volumeSlider.setRange(0.0, 1.0, 0.01); // Le volume va souvent de 0 à 1 (ou 0 à 1.5)
    volumeSlider.setValue(0.5); // Valeur par défaut à 50%
    volumeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(volumeSlider);

    volumeLabel.setText("Output Vol", juce::dontSendNotification);
    volumeLabel.attachToComponent(&volumeSlider, false);
    volumeLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(volumeLabel);

    // Liaison avec le processeur (méthode simple par Lambda)
    volumeSlider.onValueChange = [this] { 
        audioProcessor.setVolume(volumeSlider.getValue()); 
    };
    
    driveSlider.onValueChange = [this] {
        audioProcessor.setDrive(driveSlider.getValue());
    };

    setSize (500, 300);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void NewProjectAudioProcessorEditor::resized()
{
    
// On définit une zone pour nos boutons
    auto area = getLocalBounds().reduced(20);
    auto sliderWidth = 120;
    auto sliderHeight = 150;

    // Placement du Drive à gauche
    driveSlider.setBounds(area.removeFromLeft(sliderWidth).withSizeKeepingCentre(sliderWidth, sliderHeight));
    
    // Un peu d'espace entre les deux
    area.removeFromLeft(40); 
    
    // Placement du Volume à côté
    volumeSlider.setBounds(area.removeFromLeft(sliderWidth).withSizeKeepingCentre(sliderWidth, sliderHeight));

}
