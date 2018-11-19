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

#include <ui/components/PresetBar.h>
#include <JuceHeader.h>
#include <grape/presets/PresetManager.h>

//==============================================================================

namespace mbctrl {
namespace ui {

//==============================================================================

class PresetPanel : public juce::Component
{
public:
    PresetPanel (grape::presets::PresetManager&);
    ~PresetPanel();

public: // juce::Component
    void resized() override;
    void paint (juce::Graphics&) override;

private:
    juce::DrawableButton    mLogo;
    PresetBar               mPresetBar;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetPanel)
};

//==============================================================================

} // namespace ui
} // namespace mbctrl
