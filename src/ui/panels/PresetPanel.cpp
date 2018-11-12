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

#include <ui/panels/PresetPanel.h>
#include <ui/CustomLookAndFeel.h>
#include <map>

//==============================================================================

namespace mbctrl {
namespace ui {

//==============================================================================

PresetPanel::PresetPanel (grape::presets::PresetManager& presetManager)
    : mPresetBar (presetManager)
{
    const auto& montserratExtraLightTf = CustomLookAndFeel::sTypefaces.at (
        CustomLookAndFeel::TypefaceId::typefaceMontserratExtraLight
    );

    const auto& montserratRegularTf = CustomLookAndFeel::sTypefaces.at (
        CustomLookAndFeel::TypefaceId::typefaceMontserratRegular
    );

    mTitle.setText (JucePlugin_Name, juce::NotificationType::dontSendNotification);
    mTitle.setFont (juce::Font (montserratRegularTf.mPtr).withHeight (14));
    addAndMakeVisible (mTitle);

    mSubtitle.setText (
        juce::String ("Version ") + JucePlugin_VersionString,
        juce::NotificationType::dontSendNotification
    );
    mSubtitle.setFont (juce::Font (montserratExtraLightTf.mPtr).withHeight (9));
    addAndMakeVisible (mSubtitle);

    addAndMakeVisible (mPresetBar);
}

PresetPanel::~PresetPanel()
{

}

//==============================================================================

void PresetPanel::resized()
{
    static const auto sVerticalMargin   = 10;
    static const auto sHorizontalMargin = 20;
    static const auto sTitleSize        = juce::Rectangle<int> (150, 20);
    static const auto sSubtitleSize     = juce::Rectangle<int> (60, 14);

    const auto bounds        = getLocalBounds();
    const auto presetBarSize = juce::Rectangle<int> (
        bounds.getWidth() - sTitleSize.getWidth() - sHorizontalMargin * 2,
        20
    );

    mTitle.setBounds (
        sHorizontalMargin,
        sVerticalMargin,
        sTitleSize.getWidth(),
        sTitleSize.getHeight()
    );

    mSubtitle.setBounds (
        mTitle.getX(),
        mTitle.getBottom() - 5,
        sSubtitleSize.getWidth(),
        sSubtitleSize.getHeight()
    );

    mPresetBar.setBounds (
        bounds.getRight() - presetBarSize.getWidth() - sHorizontalMargin,
        sVerticalMargin + 5,
        presetBarSize.getWidth(),
        presetBarSize.getHeight()
    );
}

void PresetPanel::paint (juce::Graphics& g)
{
    const auto bounds = getLocalBounds();

    g.setColour (juce::Colours::white);
    g.drawLine (
        bounds.getX(),
        bounds.getBottom(),
        bounds.getRight(),
        bounds.getBottom(),
        2
    );
}

//==============================================================================

} // namespace ui
} // namespace mbctrl

