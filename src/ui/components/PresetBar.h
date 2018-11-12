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

class PresetBar : public juce::Component
                , private grape::presets::PresetManager::Listener
{
public:
    PresetBar (grape::presets::PresetManager&);
    ~PresetBar();

public: // juce::Component
    void resized() override;
    void paint (juce::Graphics&) override;

private:
    void updateCurrentPreset (const grape::presets::Preset&);
    void openPresetLoader();
    juce::PopupMenu createPresetsMenu (const juce::Array<grape::presets::Preset>&, int);
    void openPresetSaveDialog();

private: // presets::PresetManager::Listener
    void presetChanged (const grape::presets::Preset&) override;

private:
    grape::presets::PresetManager&  mPresetManager;
    grape::presets::Preset          mCurrentPreset;

    juce::DrawableButton            mPresetPrevious;
    juce::DrawableButton    	    mPresetNext;
    juce::TextButton                mPresetLoader;
    juce::TextButton                mPresetSave;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetBar)
};

//==============================================================================

} // namespace ui
} // namespace mbctrl
