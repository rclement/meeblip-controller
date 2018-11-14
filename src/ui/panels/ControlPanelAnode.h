/*
    Meeblip Controller - MIDI controller for the Meeblip Anode synthesizer
    Copyright (c) 2018 Romain Clement

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

//==============================================================================

#pragma once

#include <controller/MidiController.h>
#include <ui/components/ControlKnob.h>
#include <ui/components/ControlList.h>
#include <ui/components/ControlToggle.h>
#include <JuceHeader.h>
#include <grape/parameters/ParameterManager.h>

//==============================================================================

namespace mbctrl {
namespace ui {

//==============================================================================

class ControlPanelAnode : public juce::Component
{
public:
    ControlPanelAnode (grape::parameters::ParameterManager&,
                       controller::MidiController&);
    ~ControlPanelAnode();

public: // juce::Component
    void resized() override;
    void paint (juce::Graphics&) override;

private:
    controller::MidiController& mMidiController;

    juce::DrawableImage     mMeeblipLogo;
    juce::DrawableImage     mAnodeLogo;
    juce::TextButton        mSync;

    juce::GroupComponent    mEnvelopeGroup;
    ui::ControlKnob         mEnvelopeAttack;
    ui::ControlKnob         mEnvelopeDecay;
    ui::ControlToggle       mEnvelopeSustain;

    juce::GroupComponent    mFilterGroup;
    ui::ControlKnob         mFilterCutoff;

    juce::GroupComponent    mOscillatorsGroup;
    ui::ControlKnob         mOscillatorPulseWidth;
    ui::ControlKnob         mOscillatorDetune;
    ui::ControlToggle       mOscillatorBOctave;
    ui::ControlToggle       mPwmSweep;

    juce::GroupComponent    mLfoGroup;
    ui::ControlKnob         mLfoRate;
    ui::ControlKnob         mLfoDepth;
    ui::ControlToggle       mLfoDestination;

    juce::GroupComponent    mMidiOnlyGroup;
    ui::ControlKnob         mPortamento;
    ui::ControlKnob         mVcfEnvelopeAmount;
    ui::ControlToggle       mLfoRandom;
    ui::ControlToggle       mLfoNoteRetrigger;
    ui::ControlList         mOscillatorBWave;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlPanelAnode)
};

//==============================================================================

} // namespace ui
} // namespace mbctrl

