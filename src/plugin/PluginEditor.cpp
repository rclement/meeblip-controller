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

#include <plugin/PluginProcessor.h>
#include <plugin/PluginEditor.h>

//==============================================================================

namespace mbctrl {
namespace plugin {

//==============================================================================

PluginEditor::PluginEditor (PluginProcessor& processor)
    : AudioProcessorEditor (&processor)
    , mPresetPanel (processor.getPresetManager(), processor.getUndoManager())
    , mControlPanel (processor.getParameterManager(),
                     processor.getMidiController())
    , mSettingsPanel (processor.getMidiController())
{
    juce::LookAndFeel::setDefaultLookAndFeel (&mLookAndFeel);

    addAndMakeVisible (mPresetPanel);
    addAndMakeVisible (mControlPanel);
    addAndMakeVisible (mSettingsPanel);

    setSize (450, 600);
}

PluginEditor::~PluginEditor()
{
    juce::LookAndFeel::setDefaultLookAndFeel (nullptr);
}

//==============================================================================

void PluginEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void PluginEditor::resized()
{
    static const auto sPanelHeight = 50;

    const auto bounds           = getLocalBounds();
    const auto panelWidth       = bounds.getWidth();
    const auto controlHeight    = bounds.getHeight() - sPanelHeight * 2;

    mPresetPanel.setBounds (0, 0, panelWidth, sPanelHeight);

    mControlPanel.setBounds (
        mPresetPanel.getX(),
        mPresetPanel.getBottom(),
        panelWidth,
        controlHeight
    );

    mSettingsPanel.setBounds (
        mPresetPanel.getX(),
        mControlPanel.getBottom(),
        panelWidth,
        sPanelHeight
    );
}

//==============================================================================

} // namespace plugin
} // namespace mbctrl
