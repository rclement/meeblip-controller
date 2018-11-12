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

#include <JuceHeader.h>
#include <grape/presets/PresetManager.h>

//==============================================================================

namespace mbctrl {
namespace ui {

//==============================================================================

class PresetSaveDialog : public juce::Component
{
public:
    PresetSaveDialog (grape::presets::PresetManager&);
    ~PresetSaveDialog();

public: // juce::Component
    void resized() override;
    void paint (juce::Graphics&) override;

private:
    void closeParentModal();
    void savePreset();

private:
    grape::presets::PresetManager& mPresetManager;

    juce::Label       	mPresetNameLabel;
    juce::ComboBox      mPresetNameSelector;
    juce::Label         mPresetBankLabel;
    juce::ComboBox      mPresetBankSelector;
    juce::Label         mPresetAuthorLabel;
    juce::TextEditor    mPresetAuthorText;
    juce::Label         mPresetCommentsLabel;
    juce::TextEditor    mPresetCommentsText;
    juce::TextButton    mCancelButton;
    juce::TextButton    mSaveButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetSaveDialog)
};

//==============================================================================

} // namespace ui
} // namespace mbctrl
