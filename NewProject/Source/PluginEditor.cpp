#include "PluginProcessor.h"
#include "PluginEditor.h"

NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // --- DRIVE ---
    driveSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    driveSlider.setRange(1.0, 50.0, 0.1);
    driveSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(driveSlider);
    
    driveLabel.setText("Drive", juce::dontSendNotification);
    driveLabel.attachToComponent(&driveSlider, false);
    driveLabel.setJustificationType(juce::Justification::centred);

    // --- TONE ---
    toneSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    toneSlider.setRange(400.0, 15000.0, 1.0); 
    toneSlider.setSkewFactorFromMidPoint(2000.0); 
    toneSlider.setValue(2000.0);
    toneSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(toneSlider);

    toneLabel.setText("Tone", juce::dontSendNotification);
    toneLabel.attachToComponent(&toneSlider, false);
    toneLabel.setJustificationType(juce::Justification::centred);

    // --- VOLUME ---
    volumeSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    volumeSlider.setRange(0.0, 1.0, 0.01); 
    volumeSlider.setValue(0.5); 
    volumeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(volumeSlider);

    volumeLabel.setText("Volume", juce::dontSendNotification);
    volumeLabel.attachToComponent(&volumeSlider, false);
    volumeLabel.setJustificationType(juce::Justification::centred);

    // --- LIAISONS ---
    volumeSlider.onValueChange = [this] { audioProcessor.setVolume(volumeSlider.getValue()); };
    toneSlider.onValueChange = [this] { audioProcessor.setTone(toneSlider.getValue()); };
    driveSlider.onValueChange = [this] { audioProcessor.setDrive(driveSlider.getValue()); };

    setSize (500, 300);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor() {}

void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // Fond vert type "Tube Screamer"
    g.fillAll (juce::Colour::fromFloatRGBA (0.15f, 0.45f, 0.15f, 1.0f)); 

    g.setColour (juce::Colours::white);
    g.setFont (24.0f);
    g.drawFittedText ("MY OVERDRIVE", getLocalBounds().removeFromTop(50), juce::Justification::centred, 1);
}

void NewProjectAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced(20);
    area.removeFromTop(40); // On laisse de la place pour le titre
    
    int sliderWidth = area.getWidth() / 3;

    // On distribue proprement l'espace
    driveSlider.setBounds(area.removeFromLeft(sliderWidth).withSizeKeepingCentre(sliderWidth, 180));
    toneSlider.setBounds(area.removeFromLeft(sliderWidth).withSizeKeepingCentre(sliderWidth, 180));
    volumeSlider.setBounds(area.removeFromLeft(sliderWidth).withSizeKeepingCentre(sliderWidth, 180));
}