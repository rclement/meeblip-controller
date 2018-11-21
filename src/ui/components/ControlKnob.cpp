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

#include <ui/components/ControlKnob.h>

//==============================================================================

namespace mbctrl {
namespace ui {

//==============================================================================

ControlKnob::ControlKnob (grape::parameters::ParameterManager& parameterManager,
                          common::ParameterId parameterId,
                          const juce::String& label)
    : mParameterManager (parameterManager)
    , mParameterId (parameterId)
{
    const auto param = common::sParameters.at (mParameterId);
    const auto range = param.valueRange.getRange();

    mSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mSlider.setRange (range.getStart(), range.getEnd(), 0);
    mSlider.setPopupDisplayEnabled (false, false, nullptr);
    addAndMakeVisible (mSlider);

    mSliderAttachment.reset (
        new SliderAttachment (mParameterManager, param.id, mSlider)
    );

    mLabel.setFont (juce::Font (10));
    mLabel.setJustificationType (juce::Justification::centred);
    mLabel.setText (
        label == juce::String() ? param.name.toUpperCase() : label,
        juce::NotificationType::dontSendNotification
    );
    addAndMakeVisible (mLabel);
}

ControlKnob::~ControlKnob()
{

}

//==============================================================================

void ControlKnob::resized()
{
    static const auto sLabelHeight = 20;

    const auto bounds = getLocalBounds();

    mSlider.setBounds (
        bounds.getX(),
        bounds.getY(),
        bounds.getWidth(),
        bounds.getHeight() - sLabelHeight
    );

    mSlider.setTextBoxStyle (
        juce::Slider::TextEntryBoxPosition::NoTextBox,
        false,
        mSlider.getWidth(),
        sLabelHeight
    );

    mLabel.setBounds (
        mSlider.getX(),
        mSlider.getBottom(),
        mSlider.getWidth(),
        sLabelHeight
    );
}

//==============================================================================

} // namespace ui
} // namespace mbctrl
