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

#include <ui/panels/SettingsPanel.h>
#include <common/Settings.h>

//==============================================================================

namespace mbctrl {
namespace ui {

//==============================================================================

SettingsPanel::SettingsPanel (controller::MidiController& midiController)
    : mMidiController (midiController)
    , mMidiDeviceRefresh ("midi-device-refresh", juce::DrawableButton::ButtonStyle::ImageStretched)
{
    const auto useExternalMidi = mMidiController.getUseExternalMidi();

    mUseExternalMidi.onClick = [this] { updateUseExternalMidi(); };
    mUseExternalMidi.setClickingTogglesState (true);
    mUseExternalMidi.setButtonText ("External MIDI");
    mUseExternalMidi.setToggleState (
        useExternalMidi,
        juce::NotificationType::dontSendNotification
    );
    addAndMakeVisible (mUseExternalMidi);

    mMidiDeviceLabel.setText (
        "Device",
        juce::NotificationType::dontSendNotification
    );
    addAndMakeVisible (mMidiDeviceLabel);

    mMidiDeviceSelector.onChange = [this]
    {
        mMidiController.selectMidiOutputDevice (
            mMidiDeviceSelector.getSelectedItemIndex()
        );
    };
    addAndMakeVisible (mMidiDeviceSelector);

    {
        int syncArrowSvgSize = 0;
        const auto syncArrowSvg = AssetsData::getNamedResource (
            "syncarrow_svg",
            syncArrowSvgSize
        );

        std::unique_ptr<juce::Drawable> syncArrowImage (
            juce::Drawable::createFromImageData (
                syncArrowSvg,
                syncArrowSvgSize
            )
        );

        mMidiDeviceRefresh.setImages (syncArrowImage.get());
        mMidiDeviceRefresh.setButtonStyle (juce::DrawableButton::ButtonStyle::ImageOnButtonBackground);
    }
    mMidiDeviceRefresh.onClick = [this] { updateMidiDevices(); };
    addAndMakeVisible (mMidiDeviceRefresh);

    mMidiChannelLabel.setText (
        "Channel",
        juce::NotificationType::dontSendNotification
    );
    addAndMakeVisible (mMidiChannelLabel);

    mMidiChannelSelector.onChange = [this]
    {
        mMidiController.setMidiChannel (
            mMidiChannelSelector.getSelectedId()
        );
    };

    {
        const auto midiChannelRange = juce::Range<int> (1, 16);
        const auto midiChannelValue = mMidiController.getMidiChannel();
        for (
            float i = midiChannelRange.getStart();
            i <= midiChannelRange.getEnd();
            ++i
        )
        {
            mMidiChannelSelector.addItem (juce::String (i), i);
        }
        mMidiChannelSelector.setSelectedId (midiChannelValue);
    }
    addAndMakeVisible (mMidiChannelSelector);

    updateUseExternalMidi();
    updateMidiDevices();
}

SettingsPanel::~SettingsPanel()
{

}

//==============================================================================

void SettingsPanel::resized()
{
    static const auto sHeight                   = 20;
    static const auto sHorizontalMargin         = 10;
    static const auto sVerticalMargin           = 15;
    static const auto sUseMidiExternalWidth     = 80;
    static const auto sMidiChannelSelectorWidth = 60;

    const auto bounds                   = getLocalBounds();
    const auto midiDeviceLabelWidth     = mMidiDeviceLabel.getFont().getStringWidth (mMidiDeviceLabel.getText());
    const auto midiChannelLabelWidth    = mMidiChannelLabel.getFont().getStringWidth (mMidiChannelLabel.getText());
    const auto midiDeviceSelectorWidth  = (
        bounds.getWidth()
        - sHorizontalMargin * 7
        - sUseMidiExternalWidth
        - midiDeviceLabelWidth
        - sHeight
        - midiChannelLabelWidth
        - sMidiChannelSelectorWidth
    );

    mUseExternalMidi.setBounds (
        sHorizontalMargin,
        sVerticalMargin,
        sUseMidiExternalWidth,
        sHeight
    );

    mMidiDeviceLabel.setBounds (
        mUseExternalMidi.getRight() + sHorizontalMargin,
        mUseExternalMidi.getY(),
        midiDeviceLabelWidth,
        sHeight
    );

    mMidiDeviceSelector.setBounds (
        mMidiDeviceLabel.getRight() + sHorizontalMargin,
        mMidiDeviceLabel.getY(),
        midiDeviceSelectorWidth,
        sHeight
    );

    mMidiDeviceRefresh.setBounds (
        mMidiDeviceSelector.getRight() + (sHorizontalMargin / 2),
        mMidiDeviceSelector.getY(),
        sHeight,
        sHeight
    );

    mMidiChannelLabel.setBounds (
        mMidiDeviceRefresh.getRight() + sHorizontalMargin,
        mMidiDeviceRefresh.getY(),
        midiChannelLabelWidth,
        sHeight
    );

    mMidiChannelSelector.setBounds (
        mMidiChannelLabel.getRight() + sHorizontalMargin,
        mMidiChannelLabel.getY(),
        sMidiChannelSelectorWidth,
        sHeight
    );
}

void SettingsPanel::paint (juce::Graphics& g)
{
    const auto bounds = getLocalBounds();

    g.setColour (juce::Colours::white);
    g.drawLine (
        bounds.getX(),
        bounds.getY(),
        bounds.getRight(),
        bounds.getY(),
        2
    );
}

//==============================================================================

void SettingsPanel::updateUseExternalMidi()
{
    const auto toggled = mUseExternalMidi.getToggleState();

    mMidiController.setUseExternalMidi (toggled);
    mMidiDeviceLabel.setEnabled (toggled);
    mMidiDeviceSelector.setEnabled (toggled);
    mMidiChannelLabel.setEnabled (toggled);
    mMidiChannelSelector.setEnabled (toggled);
}

void SettingsPanel::updateMidiDevices()
{
    mMidiController.updateMidiOutputDevices();
    mMidiDeviceSelector.clear();

    const auto selectedMidiDevice = mMidiController.getSelectedMidiOutputDevice();
    auto midiDeviceId = 1;
    for (auto d : mMidiController.getMidiOutputDevices())
    {
        mMidiDeviceSelector.addItem (d, midiDeviceId);
        if (d == selectedMidiDevice)
        {
            mMidiDeviceSelector.setSelectedId (midiDeviceId);
        }
        ++midiDeviceId;
    }
}

//==============================================================================

} // namespace ui
} // namespace mbctrl
