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

#include <ui/components/ControlToggle.h>

//==============================================================================

namespace mbctrl {
namespace ui {

//==============================================================================

ControlToggle::ControlToggle (grape::parameters::ParameterManager& parameters,
                              common::ParameterId parameterId,
                              const juce::String& label)
    : mParameters (parameters)
    , mParameterId (parameterId)
{
    const auto param = common::sParameters.at (mParameterId);

    addAndMakeVisible (mToggle);

    mButtonAttachment.reset (
        new ButtonAttachment (mParameters, param.id, mToggle)
    );

    mLabel.setFont (juce::Font (10));
    mLabel.setJustificationType (juce::Justification::centred);
    mLabel.setText (
        label == juce::String() ? param.name.toUpperCase() : label,
        juce::NotificationType::dontSendNotification
    );
    addAndMakeVisible (mLabel);
}

ControlToggle::~ControlToggle()
{

}

//==============================================================================

void ControlToggle::resized()
{
    static const auto sTextBoxHeight = 20;

    const auto bounds = getLocalBounds();

    mToggle.setBounds (
        bounds.getX(),
        bounds.getY(),
        bounds.getWidth(),
        bounds.getHeight() - sTextBoxHeight
    );

    mLabel.setBounds (
        mToggle.getX(),
        mToggle.getBottom(),
        mToggle.getWidth(),
        sTextBoxHeight
    );
}

//==============================================================================

} // namespace mbctrl
} // namespace ui

