#pragma once
#include "PluginProcessor.h"
#include "UI/Oscilloscope.h"
#include <array>

class XumLookAndFeel : public juce::LookAndFeel_V4
{
public:
    XumLookAndFeel()
    {
        using namespace xum::Theme;
        setColour (juce::Slider::rotarySliderFillColourId, accent);
        setColour (juce::Slider::rotarySliderOutlineColourId, line);
        setColour (juce::Slider::thumbColourId, accent);
        setColour (juce::Slider::textBoxTextColourId, text);
        setColour (juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
        setColour (juce::Label::textColourId, text);
        setColour (juce::ComboBox::backgroundColourId, panel);
        setColour (juce::ComboBox::outlineColourId, line);
        setColour (juce::ComboBox::textColourId, accent);
        setColour (juce::ComboBox::arrowColourId, accent);
        setColour (juce::PopupMenu::backgroundColourId, panel);
        setColour (juce::PopupMenu::textColourId, text);
        setColour (juce::PopupMenu::highlightedBackgroundColourId, line);
        setColour (juce::PopupMenu::highlightedTextColourId, accent);
    }
};

class XumEditor : public juce::AudioProcessorEditor
{
public:
    explicit XumEditor (XumAudioProcessor&);
    ~XumEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    using SliderAtt = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ComboAtt  = juce::AudioProcessorValueTreeState::ComboBoxAttachment;

    struct Knob
    {
        juce::Slider slider;
        juce::Label label;
        std::unique_ptr<SliderAtt> att;
    };

    void addKnob (Knob&, const juce::String& paramId, const juce::String& text);
    void addCombo (juce::ComboBox&, std::unique_ptr<ComboAtt>&, const juce::String& paramId);

    XumAudioProcessor& proc;
    XumLookAndFeel laf;
    xum::Oscilloscope scope;
    juce::MidiKeyboardComponent keyboard;
    std::array<Knob, 10> knobs;
    juce::ComboBox oscType, filterType;
    std::unique_ptr<ComboAtt> oscTypeAtt, filterTypeAtt;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (XumEditor)
};
