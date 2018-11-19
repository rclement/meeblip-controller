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

#include <ui/components/ControlList.h>

//==============================================================================

namespace mbctrl {
namespace ui {

//==============================================================================

ControlList::ControlList (grape::parameters::ParameterManager& parameters,
                          common::ParameterId parameterId,
                          const juce::String& label)
    : mParameters (parameters)
    , mParameterId (parameterId)
{
    const auto param = common::sParameters.at (mParameterId);

    const auto paramValue = *mParameters.getRawParameterValue (param.id);
    auto itemId = 1;
    for (
        float i = param.valueRange.start;
        i <= param.valueRange.end;
        i += param.valueRange.interval
    )
    {
        mComboBox.addItem (
            param.valueToTextFunction (i),
            itemId
        );

        if (i == paramValue)
        {
            mComboBox.setSelectedItemIndex (itemId);
        }

        ++itemId;
    }
    addAndMakeVisible (mComboBox);

    mComboBoxAttachment.reset (
        new ComboBoxAttachment (mParameters, param.id, mComboBox)
    );

    mLabel.setFont (juce::Font (10));
    mLabel.setJustificationType (juce::Justification::centred);
    mLabel.setText (
        label == juce::String() ? param.name.toUpperCase() : label,
        juce::NotificationType::dontSendNotification
    );
    addAndMakeVisible (mLabel);
}

ControlList::~ControlList()
{

}

//==============================================================================

void ControlList::resized()
{
    static const auto sComboBoxHeight   = 20;
    static const auto sTextBoxHeight    = 20;

    const auto bounds = getLocalBounds();

    mComboBox.setBounds (
        bounds.getX(),
        bounds.getCentreY() - (sComboBoxHeight / 2),
        bounds.getWidth(),
        sComboBoxHeight
    );

    mLabel.setBounds (
        mComboBox.getX(),
        bounds.getBottom() - sTextBoxHeight,
        mComboBox.getWidth(),
        sTextBoxHeight
    );
}

//==============================================================================

} // namespace ui
} // namespace mbctrl
