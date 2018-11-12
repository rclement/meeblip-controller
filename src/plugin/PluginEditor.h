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

#include <plugin/PluginProcessor.h>
#include <ui/CustomLookAndFeel.h>
#include <ui/panels/PresetPanel.h>
#include <ui/panels/SettingsPanel.h>
#include <ui/panels/ControlPanelAnode.h>
#include <JuceHeader.h>

//==============================================================================

namespace mbctrl {
namespace plugin {

//==============================================================================

class PluginEditor : public juce::AudioProcessorEditor
{
public:
    PluginEditor (PluginProcessor&);
    ~PluginEditor();

public: // juce::Component
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    PluginProcessor&    	mProcessor;
    ui::CustomLookAndFeel   mLookAndFeel;
    ui::PresetPanel         mPresetPanel;
    ui::ControlPanelAnode   mControlPanel;
    ui::SettingsPanel       mSettingsPanel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

//==============================================================================

} // namespace plugin
} // namespace mbctrl
