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

#include <ui/components/AboutDialog.h>
#include <ui/CustomLookAndFeel.h>

//==============================================================================

namespace mbctrl {
namespace ui {

//==============================================================================

AboutDialog::AboutDialog()
    : mPluginWebsite (juce::String (JucePlugin_ManufacturerWebsite),
                      juce::URL (JucePlugin_ManufacturerWebsite))
{
    const auto& montserratExtraLightTf = CustomLookAndFeel::sTypefaces.at (
        CustomLookAndFeel::TypefaceId::typefaceMontserratExtraLight
    );

    const auto& montserratRegularTf = CustomLookAndFeel::sTypefaces.at (
        CustomLookAndFeel::TypefaceId::typefaceMontserratRegular
    );

    mPluginName.setText (
        juce::String (JucePlugin_Name),
        juce::NotificationType::dontSendNotification
    );
    mPluginName.setJustificationType (juce::Justification::centred);
    mPluginName.setFont (juce::Font (montserratRegularTf.mPtr).withHeight (20));
    addAndMakeVisible (mPluginName);

    mPluginVersion.setText (
        juce::String ("Version")
            + " " + juce::String (JucePlugin_VersionString)
            + " ("
            + (juce::SystemStats::isOperatingSystem64Bit() ? "64-bit" : "32-bit")
            + ")",
        juce::NotificationType::dontSendNotification
    );
    mPluginVersion.setJustificationType (juce::Justification::centred);
    mPluginVersion.setFont (juce::Font (montserratExtraLightTf.mPtr).withHeight (12));
    addAndMakeVisible (mPluginVersion);

    mPluginDescription.setText (
        juce::String (JucePlugin_Desc),
        juce::NotificationType::dontSendNotification
    );
    mPluginDescription.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (mPluginDescription);

    mPluginCredits.setText (
        juce::String ("Developed by ") + juce::String (JucePlugin_Manufacturer),
        juce::NotificationType::dontSendNotification
    );
    mPluginCredits.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (mPluginCredits);

    mPluginCopyright.setText (
        juce::String ("Copyright (c) 2018 - ")
            + juce::String (juce::Time::getCurrentTime().getYear())
            + " " + juce::String (JucePlugin_Manufacturer),
        juce::NotificationType::dontSendNotification
    );
    mPluginCopyright.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (mPluginCopyright);

    mPluginLicense.setText (
        "Open-source software licensed under GPLv3",
        juce::NotificationType::dontSendNotification
    );
    mPluginLicense.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (mPluginLicense);

    mPluginWebsite.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (mPluginWebsite);
}

AboutDialog::~AboutDialog()
{

}

//==============================================================================

void AboutDialog::resized()
{
    static const auto sMargin       = 10;
    static const auto sTextHeight   = 20;

    const auto textWidth = getWidth() - sMargin * 2;

    mPluginName.setBounds (sMargin, sMargin, textWidth, sTextHeight);

    mPluginVersion.setBounds (
        mPluginName.getX(),
        mPluginName.getBottom(),
        textWidth,
        sTextHeight
    );

    mPluginDescription.setBounds (
        mPluginVersion.getX(),
        mPluginVersion.getBottom() + sMargin,
        textWidth,
        sTextHeight
    );

    mPluginCredits.setBounds (
        mPluginDescription.getX(),
        mPluginDescription.getBottom() + sMargin,
        textWidth,
        sTextHeight
    );

    mPluginCopyright.setBounds (
        mPluginCredits.getX(),
        mPluginCredits.getBottom(),
        textWidth,
        sTextHeight
    );

    mPluginLicense.setBounds (
        mPluginCopyright.getX(),
        mPluginCopyright.getBottom() + sMargin,
        textWidth,
        sTextHeight
    );

    mPluginWebsite.setBounds (
        mPluginLicense.getX(),
        mPluginLicense.getBottom(),
        textWidth,
        sTextHeight
    );
}

void AboutDialog::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

//==============================================================================

} // namespace ui
} // namespace mbctrl
