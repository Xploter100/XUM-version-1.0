#include "PluginEditor.h"

XumEditor::XumEditor (XumAudioProcessor& p)
    : AudioProcessorEditor (&p), proc (p), scope (p.scope),
      keyboard (p.keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{
    setLookAndFeel (&laf);
    using namespace xum::Theme;

    addAndMakeVisible (scope);

    keyboard.setAvailableRange (36, 96);
    keyboard.setLowestVisibleKey (36);
    keyboard.setColour (juce::MidiKeyboardComponent::whiteNoteColourId, juce::Colour (0xff10131c));
    keyboard.setColour (juce::MidiKeyboardComponent::blackNoteColourId, juce::Colour (0xff040508));
    keyboard.setColour (juce::MidiKeyboardComponent::keySeparatorLineColourId, line);
    keyboard.setColour (juce::MidiKeyboardComponent::mouseOverKeyOverlayColourId, accent.withAlpha (0.15f));
    keyboard.setColour (juce::MidiKeyboardComponent::keyDownOverlayColourId, accent.withAlpha (0.55f));
    keyboard.setColour (juce::MidiKeyboardComponent::textLabelColourId, juce::Colours::transparentBlack);
    addAndMakeVisible (keyboard);

    addCombo (oscType,    oscTypeAtt,    "osc1_type");
    addCombo (filterType, filterTypeAtt, "f1_type");

    addKnob (knobs[0], "osc1_pos",    "WT POS");
    addKnob (knobs[1], "osc1_warp1",  "WARP 1");
    addKnob (knobs[2], "osc1_warp2",  "WARP 2");
    addKnob (knobs[3], "f1_cutoff",   "CUTOFF");
    addKnob (knobs[4], "f1_res",      "RES");
    addKnob (knobs[5], "env1_a",      "ATK");
    addKnob (knobs[6], "env1_d",      "DEC");
    addKnob (knobs[7], "env1_s",      "SUS");
    addKnob (knobs[8], "env1_r",      "REL");
    addKnob (knobs[9], "master_gain", "MASTER");

    setSize (880, 600);
}

XumEditor::~XumEditor() { setLookAndFeel (nullptr); }

void XumEditor::addKnob (Knob& k, const juce::String& id, const juce::String& text)
{
    k.slider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    k.slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 64, 16);
    k.label.setText (text, juce::dontSendNotification);
    k.label.setJustificationType (juce::Justification::centred);
    k.label.setFont (juce::Font (juce::FontOptions (11.f)));
    addAndMakeVisible (k.slider);
    addAndMakeVisible (k.label);
    k.att = std::make_unique<SliderAtt> (proc.apvts, id, k.slider);
}

void XumEditor::addCombo (juce::ComboBox& box, std::unique_ptr<ComboAtt>& att, const juce::String& id)
{
    if (auto* choice = dynamic_cast<juce::AudioParameterChoice*> (proc.apvts.getParameter (id)))
        box.addItemList (choice->choices, 1);
    addAndMakeVisible (box);
    att = std::make_unique<ComboAtt> (proc.apvts, id, box);
}

void XumEditor::paint (juce::Graphics& g)
{
    using namespace xum::Theme;
    g.fillAll (bg);

    g.setColour (accent);
    g.setFont (juce::Font (juce::FontOptions (26.f, juce::Font::bold)));
    g.drawText ("X  U  M", 24, 12, 200, 32, juce::Justification::centredLeft);

    g.setColour (text);
    g.setFont (juce::Font (juce::FontOptions (11.f)));
    g.drawText ("HYBRID SYNTHESIZER", getWidth() - 224, 12, 200, 32, juce::Justification::centredRight);

    g.setColour (line);
    g.drawHorizontalLine (48, 20.f, (float) getWidth() - 20.f);
}

void XumEditor::resized()
{
    auto area = getLocalBounds().reduced (20);
    area.removeFromTop (36);
    keyboard.setBounds (area.removeFromBottom (84));
    area.removeFromBottom (10);
    auto knobRow = area.removeFromBottom (110);
    area.removeFromBottom (8);
    auto comboRow = area.removeFromBottom (28);
    area.removeFromBottom (8);
    scope.setBounds (area);

    keyboard.setKeyWidth ((float) keyboard.getWidth() / 36.f);

    oscType.setBounds (comboRow.removeFromLeft (170));
    comboRow.removeFromLeft (10);
    filterType.setBounds (comboRow.removeFromLeft (170));

    const int kw = knobRow.getWidth() / (int) knobs.size();
    for (auto& k : knobs)
    {
        auto cell = knobRow.removeFromLeft (kw);
        k.label.setBounds (cell.removeFromTop (14));
        k.slider.setBounds (cell);
    }
}
