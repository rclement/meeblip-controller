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

#include <common/Parameters.h>
#include <common/Settings.h>
#include <JuceHeader.h>
#include <grape/parameters/ParameterManager.h>
#include <grape/settings/SettingManager.h>
#include <map>

//==============================================================================

namespace mbctrl {
namespace controller {

//==============================================================================

class MidiController : private juce::AudioProcessorValueTreeState::Listener
                     , private grape::settings::SettingManager::Listener
{
public:
    MidiController (grape::parameters::ParameterManager&,
                    grape::settings::SettingManager&,
                    bool useMidiDevice);
    ~MidiController();

public:
    void setUseExternalMidi (bool);
    inline bool getUseExternalMidi() const { return mUseExternalMidi; }

    juce::StringArray getMidiOutputDevices() const;
    void updateMidiOutputDevices();
    bool selectDefaultMidiOutputDevice();
    bool selectMidiOutputDevice (int index);
    juce::String getSelectedMidiOutputDevice() const;

    void setMidiChannel (int channel);
    inline int getMidiChannel() const { return mMidiChannel; }

    void synchronize();

    juce::MidiBuffer extractMidiBuffer();

private:
    void sendMidiBuffer();

    void updateParametersValues();
    void updateSettingsValues();

    void updateUseExternalMidi (bool);
    void updateMidiOutputDevice (int);
    void updateMidiOutputDeviceByName (const juce::String&);
    void updateMidiChannel (int);

    void addMidiMessageToBuffer (common::ParameterId, float);

private: // juce::AudioProcessorValueTreeState::Listener
    void parameterChanged (const juce::String&, float) override;

private: // grape::settings::SettingManager::Listener
    void settingChanged (const juce::String&, const juce::var&) override;

private:
    bool                                    mUseExternalMidi;

    juce::StringArray                       mMidiOutputDevices;
    std::unique_ptr<juce::MidiOutput>       mMidiOutput;
    int                                     mMidiChannel;
    juce::MidiBuffer                        mMidiBuffer;

    grape::parameters::ParameterManager&    mParameterManager;
    common::ParameterMapper                 mParametersValues;

    grape::settings::SettingManager&        mSettingManager;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiController)
};

//==============================================================================

} // namespace controller
} // namespace mbctrl
